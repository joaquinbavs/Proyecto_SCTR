#include "buzzer.h"              // Declaraciones públicas del módulo buzzer
#include <pico/stdlib.h>         // Tipos básicos y utilidades del SDK Pico
#include <hardware/gpio.h>       // Control de GPIO a bajo nivel

static uint buzzer_gpio;         // Número de GPIO usado por el buzzer
                                 // static → solo visible dentro de este archivo (encapsulación)

static bool state = false;       // Estado actual del buzzer (encendido/apagado)
                                 // Se usa para poder hacer toggle sin leer el GPIO

void buzzer_init(uint pin) {
    buzzer_gpio = pin;           // Guarda el pin asignado al buzzer
    gpio_init(buzzer_gpio);      // Inicializa el GPIO
    gpio_set_dir(buzzer_gpio, GPIO_OUT);
                                 // Configura el GPIO como salida
    gpio_put(buzzer_gpio, 0);    // Apaga el buzzer al iniciar
}

void buzzer_on(void) {
    gpio_put(buzzer_gpio, 1);    // Pone el GPIO a nivel alto → buzzer encendido
    state = true;                // Actualiza el estado interno
}

void buzzer_off(void) {
    gpio_put(buzzer_gpio, 0);    // Pone el GPIO a nivel bajo → buzzer apagado
    state = false;               // Actualiza el estado interno
}

void buzzer_toggle(void) {
    state = !state;              // Invierte el estado lógico del buzzer
    gpio_put(buzzer_gpio, state);
                                 // Aplica el nuevo estado al GPIO
}
