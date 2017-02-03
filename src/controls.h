#include "Arduino.h"

#ifndef CONTROL_H
#define CONTROL_H

extern volatile int controlPosition;
extern volatile bool controlPositionChanged;
extern volatile bool okPressed;
extern volatile bool cancelPressed;

void setupControls();

#endif
