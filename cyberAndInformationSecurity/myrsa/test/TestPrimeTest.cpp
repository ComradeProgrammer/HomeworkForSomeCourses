#include <gtest/gtest.h>
#define private public
#define protected public

#include "util.h"
using namespace std;
class TestPowerPrime : public ::testing::Test {
   protected:
    virtual void SetUp() {
        uint32_t seed = time(0);
        srand(seed);
    }
};
TEST_F(TestPowerPrime, TestPowerPrime1) {
    // generate s
    vector<int> prime = {};
    vector<int> nonprime = {};
    for (int i = 30000; i < 31000; i++) {
        if (i % 2 == 0) {
            continue;
        }
        bool mark = true;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                mark = false;
                break;
            }
        }
        if (!mark) {
            nonprime.push_back(i);
        } else {
            prime.push_back(i);
        }
    }
    for (auto i : prime) {
        EXPECT_EQ(primeTest(i), true);
    }
    for (auto i : nonprime) {
        EXPECT_EQ(primeTest(i), false);
    }
}