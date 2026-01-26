#ifndef DISTANCE_LOGIC_H
#define DISTANCE_LOGIC_H
// Include guard: evita múltiples inclusiones del archivo
// Protege contra redefiniciones y errores de compilación

#include <stdint.h>   // Tipos enteros estándar, como uint32_t
#include <stdbool.h>  // Tipo booleano `bool`

// Convierte la distancia en centímetros a un delay en milisegundos
uint32_t distance_to_delay_ms(float distance_cm);

// Define si un objeto está "cerca" según un umbral
bool is_object_close(float distance_cm);

#endif
