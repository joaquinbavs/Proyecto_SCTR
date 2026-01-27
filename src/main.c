#include "buzzer.h"          // Control del buzzer
#include "hcsr04.h"          // Sensor de distancia ultrasónico HC-SR04
#include "led.h"             // Control del LED
#include "logica_distancia.h"// Funciones de lógica de distancia (is_object_close, distance_to_delay_ms)
#include "fsm_control.h"     // FSM para controlar SAFE/DANGER y parpadeo

#include <pico/stdlib.h>     // Librería estándar del RP2040 / Raspberry Pi Pico
#include <stdio.h>           // Para printf

/* ---------------- Definiciones de hardware ---------------- */
#define BUZZER_GPIO 14       // Pin del buzzer
#define ECHO_GPIO   15       // Pin ECHO del sensor ultrasónico
#define TRIG_GPIO   16       // Pin TRIG del sensor ultrasónico

/* ---------------- Periodos en milisegundos ---------------- */
#define LOOP_PERIOD_MS    100   // Periodo del loop principal
#define MEASURE_PERIOD_MS 250   // Periodo de medición de distancia

int main(void)
{
    /* ---------- Inicialización ---------- */
    stdio_init_all();      // Inicializa comunicación serial / printf
    sleep_ms(1000);        // Espera 1 segundo para estabilización

    led_init();            // Inicializa el LED
    buzzer_init(BUZZER_GPIO);  // Inicializa el buzzer en su pin
    hc_sr04_init(TRIG_GPIO, ECHO_GPIO); // Inicializa sensor ultrasónico

    fsm_init();            // Inicializa la FSM en estado SAFE

    /* ---------- Variables ---------- */
    float distance = 0.0f;       // Distancia medida por el sensor
    uint32_t delay_ms = 500;     // Tiempo de parpadeo calculado según distancia

    uint32_t blink_acc = 0;      // Acumulador para parpadeo del LED/buzzer
    uint32_t measure_acc = 0;    // Acumulador para medición periódica

    /* Siguiente tick del loop */
    absolute_time_t next_tick =
        delayed_by_ms(get_absolute_time(), LOOP_PERIOD_MS);

    /* ---------- Loop principal ---------- */
    while (true) {

        blink_acc   += LOOP_PERIOD_MS;   // Acumula tiempo para parpadeo
        measure_acc += LOOP_PERIOD_MS;   // Acumula tiempo para medición

        /* ----------- Medición de distancia ----------- */
        if (measure_acc >= MEASURE_PERIOD_MS) {

            distance = hc_sr04_medicion_cm();       // Medir distancia en cm
            delay_ms = distance_to_delay_ms(distance); // Calcula retardo según distancia

            if (is_object_close(distance)) {        // Si objeto está cerca
                fsm_dispatch(EV_DANGER);           // FSM entra en estado DANGER
            } else {                                // Si no hay objeto cerca
                fsm_dispatch(EV_SAFE);             // FSM permanece o vuelve a SAFE
            }

            printf("Distancia: %.2f cm\n", distance); // Imprime distancia en consola
            measure_acc = 0;                          // Reinicia acumulador de medición
        }

        /* ----------- Parpadeo / Timeout ----------- */
        if (blink_acc >= delay_ms) {
            fsm_dispatch(EV_TIMEOUT);  // Envía evento de timeout para parpadeo
            blink_acc = 0;             // Reinicia acumulador de parpadeo
        }

        /* ---------- Sincronización del loop ---------- */
        sleep_until(next_tick);               // Espera hasta el siguiente tick
        next_tick = delayed_by_ms(next_tick, LOOP_PERIOD_MS); // Calcula siguiente tick
    }
}
