#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>

#include "pseudorandom-sequences-bbs/bbs.h"
#include "pseudorandom-sequences-bbs/bbs_tests.h"

int main()
{
    srand(time(NULL));
    generateSequence(20000);
    return 0;
}