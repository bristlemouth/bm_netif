#include "bm_adin2111.h"
#include "fff.h"
#include "gtest/gtest.h"

DEFINE_FFF_GLOBALS;

extern "C" {
void *bm_malloc(size_t size) { return malloc(size); }
void bm_free(void *p) { free(p); }
}

FAKE_VALUE_FUNC(uint32_t, HAL_DisableIrq);
FAKE_VALUE_FUNC(uint32_t, HAL_EnableIrq);
FAKE_VALUE_FUNC(uint32_t, HAL_GetEnableIrq);
FAKE_VALUE_FUNC(uint32_t, HAL_RegisterCallback, HAL_Callback_t const *, void *);
FAKE_VALUE_FUNC(uint32_t, HAL_SpiReadWrite, uint8_t *, uint8_t *, uint32_t,
                bool);
FAKE_VALUE_FUNC(uint32_t, HAL_SpiRegisterCallback, HAL_Callback_t const *,
                void *);
FAKE_VALUE_FUNC(uint32_t, HAL_UnInit_Hook);
FAKE_VALUE_FUNC(long unsigned int, __REV, long unsigned int);
FAKE_VOID_FUNC(__disable_irq);
FAKE_VOID_FUNC(__enable_irq);

FAKE_VOID_FUNC(link_changed_on_port, int);
FAKE_VALUE_FUNC(size_t, received_data_on_port, uint8_t *, size_t, int);

TEST(Adin2111, send) {
  Adin2111 adin;
  adin.link_change_callback = link_changed_on_port;
  adin.receive_callback = received_data_on_port;
  BmErr err = adin2111_init(&adin);
  EXPECT_EQ(err, BmOK);
  NetworkInterface netif = prep_adin2111_netif(&adin);
  err = netif.trait->send(netif.self, (unsigned char *)"hello", 5);
  EXPECT_EQ(err, BmOK);
}
