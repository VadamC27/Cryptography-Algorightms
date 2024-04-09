#include <stdio.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
//#include <openssl/sha3.h>
#include <cstring>
#include <iostream>
#include <chrono>

float hamming_distance(const unsigned char *hash1, const unsigned char *hash2, size_t hash_len) {
    float count = 0;
    for (size_t i = 0; i < hash_len; ++i) {
        unsigned char xor_result = hash1[i] ^ hash2[i];
        while (xor_result) {
            count += xor_result & 1;
            xor_result >>= 1;
        }
    }
    return count / (hash_len * 8); 
}


void check_probability(const char *algo_name,const unsigned char *input, size_t input_len){

    unsigned char hash_1[256], hash_2[256]; 
    size_t hash_len;

    if (strcmp(algo_name, "MD5") == 0) {
        MD5(input, input_len, hash_1);
        hash_len = MD5_DIGEST_LENGTH;
    } else if (strcmp(algo_name, "SHA1") == 0) {
        SHA1(input, input_len, hash_1);
        hash_len = SHA_DIGEST_LENGTH;
    } else if (strcmp(algo_name, "SHA256") == 0) {
        SHA256(input, input_len, hash_1);
        hash_len = SHA256_DIGEST_LENGTH;
    } else {
        printf("Unsupported algorithm.\n");
        return;
    }

    unsigned char input_diff[input_len];
    memcpy(input_diff, input, input_len);

    size_t rand_index = rand() % (input_len * 8); 
    size_t byte_index = rand_index / 8;
    size_t bit_index = rand_index % 8;
    input_diff[byte_index] ^= (1 << bit_index); 

    if (strcmp(algo_name, "MD5") == 0) {
        MD5(input_diff, input_len, hash_2);
    } else if (strcmp(algo_name, "SHA1") == 0) {
        SHA1(input_diff, input_len, hash_2);
    } else if (strcmp(algo_name, "SHA256") == 0) {
        SHA256(input_diff, input_len, hash_2);
    } 

    float difference = hamming_distance(hash_1, hash_2, hash_len);
    std::cout<<"Oryginalne slowo: "<< input <<"\nSlowo po zmianie jednego losowego bitu: " << input_diff <<
     "\nWartosc dla sprawdzenia krytrerium SAC w roznicy dwoch wynikow funkcji skrotu: " <<difference<<"\n";
}


void hash_and_print(const char *algo_name, const unsigned char *input, size_t input_len, bool msg, bool more_info) {
    unsigned char hash[256]; // SHA-3 can have a maximum hash size of 64 bytes
    unsigned char * digest;
    EVP_MD_CTX * mdctx;
    if (strcmp(algo_name, "MD5") == 0) {
        MD5(input, input_len, hash);
    } else if (strcmp(algo_name, "SHA1") == 0) {
        SHA1(input, input_len, hash);
    } else if (strcmp(algo_name, "SHA256") == 0) {
        SHA256(input, input_len, hash);
    } else  if (strcmp(algo_name, "SHA3") == 0) {
        //unsigned char * digest;
        mdctx = EVP_MD_CTX_create();
        const EVP_MD * algo = EVP_sha3_256();
        EVP_DigestInit_ex(mdctx, algo, NULL);
        EVP_DigestUpdate(mdctx, input, input_len);
        unsigned int digest_len = EVP_MD_size(algo);
        digest = (unsigned char *)OPENSSL_malloc(digest_len);
        EVP_DigestFinal_ex(mdctx, digest, &digest_len);

        memcpy(hash, digest, digest_len);
        memset(hash + digest_len, '\0', 256 - digest_len);
    } else {
        if(msg){printf("Invalid algorithm name.\n");}
        return;
    }
    if(msg){
       
        printf("%s hash: ", algo_name);
        for (size_t i = 0; i < strlen((const char *)hash); i++) {
            printf("%02x", hash[i]);
        }
        printf("\n");
        if(more_info){
            std::cout<<"Dlugosc ciagu wynikowego: "<< strlen((const char *)hash) << "\n";
        }
    }

    if(strcmp(algo_name, "SHA3")==0){
        OPENSSL_free(digest);
	    EVP_MD_CTX_destroy(mdctx);
    }
    return;
}

void hash_and_print(const char *algo_name, const unsigned char *input, size_t input_len, bool msg) {
    hash_and_print(algo_name, input, input_len, msg, false);
}


void hash_and_print(const char *algo_name, const unsigned char *input, size_t input_len) {
    hash_and_print(algo_name, input, input_len, true, false);
}

void hash_word(const unsigned char * text){
    std::cout<<"Funkcje skrotu dla slowa: \"" << text << "\"\n";
    hash_and_print("MD5", text, strlen((const char*)text), true, true);
    hash_and_print("SHA1", text, strlen((const char*)text), true, true);
    hash_and_print("SHA256", text, strlen((const char*)text), true, true);
    hash_and_print("SHA3", text, strlen((const char*)text), true, true);
}

void hash_speed_test(const unsigned char * text){
    std::cout<<"Funkcje skrotu oraz pomiar czasu wykonania dla slowa: \"" << text << "\"\n";

    auto start = std::chrono::high_resolution_clock::now();
    hash_and_print("MD5", text, strlen((const char*)text), false);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_MD5 = finish - start;
    std::cout << "MD5: czas wykoania: " << elapsed_MD5.count() * 1000  << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    hash_and_print("SHA1", text, strlen((const char*)text), false);
    finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_SHA1 = finish - start;
    std::cout << "SH1: czas wykoania: " << elapsed_SHA1.count() * 1000  << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    hash_and_print("SHA256", text, strlen((const char*)text), false);
    finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_SHA256 = finish - start;
    std::cout << "SHA256: czas wykoania: " << elapsed_SHA256.count() * 1000 << " ms\n";    

    start = std::chrono::high_resolution_clock::now();
    hash_and_print("SHA3", text, strlen((const char*)text), false);
    finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_SHA3_256 = finish - start;
    std::cout << "SHA3-256: czas wykoania: " << elapsed_SHA3_256.count() * 1000 << " ms\n";  

    std::cout<<"\n";
}


void check_probabilities(const unsigned char * text){
    check_probability("MD5", text, strlen((const char*)text));

    check_probability("SHA1", text, strlen((const char*)text));

    check_probability("SHA256", text, strlen((const char*)text));
}


void hash_functions_test(){    
    hash_speed_test((const unsigned char *) "kot");
    hash_speed_test((const unsigned char *) "kryptografia");    
    hash_speed_test((const unsigned char *) "podstawy_kryptografii");

    hash_word((const unsigned char *) "kot");
    hash_word((const unsigned char *) "kou");

    check_probabilities((const unsigned char *) "kot");
}