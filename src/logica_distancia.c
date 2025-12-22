#include "logica_distancia.h"

// Configuración de ejemplo
#define MIN_DISTANCE_CM 1.0f
#define MAX_DISTANCE_CM 450.0f
#define MIN_DELAY_MS 250   // Delay mínimo (rápido) cuando está cerca
#define MAX_DELAY_MS 1500  // Delay máximo (lento) cuando está lejos

uint32_t distance_to_delay_ms(float distance_cm) {
    if (distance_cm <= MIN_DISTANCE_CM) return MIN_DELAY_MS;
    if (distance_cm >= MAX_DISTANCE_CM) return MAX_DELAY_MS;

    // Interpolación lineal: más cerca → delay menor, más lejos → delay mayor
    float ratio = (distance_cm - MIN_DISTANCE_CM) / (MAX_DISTANCE_CM - MIN_DISTANCE_CM);
    return (uint32_t)(MIN_DELAY_MS + ratio * (MAX_DELAY_MS - MIN_DELAY_MS));
}

bool is_object_close(float distance_cm) {
    return distance_cm <= MIN_DISTANCE_CM;
}
