#include <gtest/gtest.h>
#define private public
#define protected public

#include "util.h"

using namespace std;
using boost::multiprecision::cpp_int;

class TestExtendedEuclidean : public ::testing::Test {
   protected:
    virtual void SetUp() {
        uint32_t seed = time(0);
        srand(seed);
    }
};

TEST_F(TestExtendedEuclidean, TestExtendedEuclidean1) { 
    for (int i=0;i<20;i++){
        cpp_int a= generateRandomBigNumberWithBits(64);
        cpp_int b= generateRandomBigNumberWithBits(64);
        cpp_int c,d;
        auto gcd=extendedEuclidean(a,b,c,d);
        EXPECT_EQ(a*c+b*d,gcd);
    } 
}

TEST_F(TestExtendedEuclidean, TestExtendedEuclidean2) { 
    cpp_int a= generateRandomPrimeNumberWithBits(128);
    cpp_int b= 65537;
    cpp_int c,d;
    auto gcd=extendedEuclidean(a,b,c,d);
    EXPECT_EQ(gcd,1);
}