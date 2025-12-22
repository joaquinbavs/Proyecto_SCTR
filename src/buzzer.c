#include "buzzer.h"
#include <pico/stdlib.h>
#include <hardware/gpio.h>

static uint buzzer_gpio;   // Solo visible dentro de este módulo
static bool state = false; // Estado actual del buzzer

void buzzer_init(uint pin) {
    buzzer_gpio = pin;
    gpio_init(buzzer_gpio);
    gpio_set_dir(buzzer_gpio, GPIO_OUT);
    gpio_put(buzzer_gpio, 0); // Apagado al inicio
}

void buzzer_on(void) {
    gpio_put(buzzer_gpio, 1);
    state = true;
}

void buzzer_off(void) {
    gpio_put(buzzer_gpio, 0);
    state = false;
}

void buzzer_toggle(void) {
    state = !state;
    gpio_put(buzzer_gpio, state);
}
