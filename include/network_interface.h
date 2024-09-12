#include "receiver.h"

typedef struct {
  void (*const init)(void *self, Receiver receiver);
  int (*const send)(void *self, unsigned char *data, unsigned int length);
} NetworkInterfaceTrait;

typedef struct {
  void *self;
  NetworkInterfaceTrait const *trait;
} NetworkInterface;
