#ifndef BUZZER_H
#define BUZZER_H
// Protecciones contra inclusiones múltiples (include guard)
// Evita que el compilador procese este archivo más de una vez

#include <stdint.h>    // Tipos enteros estándar (uint32_t, etc.)
#include <stdbool.h>   // Tipo booleano `bool` en C
#include "pico/stdlib.h" // Funciones básicas del SDK Pico (GPIO, sleep, etc.)

// --------------------------- Interfaz del buzzer ----------------------------

// Inicializa el buzzer en un GPIO determinado
// Parámetro:
//   pin -> número de GPIO al que está conectado el buzzer
void buzzer_init(uint pin);

// Enciende el buzzer
void buzzer_on(void);

// Apaga el buzzer
void buzzer_off(void);

// Alterna el estado del buzzer (si estaba apagado, se enciende; si estaba encendido, se apaga)
void buzzer_toggle(void);

#endif
// Fin de include guard
