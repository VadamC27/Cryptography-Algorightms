#include <iostream>
#include <array>
#include <stdlib.h>
#include <stdio.h>

#include "bbs_tests.h"
#include "bbs.h"

void print_bbs_test_menu(){
    std::cout<<" Choose method for generating random sequence:\n 1. Generate random p and q\n 2. Enter p and q\nYour choice: ";
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
                std::cout<<"Enter p: ";
                std::cin>>p;
                std::cout<<"Enter q: ";
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
                std::cout<<"incorrect option, enter again: ";
                break;
            }
        }
    } while(choice != 1 && choice != 2);
    int passed = 0;
    std::cout<< "\n----- FIPS 140-2 TEST -----\n I. Single bit test.\n";
    if(numbers_test(sequence,true)) passed++;
    std::cout<< " II. Run test.\n";
    if(series_test(sequence,true)) passed++;
    std::cout<< " III. Long run test.\n";
    if(long_series_test(sequence,true)) passed++;
    std::cout<< " IV. Poker test.\n";
    if(poker_test(sequence,true)) passed++;
    std::cout<<"\nTESTS PASSED: "<< passed<<"/4\n";
    if(passed == 4 ){
        std::cout<<"\nALL RANDOMNESS TESTS PASSED!\n";
    }else{
        std::cout<<"\nNOT ALL RANDOMNESS TESTS PASSED! \n";
    }
    return; 
}

bool numbers_test(std::string sequence){
    return numbers_test(sequence, false);
}

bool numbers_test(std::string sequence, bool msg){
    int ones = 0, zeros = 0;
    bool result = false;
    for(char ch : sequence){
        if(ch == '0') zeros++;
        if(ch == '1') ones++;
    }
    if(ones > 9725 && ones < 10275) result = true;
    if(msg){
        std::cout<< "Number of zeroes: "<<zeros<<"\tNumber of ones: "<<ones<<"\n";
        if(result){
            std::cout<< "TEST: SUCCESS!\n";
        }else {
            std::cout<< "TEST: FAILED!\n";
        }
    }
    return result;
}

bool series_test(std::string sequence){
    return series_test(sequence, false);
}

bool series_test(std::string sequence, bool msg){
    int freqs[6] = {0}; //Number apparences of given sequences
    int top_val[6] = {2685, 1386, 723, 384, 209, 209}, bottom_val[6] = {2315, 1114, 527, 240, 103, 103};
    bool result = false;
    int current_streak = 0;
    char last_char = '-';
    int correct_freqs = 0;

    for(char ch : sequence){
        if(last_char == '1' && ch == '0'){
            
            if(current_streak >= 6) {
                freqs[5]++;
            }else{
                freqs[current_streak - 1]++;
            }
            current_streak = 0;
        }
        if(ch == '1') {
            current_streak++;            
        }
        last_char = ch;
    }

    for(int i = 0; i < 6 ; i++){
        if(freqs[i]>bottom_val[i] && freqs[i] < top_val[i]){
            correct_freqs++;
        }
        if(msg){
            std::cout<< "| " << i+1 << " | "<< bottom_val[i] << "\t<\t" << freqs[i] << "\t<\t" << top_val[i] << "\t| " << (freqs[i]>bottom_val[i] && freqs[i] < top_val[i]) << "\t|\n";
        }
    }
    if(correct_freqs == 6) result = true;

    if(msg){
        if(result){
            std::cout<< "TEST: SUCCESS!\n";
        }else {
            std::cout<< "TEST: FAILED!\n";
        }
    }
    return result;
}

bool long_series_test(std::string sequence){
    return long_series_test(sequence, false);
}

bool long_series_test(std::string sequence, bool msg){
  
    int current_streak = 0;
    char last_char = '-';

    for(char ch : sequence){
        if(last_char == ch){ 
            current_streak++;
            if(current_streak >= 26 ){
                if(msg){
                    std::cout<< "Found longer 26 char or longer sequence!\nTEST: FAILED!\n";
                }
                return false;
            }
        }else{
            current_streak = 1;
         
        }
        last_char = ch;
    }
    if(msg){
        std::cout<< "TEST:  SUCCESS!\n";
    }
    return true;

}

bool poker_test(std::string sequence){
    return poker_test(sequence, false);
}

bool poker_test(std::string sequence, bool msg){
    bool result = false;
    int freqs[16] = {0};

    for(int i = 0; i<20000; i+=4) {
        std::string binary_number = sequence.substr(i, 4);
   
        int number = strtoull(binary_number.c_str(),NULL,2);
        //std::cout<<sequence.substr(i, 4)<<" "<<strtoull(sequence.c_str(),NULL,2)<<" "<<number<<"\n";
        freqs[number]++;
    }
    double sqr_sum = 0;
    for(int i = 0; i<16; i++){
        sqr_sum += freqs[i] * freqs[i];
        if(msg){
            std::cout<<"|\t" << i << ":" << freqs[i] <<"\t\t|";
            if(i%4 == 3) std::cout<< "\n";
        }
    }
    //std::cout<<"sqr_sum: "<<sqr_sum<<"\n";
    double x = ( (16) *  (sqr_sum))/5000 - 5000;
    if(x>2.16 && x<46.17) result = true;

     if(msg){
        std::cout<< "x = " << x << " | 2.16 < x < 46.17  |";
        if(result){
            std::cout<< "TEST: SUCCESS!\n";
        }else {
            std::cout<< "TEST: FAILED!\n";
        }
    }
    return result;
}