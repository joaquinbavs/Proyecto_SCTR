cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(bucle_principal C CXX ASM)

pico_sdk_init()

add_executable(bucle_principal
    src/bucle_principal.c
    src/hcsr04.c
    src/alerts.c
    src/parking_logic.c
)

target_include_directories(bucle_principal PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Enlaza librerías
target_link_libraries(bucle_principal
    pico_stdlib
)

# Habilita USB Serial y deshabilita UART si quieres
pico_enable_stdio_usb(bucle_principal 1)
pico_enable_stdio_uart(bucle_principal 0)

# Genera .uf2, .bin, .elf
pico_add_extra_outputs(bucle_principal)
