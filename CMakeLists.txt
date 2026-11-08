cmake_minimum_required(VERSION 3.20)
project(CryptoRansomwareLab LANGUAGES CXX)

if(NOT WIN32)
    message(FATAL_ERROR "La demo usa la API criptografica de Windows (CNG).")
endif()

add_executable(crypto_lab src/main.cpp src/demo.cpp)
target_include_directories(crypto_lab PRIVATE include)
target_compile_features(crypto_lab PRIVATE cxx_std_17)
target_compile_definitions(crypto_lab PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
target_link_libraries(crypto_lab PRIVATE bcrypt)

if(MSVC)
    target_compile_options(crypto_lab PRIVATE /W4 /permissive-)
endif()

include(CTest)
if(BUILD_TESTING)
    add_test(NAME demo_recuperacion_e_integridad COMMAND crypto_lab)
    add_test(NAME demo_rechaza_argumentos COMMAND crypto_lab muestra.txt)
    set_tests_properties(demo_rechaza_argumentos PROPERTIES WILL_FAIL TRUE)
endif()
