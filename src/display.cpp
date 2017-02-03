#include "display.h"
#include "pins.h"

PCD8544 display(PIN_SCLK, PIN_MOSI, PIN_LCD_DC, PIN_LCD_RST, PIN_LCD_CS);

void setupDisplay() {
  display.begin();
  display.clear();
}
