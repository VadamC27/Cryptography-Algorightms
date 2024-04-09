#ifndef CRYPTOGRAPHY_UTILS_H
#define CRYPTOGRAPHY_UTILS_H

#include <vector>
#include <limits>
#include <chrono>

bool is_prime( int num);

template <typename T>
T gcd(T a, T b);

void print_vector(std::vector<long long> vec);

long long mod_exp(long long base, long long exponent, long long modulus);

long long generate_prime();
long long generate_prime(long long min, long long max);

#endif /* CRYPTOGRAPHY_UTILS_H*/ 