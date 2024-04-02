#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>

#include "pseudorandom-sequences-bbs/bbs.h"
#include "pseudorandom-sequences-bbs/bbs_tests.h"
#include "rsa-algorithm/rsa.h"
#include "dh-algorithm/dh.h"
#include "hash-functions/hash_tests.h"


enum algorithms{ BBS = 1, RSA, DH, HASH_FUNCTIONS, FINISH, MAX_ALGORITHMS};

void printMenu(){
    std::cout<< 
    "\n-------------------\n" << 
    "Wybierz zadanie: \n" <<
    " "<<BBS<<". BBS\n" <<
    " "<<RSA<<". Algorytm RSA\n"<<
    " "<<DH<<". Algorytm Diffiego-Hellmana\n"<<
    " "<<HASH_FUNCTIONS<<". Funkcje skrotu\n"<<
    " "<<FINISH<<". Wyjdz\n"<< 
    "-------------------\n";
}

void handleMainMenu(){
    bool on = true;
    
    while(on){
        printMenu();
        int choice;
        do{
            std::cout<<"Twoj wybor: ";
            std::cin>>choice;
            switch (choice){
            case BBS:{
                bbs_test_menu();
                break;
            }
            case RSA:{
                RSAmenu();
                break;
            }
            case DH:{
                DHalgorithm();
                break;
            }
            case HASH_FUNCTIONS:{
                hash_functions_test();
                break;
            }
            case FINISH:{
                on = false;
                break;
            }
            default: {
                std::cout<<"Bledna opcja... \n";
                break;
            }
        }
        }while(!(choice < MAX_ALGORITHMS && choice >= BBS));

        
    }
}

int main()
{
    srand(time(NULL));
   
    handleMainMenu();

    return 0;
}
