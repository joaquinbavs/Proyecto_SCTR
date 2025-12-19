#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "alerts.h"
#include "parking_logic.h"
#include "hcsr04.h"

int main(void) {
    stdio_init_all();

    alerts_init();
    parking_init();
    hcsr04_init(16, 15);
    float distance;
    sleep_ms(2000);

    while (1) {
        // Actualizar la distancia (ajusta según tu API real)
        distance = hcsr04_update();

        // Mostrar distancia por pantalla
        printf("Distancia: %.2f cm\n", distance);
	fflush(stdout);
        // Lógica de alertas
        if (distance < 0) {
            alert_error();
        } else if (distance < 50) {
            alert_occupied();
        } else if (distance < 100) {
            alert_warning();
        } else {
            alert_free();
        }

        sleep_ms(500); // Evita saturar la consola
    }
}

