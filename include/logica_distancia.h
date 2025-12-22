#ifndef DISTANCE_LOGIC_H
#define DISTANCE_LOGIC_H

#include <stdint.h>  // Para uint32_t
#include <stdbool.h> // Por si quieres usar booleanos

// Convierte la distancia en centímetros a un delay en milisegundos
uint32_t distance_to_delay_ms(float distance_cm);

// Define si un objeto está "cerca" según un umbral
bool is_object_close(float distance_cm);

#endif
