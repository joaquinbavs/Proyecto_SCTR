#ifndef LED_H
#define LED_H
// Include guard: evita múltiples inclusiones del mismo archivo
// Protege de redefiniciones durante compilaciones grandes

#include <stdbool.h>   // Para usar el tipo booleano `bool`
#include <stdint.h>    // Tipos enteros estándar (`uint32_t`, etc.)

// --------------------------- Interfaz del LED -----------------------------

// Inicializa el LED 
// Configura el pin como salida y apaga el LED inicialmente
void led_init(void);

// Enciende el LED
void led_on(void);

// Apaga el LED
void led_off(void);

// Si estaba apagado → enciende, si estaba encendido → apaga
void led_toggle(void);

#endif
// Fin de include guard
