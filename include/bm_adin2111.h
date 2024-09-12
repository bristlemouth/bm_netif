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

#ifdef __cplusplus
extern "C" {
#endif

NetworkInterface prep_adin2111_netif(Adin2111 *adin);

#ifdef __cplusplus
}
#endif
