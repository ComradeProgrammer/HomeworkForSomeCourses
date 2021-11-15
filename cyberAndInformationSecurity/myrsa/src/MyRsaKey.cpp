#include "MyRsaKey.h"
using namespace std;
using boost::multiprecision::cpp_int;
std::pair<MyRsaKey, MyRsaKey> MyRsaKey::generateKeyPair(int bits) {
    while (1) {
        //生成两个大素数
        cpp_int p = generateRandomPrimeNumberWithBits(bits);
        cpp_int q = generateRandomPrimeNumberWithBits(bits);
        //欧拉函数值
        cpp_int phi = (p - 1) * (q - 1);
        //排除掉phi不和65537互素的情况（因为通常选取65537这个质数做密钥/公钥）
        if ((phi % 65537) == 0) {
            continue;
        }
        return generateKeyPair(p, q);
    }
}

std::pair<MyRsaKey, MyRsaKey> MyRsaKey::generateKeyPair(boost::multiprecision::cpp_int p,
                                                        boost::multiprecision::cpp_int q) {
    cpp_int n = p * q;
    cpp_int phi = (p - 1) * (q - 1);

    cpp_int e, d;

    cpp_int x, y;
    e = 65537;
    //使用拓展欧几里得算法求解模反元素特解
    auto gcd = extendedEuclidean(e, phi, x, y);

    //找出一个确保为正的模反元素
    if (x < 0) {
        d = x + ((-x) / (phi / gcd) + 1) * (phi / gcd);
    } else {
        d = x;
    }

    MyRsaKey k1(e, n);
    MyRsaKey k2(d, n);
    return {k1, k2};
}

cpp_int MyRsaKey::encode(cpp_int content){
    return powermod(content,e,n);
}
cpp_int MyRsaKey::decode(cpp_int content){
    return powermod(content,e,n);
}