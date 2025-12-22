#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include <stdint.h>

// Inicializa el LED (por ejemplo GPIO 25)
void led_init(void);

// Enciende el LED
void led_on(void);

// Apaga el LED
void led_off(void);

// Alterna el estado del LED
void led_toggle(void);

#endif