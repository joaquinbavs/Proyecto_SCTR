#include "hcsr04.h"               // Declaraciones públicas del módulo HC-SR04
#include <pico/stdlib.h>          // Funciones básicas del SDK Pico (sleep, tiempo)
#include <hardware/timer.h>       // Temporización de alta resolución
#include <hardware/gpio.h>        // Control directo de GPIO

static uint trig_gpio;            // GPIO asignado al pin TRIG del HC-SR04
                                 // static → encapsulado en este módulo

static uint echo_gpio;            // GPIO asignado al pin ECHO del HC-SR04

void hc_sr04_init(uint trig_pin, uint echo_pin) {
    trig_gpio = trig_pin;         // Guarda el pin TRIG
    echo_gpio = echo_pin;         // Guarda el pin ECHO

    gpio_init(trig_gpio);         // Inicializa el GPIO TRIG
    gpio_set_dir(trig_gpio, GPIO_OUT);
                                 // Configura TRIG como salida
    gpio_put(trig_gpio, 0);       // Fuerza TRIG a nivel bajo

    sleep_ms(100);                // Espera 100 ms para evitar estados indeterminados
                                 // del sensor que podrían dejar ECHO en alto
                                 // y bloquear el microcontrolador

    gpio_init(echo_gpio);         // Inicializa el GPIO ECHO
    gpio_set_dir(echo_gpio, GPIO_IN);
                                 // Configura ECHO como entrada
}

float hc_sr04_medicion_cm(void) {
    absolute_time_t start, end;   // Marcas de tiempo para medir el pulso ECHO
    uint64_t pulse_width;         // Duración del pulso ECHO en microsegundos

    // ---------- Generación del pulso TRIG ----------
    gpio_put(trig_gpio, 0);       // Asegura TRIG en bajo
    sleep_us(2);                  // Retardo mínimo de estabilización
    gpio_put(trig_gpio, 1);       // Activa TRIG
    sleep_us(10);                 // Pulso de 10 µs (requerido por HC-SR04)
    gpio_put(trig_gpio, 0);       // Finaliza el pulso TRIG

    // ---------- Esperar a que ECHO suba ----------
    while (gpio_get(echo_gpio) == 0);
    // Bloquea hasta que ECHO pase a nivel alto
    // Indica que el ultrasonido ha sido emitido

    start = get_absolute_time();  // Marca el inicio del pulso ECHO

    // ---------- Esperar a que ECHO baje ----------
    // Versión original (bloqueante):
    // while (gpio_get(echo_gpio) == 1);

    // Versión modificada con timeout:
    while (gpio_get(echo_gpio) == 1) {
        // Si el pulso dura más de 50 ms, se sale del bucle
        if (absolute_time_diff_us(start, get_absolute_time()) > 50000) {
            break;                // Evita bloqueo infinito del microcontrolador
        }
    }

    end = get_absolute_time();    // Marca el final del pulso ECHO

    // Calcula la duración del pulso en microsegundos
    pulse_width = absolute_time_diff_us(start, end);

    // Velocidad del sonido ≈ 343 m/s ≈ 0.0343 cm/µs
    // El sonido recorre ida y vuelta, por eso se divide entre 2
    return (pulse_width * 0.0343f) / 2.0f;
}
