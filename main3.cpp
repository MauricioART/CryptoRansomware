#include <files.h>
#include <modes.h>
#include <osrng.h>

#include <aes.h>
#include <fstream>
#include <iostream>
#include <array>

using aes_key_t = std::array<CryptoPP::byte, CryptoPP::AES::DEFAULT_KEYLENGTH>;
using aes_iv_t = std::array<CryptoPP::byte, CryptoPP::AES::BLOCKSIZE>;

void encrypt(const aes_key_t& key, const aes_iv_t& iv,
    const std::string& filename_in, const std::string& filename_out) {
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cipher{};
    cipher.SetKeyWithIV(key.data(), key.size(), iv.data());

    std::ifstream in{ filename_in, std::ios::binary };
    std::ofstream out{ filename_out, std::ios::binary };

    CryptoPP::FileSource{ in, /*pumpAll=*/true,
                         new CryptoPP::StreamTransformationFilter{
                             cipher, new CryptoPP::FileSink{out}} };
}

void decrypt(const aes_key_t& key, const aes_iv_t& iv,
    const std::string& filename_in, const std::string& filename_out) {
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cipher{};
    cipher.SetKeyWithIV(key.data(), key.size(), iv.data());

    std::ifstream in{ filename_in, std::ios::binary };
    std::ofstream out{ filename_out, std::ios::binary };

    CryptoPP::FileSource{ in, /*pumpAll=*/true,
                         new CryptoPP::StreamTransformationFilter{
                             cipher, new CryptoPP::FileSink{out}} };
}

int main(int argc, char** argv) {

    std::cout << CryptoPP::AES::BLOCKSIZE << std::endl;

  
    CryptoPP::AutoSeededRandomPool rng{};

    // Generate a random key
    aes_key_t key{};
    
    
    rng.GenerateBlock(key.data(), key.size());

    // Generate a random IV
    aes_iv_t iv{};
    rng.GenerateBlock(iv.data(), iv.size());

    // encrypt
    encrypt(key, iv, "abc.jpg", "abc_encrypted");

    // decrypt
    decrypt(key, iv, "abc_encrypted", "abc_decrypted.jpg");

    return 0;
}