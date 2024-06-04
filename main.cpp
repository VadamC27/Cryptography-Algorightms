#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>

#include "pseudorandom-sequences-bbs/bbs.h"
#include "pseudorandom-sequences-bbs/bbs_tests.h"
#include "rsa-algorithm/rsa.h"
#include "dh-algorithm/dh.h"
#include "hash-functions/hash_tests.h"
#include "block-ciphers/block_ciphers.h"


enum algorithms{ BBS = 1, RSA, DH, HASH_FUNCTIONS, BLOCK_CIPHERS, FINISH, MAX_ALGORITHMS};

void printMenu(){
    std::cout<< 
    "\n-------------------\n" << 
    "Choose function: \n" <<
    " "<<BBS<<". BBS\n" <<
    " "<<RSA<<". RSA algorithm\n"<<
    " "<<DH<<". Diffie-Hellman algorithm\n"<<
    " "<<HASH_FUNCTIONS<<". Hash functions\n"<<
    " "<<BLOCK_CIPHERS<<". Block ciphers\n"<<
    " "<<FINISH<<". Quit\n"<< 
    "-------------------\n";
}

void handleMainMenu(){
    bool on = true;
    
    while(on){
        printMenu();
        int choice;
        do{
            std::cout<<"Your choice: ";
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
            case BLOCK_CIPHERS:{
                test_cipher_blocks();
                break;
            }
            case FINISH:{
                on = false;
                break;
            }
            default: {
                std::cout<<"Incorrect option... \n";
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
