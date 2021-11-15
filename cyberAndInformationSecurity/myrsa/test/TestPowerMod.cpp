#include <gtest/gtest.h>
#define private public
#define protected public

#include "util.h"

class TestPowerMod : public ::testing::Test {
   protected:
    virtual void SetUp() {
        uint32_t seed = time(0);
        srand(seed);
    }
};
TEST_F(TestPowerMod, TestPowerMod1) {
    for (int i = 25; i < 30; i++) {
        for (int j = 2; j < 5; j++) {
            auto ans = powermod(i, j, 0x7fffffff);
            int std = 1;
            for (int k = 0; k < j; k++) {
                std *= i;
            }
            EXPECT_EQ(ans, std);
        }
    }
}
TEST_F(TestPowerMod, TestPowerMod2) {
    for (int i = 25; i < 30; i++) {
        for (int j = 2; j < 5; j++) {
            auto ans = powermod(i, j, i * i);
            int std = 1;
            for (int k = 0; k < j; k++) {
                std *= i;
            }
            EXPECT_EQ(ans, std % (i * i));
        }
    }
}