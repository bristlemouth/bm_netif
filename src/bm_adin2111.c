#include "bm_adin2111.h"
#include "aligned_malloc.h"
#include "bm_os.h"
#include <stdatomic.h>
#include <stdbool.h>
#include <string.h>

// Extra 4 bytes for FCS and 2 bytes for the frame header
#define MAX_FRAME_BUF_SIZE (MAX_FRAME_SIZE + 4 + 2)
#define DMA_ALIGN_SIZE (4)

// For now, there's only ever one ADIN2111.
// When supporting multiple in the future,
// we can allocate this dynamically.
static Adin2111 *ADIN2111 = NULL;
static adin2111_DeviceStruct_t DEVICE_STRUCT;
#ifdef ENABLE_TESTING
static uint8_t DEVICE_MEMORY[ADIN2111_DEVICE_SIZE + 80];
#else
static uint8_t DEVICE_MEMORY[ADIN2111_DEVICE_SIZE];
#endif
static adin2111_DriverConfig_t DRIVER_CONFIG = {
    .pDevMem = (void *)DEVICE_MEMORY,
    .devMemSize = sizeof(DEVICE_MEMORY),
    .fcsCheckEn = false,
    .tsTimerPin = ADIN2111_TS_TIMER_MUX_NA,
    .tsCaptPin = ADIN2111_TS_CAPT_MUX_NA,
};
static adi_eth_BufDesc_t RX_BUFFERS[RX_QUEUE_NUM_ENTRIES];

/**************** Private Helper Functions ****************/

// After a TX buffer is sent, it gets freed here
static void free_tx_buffer(adi_eth_BufDesc_t *buffer_description) {
  if (buffer_description) {
    if (buffer_description->pBuf) {
      aligned_free(buffer_description->pBuf);
    }
    bm_free(buffer_description);
  }
}

// This is the callback that gets called after a TX buffer is sent
static void send_callback(void *device_param, uint32_t event,
                          void *buffer_description_param) {
  (void)device_param;
  (void)event;

  adi_eth_BufDesc_t *buffer_description =
      (adi_eth_BufDesc_t *)buffer_description_param;
  free_tx_buffer(buffer_description);
}

// Allocate buffers for sending, copy the given data, and submit to the driver
static BmErr adin2111_netif_send(Adin2111 *self, uint8_t *data, size_t length) {
  BmErr err = BmOK;
  adi_eth_BufDesc_t *buffer_description = bm_malloc(sizeof(adi_eth_BufDesc_t));
  if (!buffer_description) {
    err = BmENOMEM;
    goto end;
  }
  memset(buffer_description, 0, sizeof(adi_eth_BufDesc_t));
  buffer_description->pBuf = aligned_malloc(DMA_ALIGN_SIZE, length);
  if (!buffer_description->pBuf) {
    bm_free(buffer_description);
    err = BmENOMEM;
    goto end;
  }
  memcpy(buffer_description->pBuf, data, length);
  buffer_description->bufSize = length;
  buffer_description->cbFunc = send_callback;
  adin2111_SubmitTxBuffer(self->device_handle, ADIN2111_TX_PORT_FLOOD,
                          buffer_description);
end:
  return err;
}

// Trait wrapper function to convert self from void* to Adin2111*
static inline BmErr adin2111_netif_send_(void *self, uint8_t *data,
                                         size_t length) {
  return adin2111_netif_send(self, data, length);
}

