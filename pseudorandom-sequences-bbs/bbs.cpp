#include "..\cryptography_utils.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>

long long generate_mod(int mod, int rest) {
    int maxIterations = (rand() % 2500 )+1000;
    int iteration, result = 0;
    for (iteration = 0; iteration < maxIterations; iteration++)
        result += mod;
    result = result + rest;
    while (!check_prime(result)) {
        result += mod;
    }
    return result;
}

long long generateN() {
    long long  p = generate_mod(4, 3), q = generate_mod(4, 3);
    //std::cout << "p = " << p << " mod 4: " << p % 4 << "\n" << "q = " << q << " mod 4: " << q % 4 << "\n";
    return p * q;
}

std::string generate_sequence(int length) {
    if(length <= 0) return "";

    long long  N = generateN(), X;
    do {
        X = (rand() % 9000) + 1000;
    } while (gcd<long long>(N, X) != 1);

    long long seed = (X * X) % N;

    std::string sequence = "";
    sequence += std::to_string(seed % 2);
    long long x = seed;
    for (int i = 1; i<length; i++){
        x =  (x*x) % N;
        sequence += std::to_string(x % 2);
    }

    return sequence;
}

long long generateN(long long p, long long q) {
    int err = 0;
    if(!check_prime(p)){
        std::cout<<"p nie jest liczba pierwsza!!\n";
        err = 1;
    }
    if(!check_prime(q)){
        std::cout<<"q nie jest liczba pierwsza!!\n";
        err = 1;
    }
    if(err){
        return -1;
    }
    //std::cout << "p = " << p << " mod 4: " << p % 4 << "\n" << "q = " << q << " mod 4: " << q % 4 << "\n";
    return p * q;
}

std::string generate_sequence(int length, long long p, long long q) {
    if(length <= 0) return "";

    long long  N = generateN(p, q), X;

    if(N == -1){
        return "error";
    }

    do {
        X = (rand() % 9000) + 1000;
    } while (gcd<long long>(N, X) != 1);

    long long seed = (X * X) % N;

    std::string sequence = "";
    sequence += std::to_string(seed % 2);
    long long x = seed;
    for (int i = 1; i<length; i++){
        x =  (x*x) % N;
        sequence += std::to_string(x % 2);
    }

    return sequence;
}




