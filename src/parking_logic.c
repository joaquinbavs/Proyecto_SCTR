#include "parking_logic.h"
#include "alerts.h"

static parking_state_t current_state;

void parking_init(void) {
    current_state = PARKING_FREE;
}

void parking_update(float distance, bool sensor_error) {

    if (sensor_error) {
        current_state = PARKING_ERROR;
    }
    else if (distance > 50.0f) {
        current_state = PARKING_FREE;
    }
    else if (distance > 20.0f) {
        current_state = PARKING_WARNING;
    }
    else {
        current_state = PARKING_OCCUPIED;
    }

    switch (current_state) {
    case PARKING_FREE:
        alert_free();
        break;
    case PARKING_WARNING:
        alert_warning();
        break;
    case PARKING_OCCUPIED:
        alert_occupied();
        break;
    case PARKING_ERROR:
        alert_error();  // puedes hacer parpadeo
        break;
    }
}
