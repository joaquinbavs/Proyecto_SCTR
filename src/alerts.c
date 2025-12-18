#include "alerts.h"
#include "pico/stdlib.h"

#define LED 25

void alerts_init(void) {
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 0);
}

// LED apagado
void alert_free(void) {
    gpio_put(LED, 0);
}

// Parpadeo lento
void alert_warning(void) {
    gpio_put(LED, 1);
    sleep_ms(500);
    gpio_put(LED, 0);
    sleep_ms(500);
}

// Parpadeo rápido
void alert_occupied(void) {
    gpio_put(LED, 1);
    sleep_ms(150);
    gpio_put(LED, 0);
    sleep_ms(150);
}

// Error: 3 parpadeos
void alert_error(void) {
    for (int i = 0; i < 3; i++) {
        gpio_put(LED, 1);
        sleep_ms(250);
        gpio_put(LED, 0);
        sleep_ms(250);
    }
}
