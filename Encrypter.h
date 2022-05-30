#pragma once
#include <files.h>
#include <modes.h>
#include <osrng.h>

#include <aes.h>
#include <fstream>
#include <iostream>
#include <array>

using aes_key_t = std::array<CryptoPP::byte, CryptoPP::AES::DEFAULT_KEYLENGTH>;
using aes_iv_t = std::array<CryptoPP::byte, CryptoPP::AES::BLOCKSIZE>;

class Encrypter
{
private:
    CryptoPP::AutoSeededRandomPool rng{};
    aes_key_t key{};
    aes_iv_t iv{};

public:

    aes_key_t getKey() { return this->key; }
    aes_iv_t getIv() { return this->iv; }

    Encrypter();

    /*void encrypt(const aes_key_t& key, const aes_iv_t& iv,
        const std::string& filename_in, const std::string& filename_out);
    void decrypt(const aes_key_t& key, const aes_iv_t& iv,
        const std::string& filename_in, const std::string& filename_out);*/
    void encrypt(const std::string& filename_in, const std::string& filename_out);
    void decrypt(const std::string& filename_in, const std::string& filename_out);


};

