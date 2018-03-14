#include "Structs.h"
#include "Helpers.h"

LED led1 = { ledOutput1 };
LED led2 = { ledOutput2 };
LED led3 = { ledOutput3 };
LED led4 = { ledOutput4 };
LED leds[] = {led1, led2, led3, led4};

/*
   Channel effect defaults
   Since the Boss Katana only has midi in, this is one way communication
   To avoid the controller and the Katana getting out of sync we set up defaults per channel
   Each setting has a channel value, and then whether each effect is on/off by default
   When you change between PC and CC mode the current state of fx are stored so correct LEDs show
   However, when you change channel these settings are lost and revert back to defaults
   TODO: There is scope to send CC messages on channel change to keep in sync and avoid reverting back to defaults
*/
ChannelSetting default1 = { 0, 0, 0, 0 };
ChannelSetting default2 = { 1, 1, 0, 0 };
ChannelSetting default3 = { 2, 0, 0, 0 };

ChannelSetting defaults[] = { default1, default2, default3 };
ChannelSetting *settings[] = { &default1, &default2, &default3 };

FOOTSWITCH footswitches[] = {
  { button1, led1, false, Message { default1.channel, fx1 } }, 
  { button2, led2, false, Message { default2.channel, fx2 } }, 
  { button3, led3, false, Message { default3.channel, fx3 } }, 
  { button4, led4, true, Message { 0, 0 } }
};

/*
   Value to specify what type of messages should be sent
   0 = PC mode. This is for sending channel changes
   1 = CC mode. This is for turning effects on and off
   The mode is toggled by the last footswitch
*/
boolean MODE = 0;

int currentChannel;


