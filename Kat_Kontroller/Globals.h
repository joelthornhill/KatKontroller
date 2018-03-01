#include <MIDI.h>
#include "Structs.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

boolean MODE = 0; // 0 = PC, 1 == CC
const int MIDI_CHANNEl = 1;

const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;

const int fx1 = 16;
const int fx2 = 17;
const int fx3 = 18;

// channel - fx1 - fx2 - fx3
ChannelSetting default1 = { 0, 0, 0, 0 };
ChannelSetting default2 = { 1, 1, 0, 0 };
ChannelSetting default3 = { 2, 0, 0, 0 };
ChannelSetting defaults[] = { default1, default2, default3 };


// channel - fx1 - fx2 - fx3
ChannelSetting channel1 = default1;
ChannelSetting channel2 = default2;
ChannelSetting channel3 = default3;

ChannelSetting *settings[] = { &channel1, &channel2, &channel3 };

LED led1 = { 9 };
LED led2 = { 10 };
LED led3 = { 11 };
LED led4 = { 12 };
LED currentLed;

int currentChannel;

LED leds[] = {led1, led2, led3, led4};
