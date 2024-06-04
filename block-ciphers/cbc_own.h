#ifndef CBC_OWN_H
#define CBC_OWN_H

#include "../cryptography_utils.h"
#include <ctime>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <cstring>

void decrypt_file_cbc_own(const std::string& inputFile, const std::string& outputFile, const std::string& key, const std::string& iv);
void encrypt_file_cbc_own(const std::string& inputFile, const std::string& outputFile, const std::string& key, const std::string& iv);

#endif /* CBC_OWN_H */