#include <MIDI.h>
#include "Structs.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);
const int MIDI_CHANNEl = 1;

/*
   Debug mode. 0 = off, 1 = on
   In Debug mode the Arduino Baud rate is set to 9600 so that serial print works
   Midi messages are no longer set but instead their values printed
*/
int debug = 0;

/*
   Value to specify what type of messages should be sent
   0 = PC mode. This is for sending channel changes
   1 = CC mode. This is for turning effects on and off
   The mode is toggled by the last footswitch
*/
boolean MODE = 0;

/*
   Boss Katana midi spec states that when sending a cc message the value should be
   0-63 off
   64-127 on
*/
const int ccOn = 127;
const int ccOff = 0;


/*
   CC values for turning Boss Katana fx on/off
   16 - Boost/fx1
   17 - Delay/fx2
   18 - Reverb
*/
const int fx1 = 16;
const int fx2 = 17;
const int fx3 = 18;


/*
   I/O
   Setup the buttons and LEDs for the controller
   Currently 4 buttons with an LED each
*/

LED led1 = { 9 };
LED led2 = { 10 };
LED led3 = { 11 };
LED led4 = { 12 };

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
