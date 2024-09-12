#include "bm_adin2111.h"
#include "gtest/gtest.h"

TEST(Adin2111, send) {
  Adin2111 adin;
  NetworkInterface netif = prep_adin2111_netif(&adin);
  int err = netif.trait->send(netif.self, (unsigned char *)"hello", 5);
  EXPECT_EQ(err, 0);
}