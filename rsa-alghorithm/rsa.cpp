#include "rsa.h"
#include "..\cryptography_utils.h"

#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <cmath>
#include <vector>


long long generate_prime(){
    long long number = 0;    
    do{
        number = 1000 + ( rand() % 9000 );
    } while(!is_prime(number));    
    return number;
}

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

    // Make x1 positive
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
     std::cout<<" Wybierz sposob generowania klucza:\n 1. Wygeneruj losowe p i q\n 2. Wybierz p i q\nTwoja opcja: ";
}

void print_RSA_message_menu(){
     std::cout<<" Wybierz wiadomosc:\n 1. Przykladowa wiadomosc 50 znakowa: \"Testowa wiadomosc dla RSA abcdefghijklnmopqrstuwxyz\"\n 2. Wypisz wiadomosc\nTwoja opcja: ";
}



void RSAmessage_handler(RSAkeys keys){
    std::string message = "Testowa wiadomosc dla RSA abcdefghijklnmopqrstuwxyz";
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
                std::cout<<"Podaj wiadomosc: ";
                getline(std::cin, message);             
                  
                break;
            }
            default:{
                std::cout<<"Bledna opcja, wpisz ponownie: ";
                break;
            }
        }
    } while(choice != 1 && choice != 2);

    std::vector<long long> encrypted_message = encrypt(keys.public_key, message);

    std::string decrypted_message = decrypt(keys.private_key, encrypted_message);

    std::string result;

    if(message == decrypted_message){
        result = "SUKCES!";
    }else{
        result = "PORAZKA";
    }

    std::cout<<"Wiadomosc oryginalna: " << message <<
    "\nWiadomosc po zaszyfrowaniu: "; print_vector(encrypted_message); 
    std::cout<<"\nWiadomosc po deszyfrowaniu: " << decrypted_message <<
    "\nWynik dzialania algorytmu: " << result<<"\n";
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
                std::cout<<"Podaj p: ";
                std::cin>>p;
                std::cout<<"Podaj q: ";
                std::cin>>q;
                if(!is_prime(p)){
                    std::cout<<"p nie jest liczba pierwsza!!\n";
                    print_RSA_menu();                    
                    choice = -1;
                    break;
                }
                if(!is_prime(q)){
                    std::cout<<"q nie jest liczba pierwsza!!\n";
                    print_RSA_menu();
                    choice = -1;
                    break;
                }
                if(p < 1 || q<1){
                    std::cout<<"Podaj dodatnie p i q!\n";
                    print_RSA_menu();
                    
                    choice = -1;
                    break;
                }
                keys = generate_RSA(p,q);
    
                break;
            }
            default:{
                std::cout<<"Bledna opcja, wpisz ponownie: ";
                break;
            }
        }
    } while(choice != 1 && choice != 2);
    RSAmessage_handler(keys);
}
