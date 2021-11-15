#ifndef __MY_RSA_H_
#define __MY_RSA_H_
#include<map>
#include <boost/multiprecision/cpp_int.hpp>
#include"util.h"
class MyRsaKey{
    public:
    /**
     * @brief 构造函数
     * @param _e 对应公钥{e,n}里的e或者私钥{d,n}里的d(反正公钥私钥地位等同)
     * @param _n 对应公钥{e,n}里的n或者私钥{d,n}里的n(反正公钥私钥地位等同)
     * 
    */
    MyRsaKey(boost::multiprecision::cpp_int _e,boost::multiprecision::cpp_int _n):n(_n),e(_e){}
    /**
     * @brief 复制构造函数
    */
    MyRsaKey(const MyRsaKey& )=default;

    /**
     * @brief 生成一个公钥-私钥对
     * @param bits 位数
     * @return pair<MyRsaKey,MyRsaKey>, 两个分别是公钥和私钥
    */
    static std::pair<MyRsaKey,MyRsaKey>generateKeyPair(int bits);

    /**
     * @brief 在已经生成了两个大素数情况下，用给定大素数生成一个公钥-私钥对
     * @param p 大素数
     * @param q 大素数
     * @return pair<MyRsaKey,MyRsaKey>, 两个分别是公钥和私钥
    */
    static std::pair<MyRsaKey,MyRsaKey>generateKeyPair(boost::multiprecision::cpp_int p,boost::multiprecision::cpp_int q);

    /**
     * @brief 使用密钥加密
     * @param content 明文
     * @return 密文
     * 
    */
    boost::multiprecision::cpp_int encode(boost::multiprecision::cpp_int content);

    /**
     * @brief 使用密钥解密
     * @param content 密文
     * @return 明文
     * 
    */
    boost::multiprecision::cpp_int decode(boost::multiprecision::cpp_int content);

    boost::multiprecision::cpp_int getE(){return e;}
    boost::multiprecision::cpp_int getN(){return n;}
    
    private:


    //对应公钥{e,n}里的e或者私钥{d,n}里的d(反正公钥私钥地位等同)
    boost::multiprecision::cpp_int n;
    //对应公钥{e,n}里的n或者私钥{d,n}里的n(反正公钥私钥地位等同)
    boost::multiprecision::cpp_int e;
};
#endif