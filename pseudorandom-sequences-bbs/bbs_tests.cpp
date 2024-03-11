#include <iostream>

#include "bbs_tests.h"
#include "bbs.h"

void print_bbs_test_menu(){
    std::cout<<" Wybierz sposób generowania ciagu losowego:\n 1. Wygeneruj losowe p i q\n 2. Wybierz p i q\nTwoja opcja: ";
}

void bbs_test_menu(){
    std::string sequence = "";
    int choice;
    print_bbs_test_menu();
    do{
        std::cin>>choice;
        switch (choice){
            case 1:{
                sequence = generate_sequence(20000);
                break;
            }
            case 2:{
                long long p,q;
                std::cout<<"Podaj p: ";
                std::cin>>p;
                std::cout<<"Podaj q: ";
                std::cin>>q;
                sequence = generate_sequence(20000, p, q );
                if(sequence == "error"){
                    print_bbs_test_menu();
                    choice = -1;
                    break;
                }
                break;
            }
            default:{
                std::cout<<"Bledna opcja, wpisz ponownie: ";
                break;
            }
        }
    } while(choice != 1 || choice != 2);
    return; 
}

bool numbers_test(std::string sequence){
    return numbers_test(sequence, false);
}

bool numbers_test(std::string sequence, bool msg){
    int ones = 0, zeros = 0;
    for(char ch : sequence){
        if(ch == '0') zeros++;
        if(ch == '1') ones++;
    }
    if(msg){
        std::cout<< "Number of zeroes:\t"<<zeros<<"\tNumber of ones: "<<ones<<"\n";
    }
    return true;
}
