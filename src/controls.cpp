#include "Arduino.h"
#include <avr/interrupt.h>
#include "controls.h"
#include "pins.h"

volatile int controlPosition = 0;
volatile bool controlPositionChanged = false;
volatile bool okPressed = false;
volatile bool cancelPressed = false;

// Debounce
volatile bool okState = HIGH;
volatile bool cancelState = HIGH;
volatile bool upState = HIGH;
volatile bool downState = HIGH;
volatile unsigned long okLastInterrupt = 0;
volatile unsigned long cancelLastInterrupt = 0;
volatile unsigned long upLastInterrupt = 0;
volatile unsigned long downLastInterrupt = 0;

#define DEBOUNCE 100 // 100ms debounce time

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
  unsigned long time = millis();

  // OK
  bool okNow = digitalRead(PIN_OK);
  if(okNow != okState) {
    if(okLastInterrupt + DEBOUNCE < time) {
      okPressed = okNow == LOW;
      okLastInterrupt = time;
    }
    okState = okNow;
  }

  // Cancel
  bool cancelNow = digitalRead(PIN_CANCEL);
  if(cancelNow != cancelState) {
    if(cancelLastInterrupt + DEBOUNCE < time) {
      cancelPressed = cancelNow == LOW;
      cancelLastInterrupt = time;
    }
    cancelState = cancelNow;
  }

  // Up
  bool upNow = digitalRead(PIN_UP);
  if(upNow != upState) {
    if(upLastInterrupt + DEBOUNCE < time) {
      if(upNow == LOW) {
        controlPosition++;
        controlPositionChanged = true;
      }
      upLastInterrupt = time;
    }
    upState = upNow;
  }

  // Down
  bool downNow = digitalRead(PIN_DOWN);
  if(downNow != downState) {
    if(downLastInterrupt + DEBOUNCE < time) {
      if(downNow == LOW) {
        controlPosition--;
        controlPositionChanged = true;
      }
      downLastInterrupt = time;
    }
    downState = downNow;
  }
}
