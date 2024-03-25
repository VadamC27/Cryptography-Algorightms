#include "rsa.h"
#include "..\cryptography_utils.h"

#include <iostream>
#include <ctime>
#include <stdlib.h>


long long generate_prime(){
    long long number = 0;    
    do{
        number = 1000 + ( rand() % 9000 );
    } while(!check_prime(number));    
    return number;
}

void generate_RSA(){
    long long p = generate_prime(), q = generate_prime();
    generate_RSA(p,q);
    return;
}

void generate_RSA(long long p, long long q){
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    
    // generwoanie e
    long long e;
    do{
        

    }while(1!=gcd(e,phi));

}
