#include "Setup.h"

void setup() {

  if (debug) Serial.begin(9600);
  else Serial.begin(31250);

  // buttons as input pins
  for (int i = 0; i < 4; i = i + 1) {
    pinMode(footswitches[i].button, OUTPUT);
  }

  // leds as output pins
  for (int i = 0; i < 4; i = i + 1) {
    pinMode(leds[i].led, OUTPUT);
  }

  Helpers h { footswitches[0], currentChannel, MODE };

  // blink leds on start up
  h.blinkLeds(leds);

  // set to channel 1
  h.footswitchOn(settings, leds, footswitches, defaults);
}

/*
   Reads the footswitch with a software de-bounce
*/
void readFootswitch(FOOTSWITCH &fsw, int &currentChannel, ChannelSetting *settings[], boolean &MODE, LED leds[], FOOTSWITCH footswitches[] ) {
  if (digitalRead(fsw.button) == HIGH) {
    delay(10);
    if (digitalRead(fsw.button) == HIGH) {
      Helpers h = { fsw, currentChannel, MODE };
      h.checkFootswitch(settings, leds, footswitches, defaults);
      delay(250);
    }
  }
}

void loop() {
  // read all footswitches
  for (int i = 0; i < 4; i = i + 1) {
    readFootswitch(footswitches[i], currentChannel, settings, MODE, leds, footswitches);
  }
}
