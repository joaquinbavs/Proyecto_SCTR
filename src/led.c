#include "led.h"                 // Declaraciones de las funciones públicas del módulo LED
#include <pico/stdlib.h>         // Tipos básicos y utilidades del SDK Pico
#include <hardware/gpio.h>       // Funciones de bajo nivel para manejar GPIO

#define LED_GPIO 25              // GPIO 25: LED integrado de la Raspberry Pi Pico

static bool led_state = false;   // Variable estática que guarda el estado actual del LED
                                 // static → solo visible dentro de este archivo (encapsulación)

void led_init(void) {
    gpio_init(LED_GPIO);         // Inicializa el GPIO 25
    gpio_set_dir(LED_GPIO, GPIO_OUT);
                                 // Configura el GPIO como salida
    gpio_put(LED_GPIO, 0);       // Apaga el LED al inicio (nivel lógico bajo)
    led_state = false;           // Sincroniza la variable de estado con el hardware
}

void led_on(void) {
    gpio_put(LED_GPIO, 1);       // Pone el GPIO a nivel alto → LED encendido
    led_state = true;            // Actualiza el estado interno del LED
}

void led_off(void) {
    gpio_put(LED_GPIO, 0);       // Pone el GPIO a nivel bajo → LED apagado
    led_state = false;           // Actualiza el estado interno del LED
}

void led_toggle(void) {
    led_state = !led_state;      // Invierte el estado lógico del LED
    gpio_put(LED_GPIO, led_state);
                                 // Escribe el nuevo estado en el GPIO
}
