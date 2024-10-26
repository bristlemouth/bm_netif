#include "adin2111.h"
#include "network_interface.h"
#include "util.h"

typedef struct {
  void *device_handle;
  void (*link_change_callback)(uint8_t port_index, bool is_up);
  size_t (*receive_callback)(uint8_t port_index, uint8_t *data, size_t length);
} Adin2111;

#ifdef __cplusplus
extern "C" {
#endif

BmErr adin2111_init(Adin2111 *self);
NetworkInterface prep_adin2111_netif(Adin2111 *adin);

#ifdef __cplusplus
}
#endif
