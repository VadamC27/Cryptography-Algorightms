#ifndef RSA_H
#define RSA_H

#include <ctime>

struct RSAkeys generate_RSA();

struct RSAkeys generate_RSA(long long p, long long q);

void RSAmenu();

struct PublicKey{
    long long e;
    long long n;
};

struct PrivateKey{
    long long d;
    long long n;
};

struct RSAkeys{
    PublicKey public_key;
    PrivateKey private_key; 
};



#endif //RSA_H