#include "bm_adin2111.h"
#include <stdatomic.h>
#include <stdbool.h>
#include <string.h>

// For now, there's only ever one ADIN2111.
// When supporting multiple in the future,
// we can allocate this dynamically.
static Adin2111 *ADIN2111 = NULL;
static adin2111_DeviceStruct_t DEVICE_STRUCT;
static uint8_t DEVICE_MEMORY[ADIN2111_DEVICE_SIZE];
static adin2111_DriverConfig_t DRIVER_CONFIG = {
    .pDevMem = (void *)DEVICE_MEMORY,
    .devMemSize = sizeof(DEVICE_MEMORY),
    .fcsCheckEn = false,
    .tsTimerPin = ADIN2111_TS_TIMER_MUX_NA,
    .tsCaptPin = ADIN2111_TS_CAPT_MUX_NA,
};

#define BUFSIZE 4096
static unsigned char BUFFER[BUFSIZE];
static unsigned int READABLE_BYTES = 0;
static atomic_bool LOCKED = false;

/*!
  \brief Receive data from the network

  Concrete implementation of the Receiver trait
  Handle as quickly as possible.
  Make a copy of the received data, and set a notification flag, then return.
  Clients can poll the flag to know when new data is available for processing.
  If another thread holds the buffer mutex, return 0 immediately.

  \param self - the receiver
  \param data - the data to receive
  \param length - the length of data that is available
  \return the number of bytes received
*/
static unsigned int adin2111_receive(const Adin2111 *const self,
                                     const unsigned char *const data,
                                     unsigned int length) {
  (void)self;
  unsigned int bytes_received = 0;
  bool expected = false;
  if (atomic_compare_exchange_strong(&LOCKED, &expected, true)) {
    const unsigned int writable_bytes = BUFSIZE - READABLE_BYTES;
    const unsigned int len_to_copy =
        length < writable_bytes ? length : writable_bytes;
    memcpy(BUFFER, data, len_to_copy);
    READABLE_BYTES += len_to_copy;
    bytes_received = len_to_copy;
    atomic_store(&LOCKED, false);
  }
  return bytes_received;
}

// Wraper to convert self from void* to Adin2111*
static inline unsigned int adin2111_receive_(void *self, unsigned char *data,
                                             unsigned int length) {
  return adin2111_receive(self, data, length);
}

// Build a generic Receiver out of a concrete Adin2111
Receiver prep_adin2111_receiver(Adin2111 *adin) {
  // Create the vtable once and attach a pointer to it every time
  static ReceiverTrait const trait = {.receive = adin2111_receive_};
  return (Receiver){.trait = &trait, .self = adin};
}

static void adin2111_netif_init(Adin2111 *self, Receiver receiver) {
  self->receiver = receiver;
}

static int adin2111_netif_send(Adin2111 *self, unsigned char *data,
                               unsigned int length) {
  adi_eth_BufDesc_t buffer_description;
  buffer_description.bufSize = length;
  buffer_description.pBuf = data;
  // TODO: This call segfaults during testing.
  // Continuing to flesh this out so tests pass is the next task.
  // adin2111_SubmitTxBuffer(self->device_handle, ADIN2111_TX_PORT_FLOOD,
  //                         &buffer_description);
  return 0;
}

static inline void adin2111_netif_init_(void *self, Receiver receiver) {
  adin2111_netif_init(self, receiver);
}

static inline int adin2111_netif_send_(void *self, unsigned char *data,
                                       unsigned int length) {
  return adin2111_netif_send(self, data, length);
}

// Build a generic NetworkInterface out of a concrete Adin2111
NetworkInterface prep_adin2111_netif(Adin2111 *adin) {
  // Create the vtable once and attach a pointer to it every time
  static NetworkInterfaceTrait const trait = {.init = adin2111_netif_init_,
                                              .send = adin2111_netif_send_};
  return (NetworkInterface){.trait = &trait, .self = adin};
}

static void link_change_cb(void *device_param, uint32_t event,
                           void *status_registers_param) {
  (void)device_param;
  (void)event;

  adi_mac_StatusRegisters_t *status_registers =
      (adi_mac_StatusRegisters_t *)status_registers_param;

  int port_index = -1;
  if (status_registers->p1StatusMasked == ADI_PHY_EVT_LINK_STAT_CHANGE) {
    port_index = ADIN2111_PORT_1;
  } else if (status_registers->p2StatusMasked == ADI_PHY_EVT_LINK_STAT_CHANGE) {
    port_index = ADIN2111_PORT_2;
  }

  if (ADIN2111 && ADIN2111->link_change_cb && port_index != -1) {
    ADIN2111->link_change_cb(port_index);
  }
}

BmErr adin2111_init(Adin2111 *self) {
  if (ADIN2111) {
    return BmEALREADY;
  }

  self->device_handle = &DEVICE_STRUCT;
  ADIN2111 = self;
  BmErr err = BmOK;

  adi_eth_Result_e result = adin2111_Init(self->device_handle, &DRIVER_CONFIG);
  if (result != ADI_ETH_SUCCESS) {
    err = BmENODEV;
    goto end;
  }

  result = adin2111_RegisterCallback(self->device_handle, link_change_cb,
                                     ADI_MAC_EVT_LINK_CHANGE);
  if (result != ADI_ETH_SUCCESS) {
    err = BmENODEV;
    goto end;
  }

  // TODO: aligned alloc 8 of these buffers and submit each one
  // adin2111_SubmitRxBuffer(device_handle, buffer_description)

end:
  return err;
}
