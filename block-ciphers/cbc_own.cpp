#include <openssl/evp.h>
#include <openssl/rand.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>

void xor_bytes(const unsigned char* a, const unsigned char* b, unsigned char* result, int length) {
    for (int i = 0; i < length; ++i) {
        result[i] = a[i] ^ b[i];
    }
}

void encrypt_file_cbc_own(const std::string& inputFile, const std::string& outputFile, const std::string& key, const std::string& iv) {
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
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), NULL);

    const int bufferSize = 4096;
    unsigned char inBuffer[bufferSize], outBuffer[bufferSize];
    unsigned char xorBuffer[bufferSize];
    int bytesRead, bytesWritten;

    auto start = std::chrono::steady_clock::now();
    unsigned char tempIv[bufferSize];
    memcpy(tempIv, iv.data(), EVP_CIPHER_block_size(EVP_aes_256_ecb()));

    while ((bytesRead = inFile.read(reinterpret_cast<char*>(inBuffer), bufferSize).gcount()) > 0) {
        xor_bytes(inBuffer, tempIv, xorBuffer, bytesRead);

        EVP_EncryptUpdate(ctx, outBuffer, &bytesWritten, xorBuffer, bytesRead);
        outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);
        memcpy(tempIv, outBuffer, bytesWritten);
    }

    EVP_EncryptFinal_ex(ctx, outBuffer, &bytesWritten);
    outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);

    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Encrypt (own CBC): " << std::fixed << std::setprecision(4) << duration.count() * 1000 << " ms\t\t\tFile: " << inputFile <<"\n";
}

void decrypt_file_cbc_own(const std::string& inputFile, const std::string& outputFile, const std::string& key, const std::string& iv) {
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
    EVP_DecryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), NULL);

    const int bufferSize = 4096;
    unsigned char inBuffer[bufferSize], outBuffer[bufferSize];
    unsigned char xorBuffer[bufferSize];
    int bytesRead, bytesWritten;

    memcpy(reinterpret_cast<char*>(xorBuffer),reinterpret_cast<const unsigned char*>(iv.c_str()), sizeof(iv.c_str()));
   
    auto start = std::chrono::steady_clock::now();

    while ((bytesRead = inFile.read(reinterpret_cast<char*>(inBuffer), bufferSize).gcount()) > 0) {

        EVP_DecryptUpdate(ctx, outBuffer, &bytesWritten, inBuffer, bytesRead);

        xor_bytes(outBuffer, xorBuffer, xorBuffer, bytesRead);
        outFile.write(reinterpret_cast<char*>(xorBuffer), bytesWritten);

        memcpy(xorBuffer, inBuffer, bytesRead);
    }

    EVP_DecryptFinal_ex(ctx, outBuffer, &bytesWritten);
    outFile.write(reinterpret_cast<char*>(outBuffer), bytesWritten);

    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Decrypt (own CBC): " << std::fixed << std::setprecision(4) << duration.count() * 1000 << " ms\t\t\tFile: " << inputFile <<"\n";
}
