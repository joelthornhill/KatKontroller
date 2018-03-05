#include "FootswitchHelpers.h"


int currentChannel;
LED currentLed;
ChannelSetting channel1 = default1;
ChannelSetting channel2 = default2;
ChannelSetting channel3 = default3;
ChannelSetting *settings[] = { &channel1, &channel2, &channel3 };

void setup() {

  if(debug) Serial.begin(9600);
  else Serial.begin(31250);

  // buttons as input pins
  for (int i = 0; i < 4; i = i + 1) {
    pinMode(footswitches[i].button, OUTPUT);
  }

  // leds as output pins
  for (int i = 0; i < 4; i = i + 1) {
    pinMode(leds[i].led, OUTPUT);
  }

  helper h { fsw1, currentChannel, currentLed };
  
  // set to channel 1
  h.footswitchOn(settings);
}

void loop() {
  // read all footswitches
  for (int i = 0; i < 4; i = i + 1) {
    readFootswitch(footswitches[i], currentChannel, currentLed, settings);
  }
}
