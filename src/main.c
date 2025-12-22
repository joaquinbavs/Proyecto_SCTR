#include "buzzer.h"
#include "hcsr04.h"
#include "led.h"
#include "logica_distancia.h"

#include <pico/stdlib.h>
#include <stdio.h>

#define BUZZER_GPIO 14
#define ECHO_GPIO 15
#define TRIG_GPIO 16

int main(void){
    stdio_init_all();

    led_init();
    sleep_ms(500);
    buzzer_init(BUZZER_GPIO);
    hc_sr04_init(TRIG_GPIO, ECHO_GPIO);

    while(true){
        float distance = hc_sr04_medicion_cm();
        uint32_t delay_ms = distance_to_delay_ms(distance);
        bool peligro = is_object_close(distance);

        printf("Distancia: %.2f cm, Delay: %u ms\n", distance, delay_ms);

        if(peligro){
            led_on();
            buzzer_on();
            sleep_ms(100);
        }
        else{
            led_toggle();
            buzzer_toggle();
            sleep_ms(delay_ms);
        }

        //if (2 * delay_ms < 1000) {
            //sleep_ms(1000 - 2 * delay_ms);
        //}

        // En lugar de hacer mediciones en función del valor de distancia anterior:
        sleep_ms(1000);
    }
    return 0;
}