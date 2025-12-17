#ifndef PARKING_LOGIC_H
#define PARKING_LOGIC_H

#include <stdbool.h>

typedef enum {
    PARKING_FREE,
    PARKING_WARNING,
    PARKING_OCCUPIED,
    PARKING_ERROR
} parking_state_t;

void parking_init(void);
void parking_update(float distance, bool sensor_error);

#endif
