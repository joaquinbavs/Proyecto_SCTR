#include "alerts.h"
#include "pico/stdlib.h"

#define LED_GREEN 16
#define LED_RED 17

void alerts_init(void) {
    gpio_init(LED_GREEN);
    gpio_init(LED_RED);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_RED, 0);
}

void alert_free(void) {
    gpio_put(LED_GREEN, 1);
    gpio_put(LED_RED, 0);
}

void alert_warning(void) {
    gpio_put(LED_GREEN, 1);
    gpio_put(LED_RED, 1);
}

void alert_occupied(void) {
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_RED, 1);
}

void alert_error(void) {
    // Parpadeo LED rojo como ejemplo
    for (int i = 0; i < 3; i++) {
        gpio_put(LED_RED, 1);
        sleep_ms(250);
        gpio_put(LED_RED, 0);
        sleep_ms(250);
    }
}
