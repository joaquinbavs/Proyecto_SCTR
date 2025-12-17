#ifndef ALERTS_H
#define ALERTS_H

#include "pico/stdlib.h"

void alerts_init(void);
void alert_free(void);
void alert_warning(void);
void alert_occupied(void);
void alert_error(void);

#endif
