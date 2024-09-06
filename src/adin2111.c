#include "adin2111.h"
#include <string.h>

#define BUFSIZE 64
static char BUFFER[BUFSIZE];

static void adin2111_receive(Adin2111 *self, unsigned char *data,
                             unsigned int length) {
  const unsigned int len_to_copy = length < BUFSIZE ? length : BUFSIZE;
  memcpy(BUFFER, data, len_to_copy);
}

// Wraper to convert self from void* to Adin2111*
static inline void adin2111_receive_(void *self, unsigned char *data,
                                     unsigned int length) {
  adin2111_receive(self, data, length);
}

// Build a generic Receiver out of a concrete Adin2111
Receiver prep_adin2111_receiver(Adin2111 *adin) {
  // Create the vtable once and attach a pointer to it every time
  static ReceiverTrait const trait = {.receive = adin2111_receive_};
  return (Receiver){.trait = &trait, .self = adin};
}
