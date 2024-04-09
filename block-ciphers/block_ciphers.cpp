#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <iomanip> 

#include "block_ciphers.h"
#include "cbc_own.h"

void encrypt_file_ctr(const std::string& inputFile, const std::string& outputFile, const std::string& key, const std::string& iv) {

    OpenSSL_add_all_algorithms();

    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: Cannot open input file " << inputFile << std::endl;
        return;
    }

    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Cannot open output file " << outputFile << std::endl;
        return;
    }
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), reinterpret_cast<const unsigned char*>(iv.c_str()));
    const int bufferSize = 4096;
    unsigned char inBuffer[bufferSize], outBuffer[bufferSize];
    int bytesRead, bytesWritten;

    auto start = std::chrono::steady_clock::now();

    while ((bytesRead = inFile.read(reinterpret_cast<char*>(inBuffer), bufferSize).gcount()) > 0) {
        EVP_EncryptUpdate(ctx, outBuffer, &bytesWritten, inBuffer, bytesRead);
        outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);
    }

    EVP_EncryptFinal_ex(ctx, outBuffer, &bytesWritten);
    outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);

    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Szyfrowanie (CTR): "<< std::fixed << std::setprecision(4) << duration.count() * 1000 << " ms\t\t\tPlik: " << inputFile <<"\n";
}


void decrypt_file_ctr(const std::string& inputFile, const std::string& outputFile, const std::string& key, const std::string& iv) {

    OpenSSL_add_all_algorithms();

    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: Cannot open input file " << inputFile << std::endl;
        return;
    }


    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Cannot open output file " << outputFile << std::endl;
        return;
    }
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), reinterpret_cast<const unsigned char*>(iv.c_str()));

    const int bufferSize = 4096;
    unsigned char inBuffer[bufferSize], outBuffer[bufferSize];
    int bytesRead, bytesWritten;

    auto start = std::chrono::steady_clock::now();

    while ((bytesRead = inFile.read(reinterpret_cast<char*>(inBuffer), bufferSize).gcount()) > 0) {
        EVP_DecryptUpdate(ctx, outBuffer, &bytesWritten, inBuffer, bytesRead);
        outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);
    }

    EVP_DecryptFinal_ex(ctx, outBuffer, &bytesWritten);
    outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);

    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Deszyfrowanie (CTR): " << std::fixed << std::setprecision(4) << duration.count() * 1000 << " ms\t\t\tPlik: " << inputFile <<"\n";
}


void encrypt_file_cbc(const std::string& inputFile, const std::string& outputFile, const std::string& key, const std::string& iv) {
    OpenSSL_add_all_algorithms();

    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: Cannot open input file " << inputFile << std::endl;
        return;
    }

    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Cannot open output file " << outputFile << std::endl;
        return;
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), reinterpret_cast<const unsigned char*>(iv.c_str()));

    const int bufferSize = 4096;
    unsigned char inBuffer[bufferSize], outBuffer[bufferSize];
    int bytesRead, bytesWritten;


    auto start = std::chrono::steady_clock::now();

    while ((bytesRead = inFile.read(reinterpret_cast<char*>(inBuffer), bufferSize).gcount()) > 0) {
        EVP_EncryptUpdate(ctx, outBuffer, &bytesWritten, inBuffer, bytesRead);
        outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);
    }


    EVP_EncryptFinal_ex(ctx, outBuffer, &bytesWritten);
    outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);

    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Szyfrowanie (CBC): " << std::fixed << std::setprecision(4) << duration.count() * 1000 << " ms\t\t\tPlik: " << inputFile <<"\n";
}


void decrypt_file_cbc(const std::string& inputFile, const std::string& outputFile, const std::string& key, const std::string& iv) {

    OpenSSL_add_all_algorithms();

    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: Cannot open input file " << inputFile << std::endl;
        return;
    }

    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Cannot open output file " << outputFile << std::endl;
        return;
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), reinterpret_cast<const unsigned char*>(iv.c_str()));
    const int bufferSize = 4096;
    unsigned char inBuffer[bufferSize], outBuffer[bufferSize];
    int bytesRead, bytesWritten;

    auto start = std::chrono::steady_clock::now();

    while ((bytesRead = inFile.read(reinterpret_cast<char*>(inBuffer), bufferSize).gcount()) > 0) {
        EVP_DecryptUpdate(ctx, outBuffer, &bytesWritten, inBuffer, bytesRead);
        outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);
    }


    EVP_DecryptFinal_ex(ctx, outBuffer, &bytesWritten);
    outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);

    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Deszyfrowanie (CBC): " << std::fixed << std::setprecision(4) << duration.count() * 1000 << " ms\t\t\tPlik: " << inputFile <<"\n";
}

void encrypt_file_ecb(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
   
    OpenSSL_add_all_algorithms();

    // Open input file
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: Cannot open input file " << inputFile << std::endl;
        return;
    }

    // Open output file
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Cannot open output file " << outputFile << std::endl;
        return;
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), NULL);

    const int bufferSize = 4096;
    unsigned char inBuffer[bufferSize], outBuffer[bufferSize];
    int bytesRead, bytesWritten;

    auto start = std::chrono::steady_clock::now();

    while ((bytesRead = inFile.read(reinterpret_cast<char*>(inBuffer), bufferSize).gcount()) > 0) {
        EVP_EncryptUpdate(ctx, outBuffer, &bytesWritten, inBuffer, bytesRead);
        outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);
    }

    EVP_EncryptFinal_ex(ctx, outBuffer, &bytesWritten);
    outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);

    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Szyfrowanie (ECB): " << std::fixed << std::setprecision(4) << duration.count() * 1000 << " ms\t\t\tPlik: " << inputFile <<"\n";
}

