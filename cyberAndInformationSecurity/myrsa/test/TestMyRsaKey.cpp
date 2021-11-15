#include <gtest/gtest.h>
#define private public
#define protected public
#include "MyRsaKey.h"
using namespace std;
using boost::multiprecision::cpp_int;

class TestMyRsaKey : public ::testing::Test {
   protected:
    virtual void SetUp() {
        uint32_t seed = time(0);
        srand(seed);
    }
};

TEST_F(TestMyRsaKey, TestGenerateKeyPair) {
    for (int i = 0; i < 5; i++) {
        cpp_int p, q, phi;
        while (1) {
            p = generateRandomPrimeNumberWithBits(128);
            q = generateRandomPrimeNumberWithBits(128);
            phi = (p - 1) * (q - 1);
            if ((phi % 65537) != 0) {
                break;
            }
        }

        auto res = MyRsaKey::generateKeyPair(p, q);
        cpp_int e = res.first.e;
        cpp_int d = res.second.e;
        EXPECT_EQ((e * d) % phi, 1);
    }
}
TEST_F(TestMyRsaKey, TestEncodeAndDecode) {
    auto tmp=MyRsaKey::generateKeyPair(1024);
    MyRsaKey key1=tmp.first;
    MyRsaKey key2=tmp.second;
    auto raw=generateRandomBigNumberWithBits(1024);
    auto encoded=key1.encode(raw);
    auto decoded=key2.decode(encoded);
    EXPECT_EQ(raw,decoded);
}