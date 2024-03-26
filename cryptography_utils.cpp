#include "cryptography_utils.h"

#include <iostream>

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
bool is_prime(int num) { 
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0) return false;
    return true;
}

void print_vector(std::vector<long long> vec){
    for (long long num : vec ){
        std::cout << num;
    }
}

long long mod_exp(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}