void decrypt_file_ecb(const std::string& inputFile, const std::string& outputFile, const std::string& key) {

    OpenSSL_add_all_algorithms();

    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: Cannot open input file " << inputFile << std::endl;
        return;
    }

    // Open output file
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Cannot open output file " << outputFile << std::endl;
        return;
    }
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), NULL);

    const int bufferSize = 4096;
    unsigned char inBuffer[bufferSize], outBuffer[bufferSize];
    int bytesRead, bytesWritten;

    auto start = std::chrono::steady_clock::now();

    while ((bytesRead = inFile.read(reinterpret_cast<char*>(inBuffer), bufferSize).gcount()) > 0) {
        EVP_DecryptUpdate(ctx, outBuffer, &bytesWritten, inBuffer, bytesRead);
        outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);
    }

    EVP_DecryptFinal_ex(ctx, outBuffer, &bytesWritten);
    outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout <<"Deszyfrowanie (ECB): " << std::fixed << std::setprecision(4) << duration.count() * 1000 << " ms\t\t\tPlik: " << inputFile <<"\n";
}


void test_cipher_blocks(){
    const char* input_filename = "block-ciphers/sample.txt";
    const char* output_filename_ecb_1 = "bin/output_ecb_1.bin";
    const char* output_filename_cbc_1 = "bin/output_cbc_1.bin";
    const char* output_filename_ctr_1 = "bin/output_ctr_1.bin";
    const char* output_filename_ecb_2 = "bin/output_ecb_2.bin";
    const char* output_filename_cbc_2 = "bin/output_cbc_2.bin";
    const char* output_filename_ctr_2 = "bin/output_ctr_2.bin";
    const char* output_filename_ecb_3 = "bin/output_ecb_3.bin";
    const char* output_filename_cbc_3 = "bin/output_cbc_3.bin";
    const char* output_filename_ctr_3 = "bin/output_ctr_3.bin";
    std::string key = "0123456789abcdef0123456789abcdef"; 
    std::string iv = "0123456789abcdef0123456789abcdef";
    OpenSSL_add_all_algorithms();

    encrypt_file_ecb(input_filename, output_filename_ecb_1, key);
    decrypt_file_ecb(output_filename_ecb_1, (const char *)"bin/decrypted_ecb_1.txt", key);
    encrypt_file_cbc(input_filename, output_filename_cbc_1, key, iv);
    decrypt_file_cbc(output_filename_cbc_1, (const char *)"bin/decrypted_cbc_1.txt", key, iv);
    encrypt_file_ctr(input_filename, output_filename_ctr_1, key, iv);
    decrypt_file_ctr(output_filename_ctr_1, (const char *)"bin/decrypted_ctr_1.txt", key, iv);


    input_filename = "block-ciphers/norm_hamlet.txt";


    encrypt_file_ecb(input_filename, output_filename_ecb_2, key);
    decrypt_file_ecb(output_filename_ecb_2, (const char *)"bin/decrypted_ecb_2.txt", key);
    encrypt_file_cbc(input_filename, output_filename_cbc_2, key, iv);
    decrypt_file_cbc(output_filename_cbc_2, (const char *)"bin/decrypted_cbc_2.txt", key, iv);
    encrypt_file_ctr(input_filename, output_filename_ctr_2, key, iv);
    decrypt_file_ctr(output_filename_ctr_2, (const char *)"bin/decrypted_ctr_2.txt", key, iv);


    input_filename = "block-ciphers/norm_wiki_en.txt";


    encrypt_file_ecb(input_filename, output_filename_ecb_3, key);
    decrypt_file_ecb(output_filename_ecb_3, (const char *)"bin/decrypted_ecb_3.txt", key);
    encrypt_file_cbc(input_filename, output_filename_cbc_3, key, iv);
    decrypt_file_cbc(output_filename_cbc_3, (const char *)"bin/decrypted_cbc_2.txt", key, iv);
    encrypt_file_ctr(input_filename, output_filename_ctr_3, key, iv);
    decrypt_file_ctr(output_filename_ctr_3, (const char *)"bin/decrypted_ctr_3.txt", key, iv);


    input_filename = "block-ciphers/sample_err.txt"; 
    std::cout<<"\nWersje pliku z wprowadzonym bledem przed szyfrowaniem:\n";
    encrypt_file_ecb(input_filename, (const char *) "bin/error_ecb.bin", key);
    encrypt_file_cbc(input_filename, (const char *) "bin/error_cbc.bin", key, iv);
    encrypt_file_ctr(input_filename, (const char *) "bin/error_ctr.bin", key, iv);

    std::cout<<"\nDeszyfrowanie pliku z wprowadzonym bledem w pliku binarnym:\n";
    decrypt_file_ecb((const char *)"block-ciphers/output_ecb_1_err.bin", (const char *)"bin/decrypted_ecb_err.txt", key);
    decrypt_file_cbc((const char *)"block-ciphers/output_cbc_1_err.bin", (const char *)"bin/decrypted_cbc_err.txt", key, iv);
    decrypt_file_ctr((const char *)"block-ciphers/output_ctr_1_err.bin", (const char *)"bin/decrypted_ctr_err.txt", key, iv);

    input_filename = "block-ciphers/sample.txt";

    std::cout<<"\nWlasna implementacja CBC na bazie ECB:\n";
    encrypt_file_cbc_own(input_filename, (const char *) "bin/output_cbc_1_own.bin", key, iv);
    decrypt_file_cbc_own((const char *)"bin/output_cbc_1_own.bin", (const char *)"bin/decrypted_cbc_own.txt", key, iv);

    EVP_cleanup();

    return;

}
