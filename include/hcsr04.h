#ifndef HC_SR04_H
#define HC_SR04_H

#include <stdint.h>

#include "pico/stdlib.h"

void hc_sr04_init(uint trig_pin, uint echo_pin);
float hc_sr04_medicion_cm(void);

#endif