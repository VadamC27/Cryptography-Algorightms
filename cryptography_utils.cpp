#include "cryptography_utils.h"


template long long gcd<long long>(long long a, long long b);
//greatest common divisor
template <typename T>
T gcd(T a, T b) { 
    while (a != b) {
        if (a > b)  a -= b;
        else b -= a;
    }
    return a;
}

//checks if given number is a prime number
bool checkPrime(int num) { 
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0) return false;
    return true;
}