# CryptoRansomware Lab

Proyecto de clase de ciberseguridad sobre el impacto del ransomware en la disponibilidad de los datos y el papel de la recuperación. La demo de consola está escrita en C++ y usa AES-256-GCM para cifrar un texto ficticio en memoria, recuperarlo con la misma clave y comprobar que un cambio en el texto cifrado se detecta.

La demo usa una muestra fija, no acepta rutas y no accede a archivos personales, al registro de Windows ni a la red.

## Estructura

| Ruta | Contenido |
| --- | --- |
| [`src/main.cpp`](src/main.cpp) | Entrada de consola y presentación de los resultados. |
| [`src/demo.cpp`](src/demo.cpp) | Ejercicio con datos ficticios y la API criptográfica de Windows (CNG). |
| [`include/crypto_lab/demo.hpp`](include/crypto_lab/demo.hpp) | Interfaz entre el ejercicio y la consola. |
| [`CMakeLists.txt`](CMakeLists.txt) | Configuración de compilación y verificaciones con CTest. |
| [`docs/laboratorio.md`](docs/laboratorio.md) | Guía de clase y mapa de la entrega original. |

## Compilar y ejecutar

Requisitos: Windows 10 u 11, Visual Studio 2022 o sus Build Tools con la carga **Desarrollo para el escritorio con C++**, el SDK de Windows y CMake 3.20 o posterior disponible en `PATH`. Se usa la biblioteca `bcrypt` del SDK; no se necesita instalar Crypto++ ni ejecutar la demo como administrador.

Desde la raíz del repositorio, en PowerShell:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
.\build\Release\crypto_lab.exe
ctest --test-dir build -C Release --output-on-failure
```

La consola debe mostrar `Recuperacion: correcta` y `Cifrado alterado: rechazado`. El texto cifrado en hexadecimal cambia entre ejecuciones porque la demo genera una clave y un nonce nuevos. CTest verifica el resultado de la demo y que el ejecutable rechace argumentos.

## Entrega original

El prototipo de clase y sus experimentos se conservan en el commit `c017d8c`. Su punto de entrada recorría el Escritorio y eliminaba archivos originales después de cifrarlos. La [guía del laboratorio](docs/laboratorio.md#entrega-original) describe sus componentes y cómo consultar ese código como texto desde Git.
