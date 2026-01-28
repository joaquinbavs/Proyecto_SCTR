#include "buzzer.h"
#include "hcsr04.h"
#include "led.h"
#include "logica_distancia.h"

#include <pico/stdlib.h>
#include <stdio.h>

#define BUZZER_GPIO 19
#define ECHO_GPIO 20
#define TRIG_GPIO 21

int main(void){
    stdio_init_all();

    led_init();
    buzzer_init(BUZZER_GPIO);
    hc_sr04_init(TRIG_GPIO, ECHO_GPIO);

    while(true){
        float distance = hc_sr04_medicion_cm();
        uint32_t delay_ms = distance_to_delay_ms(distance);

        printf("Distancia: %.2f cm, Delay: %u ms\n", distance, delay_ms);

        led_on();
        buzzer_on();
        //sleep_ms(delay_ms);

        //led_off();
        //buzzer_off();
        //sleep_ms(delay_ms);

        if (2 * delay_ms < 1000) {
            sleep_ms(1000 - 2 * delay_ms);
        }
    }
    return 0;
}
