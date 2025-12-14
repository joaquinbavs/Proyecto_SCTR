# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.13)
# Importar el SDK de la Raspberry
include(pico_sdk_import.cmake)
# Nombre del proyecto
project(bucle_principal)
# Inicializa las configuraciones del SDK
pico_sdk_init()
# Crea el ejecutable a partir del código fuente
add_executable(bucle_principal bucle_principal.c)
# Enlaza con la biblioteca estándar del SDK
target_link_libraries(bucle_principal pico_stdlib)
# Genera archivos .uf2, .bin y .elf al compilar
pico_add_extra_outputs(bucle_principal)
