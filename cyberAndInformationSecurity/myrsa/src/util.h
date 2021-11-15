#ifndef __UTIL_H_
#define __UTIL_H_
#include<vector>
#include <boost/multiprecision/cpp_int.hpp>
/**
 * @brief 生成一个指定位数的大整数，保证最高位不是0
 * @param bits 位数
*/
boost::multiprecision::cpp_int generateRandomBigNumberWithBits(int bits);

/**
 * @brief 使用 Fermat素性测试对n是否为素数进行测试
*/
bool primeTest(boost::multiprecision::cpp_int n);

/**
 * @brief 使用快速幂算法计算a的n次幂对modbase取模
 * @param a 底数
 * @param power 指数
 * @param modBase 模数
 * @return a^n mod modbase
*/
boost::multiprecision::cpp_int powermod(boost::multiprecision::cpp_int a,boost::multiprecision::cpp_int power,boost::multiprecision::cpp_int modBase);

/**
 * @brief 生成一个指定位数的大素数，保证最高位不是0
 * @param bits 位数
*/
boost::multiprecision::cpp_int generateRandomPrimeNumberWithBits(int bits);


/**
 * @brief 拓展欧几里得算法，求解不定方程ax+by=gcd(a,b)的一个特解
 * @param a 入参，即不定方程中的a
 * @param b 入参，即不定方程中的b
 * @param x 出参，引用类型，函数返回时会被修改为不定方程里x的值
 * @param x 出参，引用类型，函数返回时会被修改为不定方程里y的值
 * @return gcd(a,b)
*/
boost::multiprecision::cpp_int extendedEuclidean(
    boost::multiprecision::cpp_int a,
    boost::multiprecision::cpp_int b,
    boost::multiprecision::cpp_int &x,
    boost::multiprecision::cpp_int &y
);
#endif
