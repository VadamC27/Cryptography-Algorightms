#include "rsa.h"
#include "..\cryptography_utils.h"

#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <cmath>
#include <vector>

long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;

    return x1;
}

struct RSAkeys generate_RSA(){
    long long p = generate_prime(), q = generate_prime();
    
    return generate_RSA(p,q);
}

struct RSAkeys generate_RSA(long long p, long long q){
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    
    // generwoanie e
    long long e;

    long long d;
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1 && is_prime(e))
            break;
    }
    d = mod_inverse(e, phi);
       

    RSAkeys keys;
    keys.private_key.d = d;
    keys.private_key.n = n;
    keys.public_key.e = e;
    keys.public_key.n = n;
    
    return keys;
}

std::vector<long long> encrypt(PublicKey key, std::string message){
    std::vector<long long> encrypted_message;

    for(char ch : message){
        encrypted_message.push_back( ((long long) pow((long long) ch, key.e ) % key.n));
    }

    return encrypted_message;
}

std::string decrypt(PrivateKey key, std::vector<long long>& message){
    std::string decrypted_message = "";

    for(long long ch : message){
        decrypted_message +=  (char) mod_exp(ch, key.d,key.n ) % key.n;
    }

    return decrypted_message;
}

void print_RSA_menu(){
     std::cout<<" Choose method for key generation:\n 1. Generate random p and q\n 2. Enter custom p and q\nYour choice: ";
}

void print_RSA_message_menu(){
     std::cout<<" Chose message to encrypt:\n 1. Exemplary 50 chars: \"Test message for RSA abcdefghijklnmopqrstuwxyz1234\"\n 2. Enter custom message\nYour choice: ";
}



void RSAmessage_handler(RSAkeys keys){
    std::string message = "Test message for RSA abcdefghijklnmopqrstuwxyz1234";
    int choice;
    print_RSA_message_menu();
    do{
        std::cin>>choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice){
            case 1:{
                
                break;
            }
            case 2:{
                std::cout<<"Enter message: ";
                getline(std::cin, message);             
                  
                break;
            }
            default:{
                std::cout<<"Incorrect input, enter again: ";
                break;
            }
        }
    } while(choice != 1 && choice != 2);

    std::vector<long long> encrypted_message = encrypt(keys.public_key, message);

    std::string decrypted_message = decrypt(keys.private_key, encrypted_message);

    std::string result;

    if(message == decrypted_message){
        result = "SUCCESS!";
    }else{
        result = "FAILURE";
    }

    std::cout<<"Orginal message: " << message <<
    "\nEncrypted message: "; print_vector(encrypted_message); 
    std::cout<<"\nDecrypted message: " << decrypted_message <<
    "\nResult: " << result<<"\n";
}


void RSAmenu(){
    RSAkeys keys;
    int choice;
    print_RSA_menu();
    do{
        std::cin>>choice;
        switch (choice){
            case 1:{
                keys = generate_RSA();
                break;
            }
            case 2:{
                long long p,q;
                std::cout<<"Enter p: ";
                std::cin>>p;
                std::cout<<"Enter q: ";
                std::cin>>q;
                if(!is_prime(p)){
                    std::cout<<"p must be a prime number!!\n";
                    print_RSA_menu();                    
                    choice = -1;
                    break;
                }
                if(!is_prime(q)){
                    std::cout<<"q must be a prime number!!\n";
                    print_RSA_menu();
                    choice = -1;
                    break;
                }
                if(p < 1 || q<1){
                    std::cout<<"Enter positive p and q!\n";
                    print_RSA_menu();
                    
                    choice = -1;
                    break;
                }
                keys = generate_RSA(p,q);
    
                break;
            }
            default:{
                std::cout<<"Incorrect input, enter again: ";
                break;
            }
        }
    } while(choice != 1 && choice != 2);
    RSAmessage_handler(keys);
}
