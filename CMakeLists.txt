cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(sensor_proximidad)

pico_sdk_init()

add_executable(sensor_proximidad
    src/main.c
    src/hcsr04.c
    src/led.c
    src/logica_distancia.c
    src/buzzer.c
)

target_include_directories(sensor_proximidad PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Enlaza librerías
target_link_libraries(sensor_proximidad
    pico_stdlib
    hardware_gpio
    hardware_timer
)

# Habilita USB Serial y deshabilita UART si quieres
pico_enable_stdio_usb(sensor_proximidad 1)
pico_enable_stdio_uart(sensor_proximidad 0)

# Genera .uf2, .bin, .elf
pico_add_extra_outputs(sensor_proximidad)