# Guía del laboratorio

## Objetivo

Explicar por qué una víctima puede perder acceso a sus datos si no controla la clave de cifrado o no tiene una copia recuperable. El ejercicio separa ese problema de la **integridad**: la demo también comprueba si los datos cifrados fueron alterados.

## Qué observar en la demo

1. **Cifrado:** el programa toma una frase ficticia y la cifra con AES-256-GCM. Muestra el resultado en hexadecimal para poder leer los bytes en la consola.
2. **Recuperación:** el programa usa la misma clave para descifrar y compara el resultado con la frase original. La clave solo existe durante esa ejecución; esta recuperación es una demostración controlada.
3. **Integridad:** el programa cambia un bit en una copia del texto cifrado. Al verificar la etiqueta de autenticación, CNG detecta la modificación y rechaza el descifrado.

Repite la demo y compara el texto cifrado y el texto recuperado. Después, discute qué ocurriría si la organización no tuviera la clave o si la copia de respaldo estuviera al alcance del mismo usuario que perdió acceso a los datos. Propón una forma de verificar por adelantado que un respaldo independiente se puede restaurar.

Referencia: [Programación con Windows CNG y cifrado autenticado](https://learn.microsoft.com/en-us/windows/win32/seccng/typical-cng-programming).

## Entrega original

El commit `c017d8c` conserva el prototipo y sus ejercicios de Windows. Puedes consultar el árbol y leer el código sin cambiar de versión ni ejecutarlo:

```powershell
git ls-tree --name-only c017d8c
git show c017d8c:main.cpp
git show c017d8c:CryptoRansomware.cpp
```

| Archivo original | Papel en la entrega |
| --- | --- |
| `main.cpp` y `CryptoRansomware.*` | Localizaban archivos por extensión en el Escritorio, escribían copias cifradas e intentaban eliminar los originales. |
| `Encrypter.*` | Implementaban el cifrado de archivos con AES en modo CFB mediante Crypto++. La instancia reutilizaba el IV y el cifrado carecía de una etiqueta de autenticación. |
| `InfoSeeker.*` | Consultaban el nombre de usuario y contenían código para consultar la dirección MAC. |
| `RegistryModifier.*` y `main4.cpp` | Contenían utilidades y un ensayo aparte con el registro de Windows. El flujo principal no las invocaba. |
| `main2.cpp`, `main3.cpp` y `principal.cpp` | Eran ensayos separados de cifrado y descifrado. |

El proyecto de Visual Studio original también tenía rutas a Crypto++ específicas de la máquina del autor y pedía elevación en la configuración Release x64. La configuración actual usa CMake y la API criptográfica del SDK de Windows.
