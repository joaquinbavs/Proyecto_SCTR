#ifndef HC_SR04_H
#define HC_SR04_H
// Include guard: evita que el archivo sea incluido más de una vez
// Protege contra errores de redefinición en compilaciones grandes

#include <stdint.h>       // Tipos de enteros estándar (uint32_t, etc.)
#include "pico/stdlib.h"  // Funciones básicas del SDK Pico (GPIO, sleep, tiempo)


// --------------------------- Interfaz del sensor HC-SR04 --------------------

// Inicializa el sensor HC-SR04 en los pines GPIO especificados
// Parámetros:
//   trig_pin -> GPIO conectado al pin TRIG
//   echo_pin -> GPIO conectado al pin ECHO
void hc_sr04_init(uint trig_pin, uint echo_pin);

// Realiza una medición de distancia usando el sensor HC-SR04
// Devuelve la distancia en centímetros
// Si ocurre timeout (eco no recibido), devuelve un valor basado en la duración máxima del pulso
float hc_sr04_medicion_cm(void);

#endif
// Fin de include guard
