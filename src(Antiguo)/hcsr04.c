#include "hcsr04.h"               // Declaraciones públicas del módulo HC-SR04
#include <pico/stdlib.h>          // Funciones básicas del SDK Pico (sleep, tipos, tiempo)
#include <hardware/timer.h>       // Funciones de temporización de alta resolución
#include <hardware/gpio.h>        // Control de GPIO a bajo nivel

static uint trig_gpio;            // GPIO usado para el pin TRIG del HC-SR04
                                 // static → visible solo dentro de este archivo

static uint echo_gpio;            // GPIO usado para el pin ECHO del HC-SR04

void hc_sr04_init(uint trig_pin, uint echo_pin) {
    trig_gpio = trig_pin;         // Guarda el pin TRIG
    echo_gpio = echo_pin;         // Guarda el pin ECHO

    gpio_init(trig_gpio);         // Inicializa el GPIO TRIG
    gpio_set_dir(trig_gpio, GPIO_OUT);
                                 // Configura TRIG como salida
    gpio_put(trig_gpio, 0);       // Asegura TRIG en bajo al inicio

    gpio_init(echo_gpio);         // Inicializa el GPIO ECHO
    gpio_set_dir(echo_gpio, GPIO_IN);
                                 // Configura ECHO como entrada
}

float hc_sr04_medicion_cm(void) {
    absolute_time_t start, end;   // Tiempos de inicio y fin del pulso ECHO
    uint64_t pulse_width;         // Duración del pulso ECHO en microsegundos

    // ---------- Generación del pulso TRIG ---------
    gpio_put(trig_gpio, 0);       // Asegura TRIG en bajo
    sleep_us(2);                  // Espera 2 µs (estabilización)
    gpio_put(trig_gpio, 1);       // Activa TRIG
    sleep_us(10);                 // Pulso de 10 µs (requisito del HC-SR04)
    gpio_put(trig_gpio, 0);       // Finaliza el pulso TRIG

    // ---------- Espera a que ECHO suba ---------
    while (gpio_get(echo_gpio) == 0);
    // Bloquea la ejecución hasta que ECHO pase a nivel alto
    // Indica que el ultrasonido fue emitido y regresó

    start = get_absolute_time();  // Guarda el tiempo cuando ECHO se pone en alto

    // ---------- Espera a que ECHO baje ---------
    while (gpio_get(echo_gpio) == 1);
    // Bloquea hasta que ECHO vuelva a nivel bajo
    // Marca el final del pulso

    end = get_absolute_time();    // Guarda el tiempo cuando ECHO baja

    // Calcula la duración del pulso ECHO en microsegundos
    pulse_width = absolute_time_diff_us(start, end);

    // Velocidad del sonido ≈ 343 m/s → 0.0343 cm/µs
    // La señal recorre ida y vuelta, por eso se divide entre 2
    return (pulse_width * 0.0343f) / 2.0f;
}
