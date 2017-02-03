#include "Arduino.h"
#include <avr/interrupt.h>
#include "controls.h"
#include "pins.h"

volatile int controlPosition = 0;
volatile bool controlPositionChanged = false;
volatile bool okPressed = false;
volatile bool cancelPressed = false;

// State of each button, HIGH due to pullup resistors
volatile bool okState = HIGH;
volatile bool cancelState = HIGH;
volatile bool upState = HIGH;
volatile bool downState = HIGH;

void setupControls() {
  pinMode(PIN_UP, INPUT);
  pinMode(PIN_DOWN, INPUT);
  pinMode(PIN_OK, INPUT);
  pinMode(PIN_CANCEL, INPUT);

  // Disable interrupts
  cli();

  // Set pin change interrupt flags on the control pins
  PCMSK2 |= (1 << PCINT18);
  PCMSK2 |= (1 << PCINT19);
  PCMSK2 |= (1 << PCINT20);
  PCMSK2 |= (1 << PCINT21);

  // Enable PCINT2 interrupts
  PCICR |= (1<<PCIE2);

  sei();
}

ISR(PCINT2_vect) {
  // OK
  bool ok = digitalRead(PIN_OK);
  if(ok != okState) {
    okPressed = ok == LOW;
    okState = ok;
  }

  // Cancel
  bool cancel = digitalRead(PIN_CANCEL);
  if(cancel != cancelState) {
    cancelPressed = cancel == LOW;
    cancelState = cancel;
  }

  // Up
  bool up = digitalRead(PIN_UP);
  if(up != upState) {
    controlPosition++;
    controlPositionChanged = up == LOW;
    upState = up;
  }

  // Down
  bool down = digitalRead(PIN_DOWN);
  if(down != downState) {
    controlPosition++;
    controlPositionChanged = down == LOW;
    downState = down;
  }
}
