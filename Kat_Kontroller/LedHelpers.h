#include "Globals.h"

void turnOffLeds(boolean fx) {
  for (int i = 0; i < 4; i = i + 1) {
    leds[i].turnOff(fx);
  }
}

void turnOffFxLeds(LED &currentLed) {
  turnOffLeds(true);
  currentLed.turnOn(true);
}
