#include "adin2111.h"
#include "network_interface.h"
#include "util.h"

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
  void *device_handle;
  void (*link_change_cb)(int port_index);
} Adin2111;

#ifdef __cplusplus
extern "C" {
#endif

BmErr adin2111_init(Adin2111 *self);
NetworkInterface prep_adin2111_netif(Adin2111 *adin);

#ifdef __cplusplus
}
#endif
