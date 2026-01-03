#include "buzzer.h"
#include "hcsr04.h"
#include "led.h"
#include "logica_distancia.h"

#include <pico/stdlib.h>
#include <stdio.h>

#define BUZZER_GPIO 14
#define ECHO_GPIO 15
#define TRIG_GPIO 16

#define LOOP_CICLO 100
static uint32_t blink_phase_ms = 0;
static uint32_t measure_phase_ms = 0;

int main(void){
    stdio_init_all();

    sleep_ms(1000);

    led_init();
    buzzer_init(BUZZER_GPIO);
    hc_sr04_init(TRIG_GPIO, ECHO_GPIO);

    led_on();
    buzzer_on();
    sleep_ms(250); //Parpadeo de comprobación que se ejecutó correctamente el código.

    led_off();
    buzzer_off();

    float     distance   = 0.0f;
    uint32_t  delay_ms   = 0;
    bool      peligro    = false;
    bool      peligro_prev = false;

    absolute_time_t  next_tick = delayed_by_ms(get_absolute_time(), LOOP_CICLO);

    while(true){

        blink_phase_ms   += LOOP_CICLO;
        measure_phase_ms += LOOP_CICLO;

        if (measure_phase_ms >= 250) {
        distance = hc_sr04_medicion_cm();
        delay_ms = distance_to_delay_ms(distance);
        peligro = is_object_close(distance);
            if (peligro && !peligro_prev){
                printf("Peligro. El objeto está a una distancia menor de 10 cm.\n");
            }
            else if (!peligro && (distance <= 350)){
                printf("Distancia: %.2f cm, Delay: %u ms\n", distance, delay_ms);
            }
            peligro_prev = peligro;
        measure_phase_ms = 0;
        }

        if(peligro){
            led_on();
            buzzer_on();
        }
        else if(blink_phase_ms >= delay_ms){
            led_toggle();
            buzzer_toggle();
            blink_phase_ms = 0;
        }

        sleep_until(next_tick);
        next_tick = delayed_by_ms(next_tick, LOOP_CICLO);
    }
    return 0;
}