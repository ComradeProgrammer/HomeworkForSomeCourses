#include <iostream>

#include "MyRsaKey.h"
using namespace std;
using boost::multiprecision::cpp_int;
int main() {
    cpp_int p, q, phi;
        while (1) {
            p = generateRandomPrimeNumberWithBits(1024);
            q = generateRandomPrimeNumberWithBits(1024);
            phi = (p - 1) * (q - 1);
            if ((phi % 65537) != 0) {
                break;
            }
        }
    cout<<"p="<<p<<endl;
    cout<<"q="<<q<<endl;
    cout<<"n="<<p*q<<endl;
    cout<<"phi(n)="<<phi<<endl;
    
    auto tmp = MyRsaKey::generateKeyPair(p,q);
    MyRsaKey key1 = tmp.first;
    MyRsaKey key2 = tmp.second;
    cout<<"key1={"<<key1.getE()<<","<<key1.getN()<<"}"<<endl;
    cout<<"key2={"<<key2.getE()<<","<<key2.getN()<<"}"<<endl;

    
    auto raw=generateRandomBigNumberWithBits(1024);
    cout<<"raw content: "<<raw<<endl;
    auto encoded=key1.encode(raw);
    cout<<"encrypted content "<<encoded<<endl;
    auto decoded=key2.decode(encoded);
    cout<<"decrypted content "<<decoded<<endl;
    
}