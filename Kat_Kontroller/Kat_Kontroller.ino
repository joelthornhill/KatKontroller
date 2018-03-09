#include "Setup.h"

void setup() {

  if (debug) Serial.begin(9600);
  else Serial.begin(31250);

  // buttons as input pins
  for (int i = 0; i < 4; i = i + 1) {
    pinMode(footswitches[i].button, INPUT_PULLUP);
  }

  // leds as output pins
  for (int i = 0; i < 4; i = i + 1) {
    pinMode(leds[i].led, OUTPUT);
  }

  // blink leds on start up
  blinkLeds();

  Helpers h { footswitches[0], currentChannel, currentLed, MODE };

  // set to channel 1
  h.footswitchOn(settings, leds, footswitches, defaults);
}

void blinkLeds() {

  for (int i = 0; i < 4; i = i + 1) {
    digitalWrite(leds[i].led, HIGH);
    delay(200);
    digitalWrite(leds[i].led, LOW);
    delay(200);
  }


  blinkAll();
  blinkAll();
}

void blinkAll() {
  for (int i = 0; i < 4; i = i + 1) {
    digitalWrite(leds[i].led, HIGH);
  }

  delay(400);

  for (int i = 0; i < 4; i = i + 1) {
    digitalWrite(leds[i].led, LOW);
  }

  delay(400);
}

/*
   Reads the footswitch with a software de-bounce
*/
void readFootswitch(FOOTSWITCH &fsw, int &currentChannel, LED &currentLed, ChannelSetting *settings[], boolean &MODE, LED leds[], FOOTSWITCH footswitches[] ) {
  if (digitalRead(fsw.button) == LOW) {
    delay(10);
    if (digitalRead(fsw.button) == LOW) {
      Helpers h = { fsw, currentChannel, currentLed, MODE };
      h.checkFootswitch(settings, leds, footswitches, defaults);
      delay(250);
    }
  }
}

void loop() {
  // read all footswitches
  for (int i = 0; i < 4; i = i + 1) {
    readFootswitch(footswitches[i], currentChannel, currentLed, settings, MODE, leds, footswitches);
  }
}
