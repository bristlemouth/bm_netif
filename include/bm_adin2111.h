#include "network_interface.h"

// whatever, placeholder
typedef int Pin;

typedef struct {
  Pin pico;
  Pin poci;
  Pin cs;
  Pin sck;
} Spi;

typedef struct {
  Receiver receiver;
  Spi spi;
} Adin2111;
