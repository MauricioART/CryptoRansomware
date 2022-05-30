#include "Encrypter.h"


Encrypter::Encrypter() {
    this->rng.GenerateBlock(key.data(), key.size());
    this->rng.GenerateBlock(iv.data(), iv.size());
}
/*
void Encrypter::encrypt(const aes_key_t& key, const aes_iv_t& iv,
    const std::string& filename_in, const std::string& filename_out) {
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cipher{};
    cipher.SetKeyWithIV(key.data(), key.size(), iv.data());

    std::ifstream in{ filename_in, std::ios::binary };
    std::ofstream out{ filename_out, std::ios::binary };

    CryptoPP::FileSource{ in, true,
                         new CryptoPP::StreamTransformationFilter{
                             cipher, new CryptoPP::FileSink{out}} };
}
void Encrypter::decrypt(const aes_key_t& key, const aes_iv_t& iv,
    const std::string& filename_in, const std::string& filename_out) {
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cipher{};
    cipher.SetKeyWithIV(key.data(), key.size(), iv.data());

    std::ifstream in{ filename_in, std::ios::binary };
    std::ofstream out{ filename_out, std::ios::binary };

    CryptoPP::FileSource{ in,true,
                         new CryptoPP::StreamTransformationFilter{
                             cipher, new CryptoPP::FileSink{out}} };
 }                            */

void Encrypter::encrypt(const std::string& filename_in, const std::string& filename_out) {
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cipher{};
    cipher.SetKeyWithIV(this->key.data(), this->key.size(), this->iv.data());

    std::ifstream in{ filename_in, std::ios::binary };
    std::ofstream out{ filename_out, std::ios::binary };

    CryptoPP::FileSource{ in, true,
                         new CryptoPP::StreamTransformationFilter{
                             cipher, new CryptoPP::FileSink{out}} };
}
void Encrypter::decrypt(const std::string& filename_in, const std::string& filename_out) {
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cipher{};
    cipher.SetKeyWithIV(this->key.data(), this->key.size(), this->iv.data());

    std::ifstream in{ filename_in, std::ios::binary };
    std::ofstream out{ filename_out, std::ios::binary };

    CryptoPP::FileSource{ in,true,
                         new CryptoPP::StreamTransformationFilter{
                             cipher, new CryptoPP::FileSink{out}} };
}