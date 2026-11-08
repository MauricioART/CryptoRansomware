#include "crypto_lab/demo.hpp"

#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS
#include <ntstatus.h>
#include <bcrypt.h>

#include <array>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace crypto_lab {
namespace {

struct KeyMaterial {
    std::array<UCHAR, 32> bytes{};
    ~KeyMaterial() { SecureZeroMemory(bytes.data(), bytes.size()); }
};

struct EncryptedSample {
    std::array<UCHAR, 12> nonce{};
    std::array<UCHAR, 16> tag{};
    std::string ciphertext;
};

void check(NTSTATUS status, const char* operation) {
    if (status < 0) {
        std::ostringstream message;
        message << operation << " (0x" << std::hex << static_cast<ULONG>(status) << ')';
        throw std::runtime_error(message.str());
    }
}

auto make_provider() {
    BCRYPT_ALG_HANDLE handle = nullptr;
    check(BCryptOpenAlgorithmProvider(&handle, BCRYPT_AES_ALGORITHM, nullptr, 0),
          "BCryptOpenAlgorithmProvider");

    const auto close = [](void* provider) { BCryptCloseAlgorithmProvider(provider, 0); };
    std::unique_ptr<void, decltype(close)> provider(handle, close);
    wchar_t mode[] = BCRYPT_CHAIN_MODE_GCM;
    check(BCryptSetProperty(provider.get(), BCRYPT_CHAINING_MODE,
                            reinterpret_cast<PUCHAR>(mode), static_cast<ULONG>(sizeof(mode)), 0),
          "BCryptSetProperty");
    return provider;
}

auto make_key(BCRYPT_ALG_HANDLE provider) {
    KeyMaterial secret;
    check(BCryptGenRandom(nullptr, secret.bytes.data(), static_cast<ULONG>(secret.bytes.size()),
                         BCRYPT_USE_SYSTEM_PREFERRED_RNG), "BCryptGenRandom (clave)");

    BCRYPT_KEY_HANDLE handle = nullptr;
    check(BCryptGenerateSymmetricKey(provider, &handle, nullptr, 0, secret.bytes.data(),
                                    static_cast<ULONG>(secret.bytes.size()), 0),
          "BCryptGenerateSymmetricKey");
    const auto destroy = [](void* key) { BCryptDestroyKey(key); };
    return std::unique_ptr<void, decltype(destroy)>(handle, destroy);
}

BCRYPT_AUTHENTICATED_CIPHER_MODE_INFO auth_info(EncryptedSample& sample) {
    BCRYPT_AUTHENTICATED_CIPHER_MODE_INFO info;
    BCRYPT_INIT_AUTH_MODE_INFO(info);
    info.pbNonce = sample.nonce.data();
    info.cbNonce = static_cast<ULONG>(sample.nonce.size());
    info.pbTag = sample.tag.data();
    info.cbTag = static_cast<ULONG>(sample.tag.size());
    return info;
}

EncryptedSample encrypt_sample(BCRYPT_KEY_HANDLE key, std::string plaintext) {
    EncryptedSample sample;
    check(BCryptGenRandom(nullptr, sample.nonce.data(), static_cast<ULONG>(sample.nonce.size()),
                         BCRYPT_USE_SYSTEM_PREFERRED_RNG), "BCryptGenRandom (nonce)");

    auto info = auth_info(sample);
    const auto size = static_cast<ULONG>(plaintext.size());
    sample.ciphertext.resize(size);
    ULONG written = 0;
    check(BCryptEncrypt(key, reinterpret_cast<PUCHAR>(plaintext.data()), size, &info, nullptr, 0,
                        reinterpret_cast<PUCHAR>(sample.ciphertext.data()), size, &written, 0),
          "BCryptEncrypt");
    sample.ciphertext.resize(written);
    return sample;
}

NTSTATUS decrypt_sample(BCRYPT_KEY_HANDLE key, EncryptedSample sample, std::string& recovered) {
    auto info = auth_info(sample);
    const auto size = static_cast<ULONG>(sample.ciphertext.size());
    std::string output(size, '\0');
    ULONG written = 0;
    const NTSTATUS status = BCryptDecrypt(key, reinterpret_cast<PUCHAR>(sample.ciphertext.data()),
                                          size, &info, nullptr, 0,
                                          reinterpret_cast<PUCHAR>(output.data()), size, &written, 0);
    if (status >= 0) {
        recovered.assign(output.data(), written);
    }
    return status;
}

std::string to_hex(const std::string& bytes) {
    constexpr char digits[] = "0123456789abcdef";
    std::string hex;
    hex.reserve(bytes.size() * 2);
    for (char value : bytes) {
        const auto byte = static_cast<unsigned char>(value);
        hex.push_back(digits[byte >> 4]);
        hex.push_back(digits[byte & 0x0f]);
    }
    return hex;
}

}  // namespace

DemoResult run_demo() {
    const auto provider = make_provider();
    const auto key = make_key(provider.get());
    DemoResult result{"Inventario ficticio: 3 equipos de laboratorio.", {}, {}, false};

    auto sample = encrypt_sample(key.get(), result.original);
    if (sample.ciphertext.size() != result.original.size()) {
        throw std::runtime_error("El cifrado produjo una longitud inesperada");
    }
    result.ciphertext_hex = to_hex(sample.ciphertext);
    check(decrypt_sample(key.get(), sample, result.recovered), "BCryptDecrypt");

    // Change one bit and verify that authentication, specifically, rejects it.
    sample.ciphertext.front() ^= 1;
    std::string discarded;
    const auto status = decrypt_sample(key.get(), sample, discarded);
    if (status == STATUS_AUTH_TAG_MISMATCH) {
        result.tampering_rejected = true;
    } else {
        check(status, "BCryptDecrypt (cifrado alterado)");
    }
    return result;
}

}  // namespace crypto_lab
