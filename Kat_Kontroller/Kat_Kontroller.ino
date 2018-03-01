#include "FootswitchHelpers.h"

void setup() {

  Serial.begin(9600);

  // buttons as input pins
  for (int i = 0; i < 4; i = i + 1) {
    pinMode(footswitches[i].button, OUTPUT);
  }

  // leds as output pins
  for (int i = 0; i < 4; i = i + 1) {
    pinMode(leds[i].led, OUTPUT);
  }
  
  // set to channel 1
  footswitchOn(fsw1);
}

void loop() {
  // read all footswitches
  for (int i = 0; i < 4; i = i + 1) {
    readFootswitch(footswitches[i]);
  }
}
