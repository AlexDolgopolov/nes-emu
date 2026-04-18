#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "stdbool.h"
#include "stdint.h"

typedef enum{
	SignalStrobe,
	SignalLatch
} ControllerSignalType;

void controller_signal(ControllerSignalType signal);
uint8_t controller_read(uint8_t num);

#endif