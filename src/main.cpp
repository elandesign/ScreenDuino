#include "Arduino.h"
#include "display.h"
#include "controls.h"
// #include "rotaryEncoder.h"

#define PIN_LED 9

void displayControlPosition() {
  display.clear();
  display.setCursor(0, 0);
  display.print(controlPosition);
}

void setup() {
  setupDisplay();
  setupControls();
  displayControlPosition();

  // Test code - use OK/Cancel to turn on/off an LED
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  if(okPressed) {
    digitalWrite(PIN_LED, HIGH);
    okPressed = false;
  }

  if(cancelPressed) {
    digitalWrite(PIN_LED, LOW);
    cancelPressed = false;
  }

  if(controlPositionChanged) {
    displayControlPosition();
    controlPositionChanged = false;
  }
}