// Called by the driver when the link status changes
// If the user has registered a callback, call it
static void link_change_callback_(void *device_param, uint32_t event,
                                  void *status_registers_param) {
  (void)event;

  if (ADIN2111 && ADIN2111->link_change_callback) {
    const adi_mac_StatusRegisters_t *status_registers =
        (adi_mac_StatusRegisters_t *)status_registers_param;

    int port_index = -1;
    if (status_registers->p1StatusMasked == ADI_PHY_EVT_LINK_STAT_CHANGE) {
      port_index = ADIN2111_PORT_1;
    } else if (status_registers->p2StatusMasked ==
               ADI_PHY_EVT_LINK_STAT_CHANGE) {
      port_index = ADIN2111_PORT_2;
    }

    if (port_index >= 0) {
      adin2111_DeviceHandle_t device_handle =
          (adin2111_DeviceHandle_t)device_param;
      adi_eth_LinkStatus_e status;
      adi_eth_Result_e result =
          adin2111_GetLinkStatus(device_handle, port_index, &status);
      if (result == ADI_ETH_SUCCESS) {
        ADIN2111->link_change_callback(port_index, status);
      }
    }
  }
}

// Called by the driver on received data
// If the user has registered a callback, call it
static void receive_callback_(void *device_param, uint32_t event,
                              void *buffer_description_param) {
  (void)device_param;
  (void)event;

  if (ADIN2111 && ADIN2111->receive_callback) {
    adi_eth_BufDesc_t *buffer_description =
        (adi_eth_BufDesc_t *)buffer_description_param;
    uint8_t port_index = 1 << buffer_description->port;
    ADIN2111->receive_callback(port_index, buffer_description->pBuf,
                               buffer_description->bufSize);
  }
}

/**************** Public API Functions ****************/

/*! @brief Initialize an Adin2111 device
    @param self a pointer to an Adin2111 struct
    @return BmOK if successful, otherwise an error */
BmErr adin2111_init(Adin2111 *self) {
  BmErr err = BmOK;

  if (ADIN2111) {
    err = BmEALREADY;
    goto end;
  }

  self->device_handle = &DEVICE_STRUCT;
  ADIN2111 = self;

  adi_eth_Result_e result = adin2111_Init(self->device_handle, &DRIVER_CONFIG);
  if (result != ADI_ETH_SUCCESS) {
    err = BmENODEV;
    goto end;
  }

  result = adin2111_RegisterCallback(self->device_handle, link_change_callback_,
                                     ADI_MAC_EVT_LINK_CHANGE);
  if (result != ADI_ETH_SUCCESS) {
    err = BmENODEV;
    goto end;
  }

  for (int i = 0; i < RX_QUEUE_NUM_ENTRIES; i++) {
    adi_eth_BufDesc_t *buffer_description = &RX_BUFFERS[i];
    memset(buffer_description, 0, sizeof(adi_eth_BufDesc_t));
    buffer_description->pBuf =
        aligned_malloc(DMA_ALIGN_SIZE, MAX_FRAME_BUF_SIZE);
    if (!buffer_description->pBuf) {
      err = BmENOMEM;
      goto end;
    }
    memset(buffer_description->pBuf, 0, MAX_FRAME_BUF_SIZE);
    buffer_description->bufSize = MAX_FRAME_BUF_SIZE;
    buffer_description->cbFunc = receive_callback_;
    result = adin2111_SubmitRxBuffer(self->device_handle, buffer_description);
    if (result != ADI_ETH_SUCCESS) {
      err = BmENODEV;
      goto end;
    }
  }

  result = adin2111_SyncConfig(self->device_handle);
  if (result != ADI_ETH_SUCCESS) {
    err = BmENODEV;
    goto end;
  }

  result = adin2111_EnablePort(self->device_handle, ADIN2111_PORT_1);
  if (result != ADI_ETH_SUCCESS) {
    err = BmENODEV;
    goto end;
  }
  result = adin2111_EnablePort(self->device_handle, ADIN2111_PORT_2);
  if (result != ADI_ETH_SUCCESS) {
    err = BmENODEV;
    goto end;
  }

end:
  return err;
}

/// Build a generic NetworkInterface out of a concrete Adin2111
NetworkInterface prep_adin2111_netif(Adin2111 *adin) {
  // Create the vtable once and attach a pointer to it every time
  static NetworkInterfaceTrait const trait = {.send = adin2111_netif_send_};
  return (NetworkInterface){.trait = &trait, .self = adin};
}
