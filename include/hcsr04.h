#ifndef HCSR04_H
#define HCSR04_H

#include <stdbool.h>
#include <stdint.h>

void hcsr04_init(uint32_t trig_pin, uint32_t echo_pin);
void hcsr04_start_measurement(void);
bool hcsr04_update(void);
float hcsr04_get_distance_cm(void);
bool hcsr04_has_timeout(void);

#endif
