#ifndef CRYPTOGRAPHY_UTILS_H
#define CRYPTOGRAPHY_UTILS_H

#include <vector>
#include <limits>

bool is_prime( int num);

template <typename T>
T gcd(T a, T b);

void print_vector(std::vector<long long> vec);

long long mod_exp(long long base, long long exponent, long long modulus);

#endif // CRYPTOGRAPHY_UTILS_H