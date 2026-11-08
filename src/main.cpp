#include "crypto_lab/demo.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

int main(int argc, char*[]) {
    if (argc != 1) {
        std::cerr << "Uso: crypto_lab (sin argumentos)\n";
        return EXIT_FAILURE;
    }

    try {
        const auto result = crypto_lab::run_demo();
        const bool recovered = result.recovered == result.original;

        std::cout << "Laboratorio de ciberseguridad: AES-256-GCM en memoria\n"
                  << "Original ficticio: " << result.original << '\n'
                  << "Cifrado (hex):     " << result.ciphertext_hex << '\n'
                  << "Texto recuperado:  " << result.recovered << '\n'
                  << "Recuperacion:      " << (recovered ? "correcta" : "fallida") << '\n'
                  << "Cifrado alterado:  " << (result.tampering_rejected ? "rechazado" : "aceptado") << '\n';

        return recovered && result.tampering_rejected ? EXIT_SUCCESS : EXIT_FAILURE;
    } catch (const std::exception& error) {
        std::cerr << "No se pudo completar la demo: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
