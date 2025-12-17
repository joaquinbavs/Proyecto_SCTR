#include <stdio.h>          // Para printf()
#include <stdbool.h>        // Para bool, true, false
#include "pico/stdlib.h"    // Funciones del SDK: stdio_init_all, sleep_ms, timing, etc.
#include "alerts.h"         // Declaraciones de alerts_init()
#include "parking_logic.h"   // Declaraciones de parking_init(), parking_update()
#include "hcsr04.h"         // Declaraciones de hcsr04_init(), hcsr04_update(), etc.

int main(void) {
    stdio_init_all();

    alerts_init();
    parking_init();
    hcsr04_init(2, 3);

    absolute_time_t last_measure = get_absolute_time();

    while (1) {

        if (absolute_time_diff_us(last_measure, get_absolute_time()) > 500000) {
            hcsr04_start_measurement();
            last_measure = get_absolute_time();
        }

        if (hcsr04_update()) {
            float d = hcsr04_get_distance_cm();
            parking_update(d, false);
            printf("Distancia: %.2f cm\n", d);
        }

        if (hcsr04_has_timeout()) {
            parking_update(0, true);
            printf("ERROR: Timeout sensor\n");
        }

        sleep_ms(10);
    }
}

