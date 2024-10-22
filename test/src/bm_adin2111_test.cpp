#include "bm_adin2111.h"
#include "gtest/gtest.h"

static void link_changed_on_port(int port_index) {
  (void)port_index;
}

TEST(Adin2111, send) {
  Adin2111 adin;
  adin.link_change_cb = link_changed_on_port;
  adin2111_init(&adin);
  NetworkInterface netif = prep_adin2111_netif(&adin);
  int err = netif.trait->send(netif.self, (unsigned char *)"hello", 5);
  EXPECT_EQ(err, 0);
}
