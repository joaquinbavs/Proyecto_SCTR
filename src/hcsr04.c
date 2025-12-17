#include "hcsr04.h"
#include "pico/stdlib.h"

#define TIMEOUT_US 30000  // Timeout máximo en microsegundos

typedef enum {
    HCSR_IDLE,
    HCSR_TRIGGER,
    HCSR_WAIT_ECHO_HIGH,
    HCSR_WAIT_ECHO_LOW,
    HCSR_DONE,
    HCSR_TIMEOUT
} hcsr_state_t;

static uint32_t trig, echo;           // Pines trig y echo
static hcsr_state_t state = HCSR_IDLE;

static absolute_time_t t_start;
static absolute_time_t echo_start, echo_end;
static float distance_cm = 0.0f;

// Inicializa el sensor HC-SR04
void hcsr04_init(uint32_t trig_pin, uint32_t echo_pin) {
    trig = trig_pin;
    echo = echo_pin;

    gpio_init(trig);
    gpio_set_dir(trig, GPIO_OUT);
    gpio_put(trig, 0);

    gpio_init(echo);
    gpio_set_dir(echo, GPIO_IN);
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
        gpio_put(trig, 1);
        sleep_us(10);
        gpio_put(trig, 0);
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

// Devuelve la última distancia medida en cm
float hcsr04_get_distance_cm(void) {
    return distance_cm;
}

// Indica si hubo timeout
bool hcsr04_has_timeout(void) {
    return state == HCSR_TIMEOUT;
}
