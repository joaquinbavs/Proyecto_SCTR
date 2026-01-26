#include "led.h"
#include <pico/stdlib.h>
#include <hardware/gpio.h>

#define LED_GPIO 25  // Pin integrado de la Raspberry Pi Pico

static bool led_state = false;  // Estado actual del LED

void led_init(void) {
    gpio_init(LED_GPIO);
    gpio_set_dir(LED_GPIO, GPIO_OUT);
    gpio_put(LED_GPIO, 0);  // Apagado inicial
    led_state = false;
}

void led_on(void) {
    gpio_put(LED_GPIO, 1);
    led_state = true;
}

void led_off(void) {
    gpio_put(LED_GPIO, 0);
    led_state = false;
}

void led_toggle(void) {
    led_state = !led_state;
    gpio_put(LED_GPIO, led_state);
}
