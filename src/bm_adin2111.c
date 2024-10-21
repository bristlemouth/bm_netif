#include "adin2111.h"
#include "bm_adin2111.h"
#include <stdatomic.h>
#include <stdbool.h>
#include <string.h>

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

static void adin2111_init(Adin2111 *self, Receiver receiver) {
  self->receiver = receiver;
}

static int adin2111_send(Adin2111 *self, unsigned char *data,
                         unsigned int length) {
  // TODO
  return 0;
}

static inline void adin2111_init_(void *self, Receiver receiver) {
  adin2111_init(self, receiver);
}

static inline int adin2111_send_(void *self, unsigned char *data,
                                 unsigned int length) {
  return adin2111_send(self, data, length);
}

// Build a generic NetworkInterface out of a concrete Adin2111
NetworkInterface prep_adin2111_netif(Adin2111 *adin) {
  // Create the vtable once and attach a pointer to it every time
  static NetworkInterfaceTrait const trait = {.init = adin2111_init_,
                                              .send = adin2111_send_};
  return (NetworkInterface){.trait = &trait, .self = adin};
}

static int adin2111_send_bare(unsigned char *data, unsigned int length) {
  // TODO
  return 0;
}

Adin2111 create_adin2111(void) {
  adin2111_DeviceStruct_t adin_device;
  adin2111_DriverConfig_t adin_cfg;
  adi_eth_Result_e result = adin2111_Init(&adin_device, &adin_cfg);

  static Adin2111 adin = {
      .receiver = 0,
      .send = adin2111_send_bare,
  };
  return adin;
}