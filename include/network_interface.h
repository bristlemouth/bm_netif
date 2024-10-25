#include "util.h"

typedef struct {
  BmErr (*const send)(void *self, uint8_t *data, size_t length);
} NetworkInterfaceTrait;

typedef struct {
  void *self;
  NetworkInterfaceTrait const *trait;
} NetworkInterface;
