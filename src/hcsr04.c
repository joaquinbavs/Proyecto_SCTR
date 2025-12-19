#include "hcsr04.h"
#include "pico/stdlib.h"
#include "pico/time.h"


#define TIMEOUT_US 30000  // Timeout máximo en microsegundos

typedef enum {
    HCSR_IDLE,
    HCSR_TRIGGER,
    HCSR_WAIT_ECHO_HIGH,
    HCSR_WAIT_ECHO_LOW,
    HCSR_DONE,
    HCSR_TIMEOUT
} hcsr_state_t;

static uint32_t trig_pin_g, echo_pin_g;           // Pines trig y echo
static hcsr_state_t state = HCSR_IDLE;

static absolute_time_t t_start;
static absolute_time_t echo_start, echo_end;
static float distance = 0.0f;

// Inicializa el sensor HC-SR04
void hcsr04_init(uint32_t trig_pin, uint32_t echo_pin) {
    trig_pin_g = trig_pin;
    echo_pin_g = echo_pin;

    gpio_init(trig_pin_g);
    gpio_set_dir(trig_pin_g, GPIO_OUT);
    gpio_put(trig_pin_g, 0);

    gpio_init(echo_pin_g);
    gpio_set_dir(echo_pin_g, GPIO_IN);
}

// Inicia una medición
void hcsr04_start_measurement(void) {
    if (state == HCSR_IDLE || state == HCSR_DONE || state == HCSR_TIMEOUT) {
        state = HCSR_TRIGGER;
        t_start = get_absolute_time();
    }
}

// Actualiza el estado del sensor (debe llamarse en el bucle principal)
bool hcsr04_update(void) {
    switch (state) {

    case HCSR_TRIGGER:
        gpio_put(trig_pin_g, 1);
        sleep_us(10);
        gpio_put(trig_pin_g, 0);
        state = HCSR_WAIT_ECHO_HIGH;
        break;

    case HCSR_WAIT_ECHO_HIGH:
        if (gpio_get(echo)) {
            echo_start = get_absolute_time();
            state = HCSR_WAIT_ECHO_LOW;
        } else if (absolute_time_diff_us(t_start, get_absolute_time()) > TIMEOUT_US) {
            state = HCSR_TIMEOUT;
        }
        break;

    case HCSR_WAIT_ECHO_LOW:
        if (!gpio_get(echo)) {
            echo_end = get_absolute_time();
            int64_t diff = absolute_time_diff_us(echo_start, echo_end);
            distance_cm = (diff * 0.0343f) / 2.0f; // Convertir tiempo a distancia
            state = HCSR_DONE;
            return true;
        } else if (absolute_time_diff_us(echo_start, get_absolute_time()) > TIMEOUT_US) {
            state = HCSR_TIMEOUT;
        }
        break;

    default:
        break;
    }

    return false;
}

float hcsr04_get_distance_cm(void) {
    // Usamos las variables que ya tenéis definidas en vuestro hcsr04.h
    gpio_put(trig_pin_g, 1);
    sleep_us(10);
    gpio_put(trig_pin_g, 0);

    // 1. Esperar a que el pin Echo suba con TIMEOUT
    uint32_t wait_start = time_us_32();
    while (gpio_get(echo_pin_g) == 0) {
        // Si pasan más de 30ms (30000us) sin señal, devolvemos error
        if (time_us_32()-wait_start > 30000) return -1.0f; 
    }

    uint32_t pulse_start = time_us_32();
    
    // 2. Esperar a que el pin Echo baje con TIMEOUT
    while (gpio_get(echo) == 1) {
        if (time_us_32()-pulse_start > 30000) break; 
    }
    
    uint32_t pulse_end = time_us_32();
    uint32_t duration = pulse_end-pulse_start;

    // Cálculo: (Tiempo * velocidad del sonido) / 2
    // 0.0343 / 2 = 0.01715
    return ((float)duration * 0.01715f);
}
// Indica si hubo timeout
bool hcsr04_has_timeout(void) {
    return (state == HCSR_TIMEOUT);
}
