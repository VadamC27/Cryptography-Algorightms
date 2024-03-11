#include <iostream>

#include "bbs_tests.h"

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
}