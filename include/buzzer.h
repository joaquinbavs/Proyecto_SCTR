#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"

// Inicializa el buzzer en un GPIO determinado
void buzzer_init(uint pin);

// Enciende el buzzer
void buzzer_on(void);

// Apaga el buzzer
void buzzer_off(void);

// Alterna el estado del buzzer
void buzzer_toggle(void);

#endif