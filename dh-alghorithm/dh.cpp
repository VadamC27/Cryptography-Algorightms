#include "dh.h"

#include <cstdio>
#include <iostream>

long long find_primitive_root(long long n) {
    for (long long g = 2; g < n; g++) {
        bool is_primitive = true;
        for (long long i = 1; i < n - 1; i++) {
            if (mod_exp(g, i, n) == 1) {
                is_primitive = false;
                break;
            }
        }
        if (is_primitive) return g;
    }
    return -1; // No primitive root found
}


void DHalgorithm(){
    long long n = generate_prime(1000000, 10000000); 
    long long g = find_primitive_root(n);
    //printf("Prime modulus (n): %lld\n", n);printf("Generator (g): %lld\n", g);

    long long A_secret = (rand() %1000000 ) + 10000;
    long long B_secret = (rand() %1000000 ) + 10000;

    long long X = mod_exp(g, A_secret, n);


    long long Y = mod_exp(g, B_secret, n);


    long long A_key = mod_exp(Y, A_secret, n);

    long long B_key = mod_exp(X, B_secret, n);

    std::string result;
    if(B_key == A_key){
        result = "SUKCES!";
    }else{
        result = "PORAZKA";
    }

    std::cout<<"OSOBA A:\n"<<
    "\tx (tajna liczba calkowita)\t=\t" << A_secret <<
    "\n\tX (g^x mod n)\t\t\t=\t" << X <<
    "\n\tobliczony klucz k\t\t=\t" << A_key <<
    "\nOSOBA B\n" <<
    "\ty (tajna liczba calkowita)\t=\t" << B_secret <<
    "\n\tY (g^y mod n)\t\t\t=\t" << Y <<
    "\n\tk (obliczony klucz)\t\t=\t" << B_key <<
    "\nWYNIK: "<<result;
}