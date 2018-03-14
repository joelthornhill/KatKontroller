MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);
const int MIDI_CHANNEl = 1;

/*
   Debug mode. 0 = off, 1 = on
   In Debug mode the Arduino Baud rate is set to 9600 so that serial print works
   Midi messages are no longer set but instead their values printed
*/
int debug = 0;

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
   Set the arduino input/outputs for leds and buttons
*/
const int ledOutput1 = 8;
const int ledOutput2 = 9;
const int ledOutput3 = 10;
const int ledOutput4 = 11;

const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;
