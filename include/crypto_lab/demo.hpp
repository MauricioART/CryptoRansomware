#pragma once

#include <string>

namespace crypto_lab {

struct DemoResult {
    std::string original;
    std::string ciphertext_hex;
    std::string recovered;
    bool tampering_rejected;
};

// Runs a fixed exercise entirely in memory, using a fresh key each time.
DemoResult run_demo();

}  // namespace crypto_lab
