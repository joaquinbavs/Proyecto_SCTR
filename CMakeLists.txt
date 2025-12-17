cmake_minimum_required(VERSION 3.13)

# Importa el SDK de la Raspberry Pi Pico
include(pico_sdk_import.cmake)

# Nombre del proyecto
project(bucle_principal C CXX ASM)

# Inicializa el SDK
pico_sdk_init()

# Crea el ejecutable con TODOS los fuentes
add_executable(bucle_principal
    src/bucle_principal.c
    src/hcsr04.c
    src/alerts.c
    src/parking_logic.c
)

# Carpeta de headers
target_include_directories(bucle_principal PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Enlaza con la librería estándar del Pico
target_link_libraries(bucle_principal
    pico_stdlib
)

# Genera .uf2, .bin, .elf
pico_add_extra_outputs(bucle_principal)
