#include "hcsr04.h"
#include <pico/stdlib.h>
#include <hardware/timer.h>
#include <hardware/gpio.h>

static uint trig_gpio;
static uint echo_gpio;

void hc_sr04_init(uint trig_pin, uint echo_pin) {
    trig_gpio = trig_pin;
    echo_gpio = echo_pin;

    gpio_init(trig_gpio);
    gpio_set_dir(trig_gpio, GPIO_OUT);
    gpio_put(trig_gpio, 0);
    sleep_ms(100); //Evitar que se quede a 1 el sensor, y bloquee el microprocesador.

    gpio_init(echo_gpio);
    gpio_set_dir(echo_gpio, GPIO_IN);
}

float hc_sr04_medicion_cm(void) {
    absolute_time_t start, end;
    uint64_t pulse_width;

    // Pulso TRIG
    gpio_put(trig_gpio, 0);
    sleep_us(2);
    gpio_put(trig_gpio, 1);
    sleep_us(10);
    gpio_put(trig_gpio, 0);

    // Esperar a que ECHO suba
    while (gpio_get(echo_gpio) == 0);

    start = get_absolute_time();

    // Esperar a que ECHO baje
    //while (gpio_get(echo_gpio) == 1);

    // Modificando el anterior while:
    while(gpio_get(echo_gpio) == 1) {
        if (absolute_time_diff_us(start, get_absolute_time()) > 50000) {
            break; // 50 ms máximo
            }
        }

    end = get_absolute_time();

    pulse_width = absolute_time_diff_us(start, end);

    // Velocidad del sonido ≈ 343 m/s
    // distancia = (tiempo_us * 0.0343) / 2
    return (pulse_width * 0.0343f) / 2.0f;
}