#include <stdio.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
//#include <openssl/sha3.h>
#include <cstring>
#include <iostream>

void hash_and_print(const char *algo_name, const unsigned char *input, size_t input_len) {
    unsigned char hash[64]; // SHA-3 can have a maximum hash size of 64 bytes
    if (strcmp(algo_name, "MD5") == 0) {
        MD5(input, input_len, hash);
    } else if (strcmp(algo_name, "SHA1") == 0) {
        SHA1(input, input_len, hash);
    } else if (strcmp(algo_name, "SHA256") == 0) {
        SHA256(input, input_len, hash);
    } else  {
        printf("Invalid algorithm name.\n");
        return;
    }

    printf("%s hash: ", algo_name);
    for (size_t i = 0; i < strlen((const char *)hash); i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

void hash_word(const unsigned char * text){
    std::cout<<"Funkcje skrotu dla slowa: \"" << text << "\"\n";
    hash_and_print("MD5", text, strlen((const char*)text));
    hash_and_print("SHA1", text, strlen((const char*)text));
    hash_and_print("SHA256", text, strlen((const char*)text));
}


void hash_functions_test(){
    hash_word((const unsigned char *) "kot");
    hash_word((const unsigned char *) "kou");
}