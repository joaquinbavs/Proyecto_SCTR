#include "buzzer.h"              // Funciones para controlar el buzzer
#include "hcsr04.h"              // Funciones para manejar el sensor ultrasónico HC-SR04
#include "led.h"                 // Funciones para controlar el LED
#include "logica_distancia.h"    // Lógica de distancia: delay y detección de peligro

#include <pico/stdlib.h>         // SDK estándar de Raspberry Pi Pico (GPIO, temporización, tipos)
#include <stdio.h>               // Entrada/salida estándar (printf)

/* Definición de pines GPIO */
#define BUZZER_GPIO 14           // GPIO conectado al buzzer
#define ECHO_GPIO 15             // GPIO conectado al pin ECHO del HC-SR04
#define TRIG_GPIO 16             // GPIO conectado al pin TRIG del HC-SR04

#define LOOP_CICLO 100            // Periodo base del bucle principal en milisegundos

/* Contadores de tiempo acumulado */
static uint32_t blink_phase_ms = 0;    // Tiempo acumulado para el parpadeo LED/buzzer
static uint32_t measure_phase_ms = 0;  // Tiempo acumulado para la medición de distancia

int main(void){
    stdio_init_all();            // Inicializa la salida estándar (USB serial)

    sleep_ms(1000);              // Retardo inicial para estabilizar el sistema

    led_init();                  // Inicializa el LED
    buzzer_init(BUZZER_GPIO);    // Inicializa el buzzer con el GPIO definido
    hc_sr04_init(TRIG_GPIO, ECHO_GPIO); // Inicializa el sensor HC-SR04

    led_on();                    // Enciende el LED
    buzzer_on();                 // Enciende el buzzer
    sleep_ms(250);               // Parpadeo de comprobación de arranque correcto

    led_off();                   // Apaga el LED
    buzzer_off();                // Apaga el buzzer

    /* Variables de estado */
    float     distance   = 0.0f; // Distancia medida en centímetros
    uint32_t  delay_ms   = 0;    // Retardo calculado en función de la distancia
    bool      peligro    = false;// Indica si el objeto está demasiado cerca
    bool      peligro_prev = false; // Estado anterior de peligro (detección de flanco)

    /* Marca de tiempo para temporización precisa del bucle */
    absolute_time_t next_tick =
        delayed_by_ms(get_absolute_time(), LOOP_CICLO);
    // Define cuándo debe ejecutarse la siguiente iteración

    while(true){

        blink_phase_ms   += LOOP_CICLO;
        // Acumula tiempo para controlar el parpadeo

        measure_phase_ms += LOOP_CICLO;
        // Acumula tiempo para controlar la frecuencia de medición

        if (measure_phase_ms >= 250) {
            // Realiza una medición cada 250 ms

            distance = hc_sr04_medicion_cm();
            // Obtiene la distancia en centímetros desde el HC-SR04

            delay_ms = distance_to_delay_ms(distance);
            // Calcula el retardo de parpadeo en función de la distancia

            peligro = is_object_close(distance);
            // Determina si la distancia está dentro del umbral de peligro

            if (peligro && !peligro_prev){
                // Detecta transición de estado seguro a peligro
                printf("Peligro. El objeto está a una distancia menor de 10 cm.\n");
            }
            else if (!peligro && (distance <= 350)){
                // Muestra información normal si la distancia es válida
                printf("Distancia: %.2f cm, Delay: %u ms\n", distance, delay_ms);
            }

            peligro_prev = peligro;
            // Guarda el estado actual para la siguiente iteración

            measure_phase_ms = 0;
            // Reinicia el contador de medición
        }

        if(peligro){
            // En modo peligro: LED y buzzer siempre encendidos
            led_on();
            buzzer_on();
        }
        else if(blink_phase_ms >= delay_ms){
            // En modo normal: parpadeo según la distancia
            led_toggle();         // Cambia el estado del LED
            buzzer_toggle();      // Cambia el estado del buzzer
            blink_phase_ms = 0;   // Reinicia el contador de parpadeo
        }

        sleep_until(next_tick);
        // Espera hasta el instante exacto del siguiente ciclo

        next_tick = delayed_by_ms(next_tick, LOOP_CICLO);
        // Programa el siguiente tick manteniendo un periodo fijo
    }

    return 0;                   
}
