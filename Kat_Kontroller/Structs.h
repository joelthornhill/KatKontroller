#include <MIDI.h>
#include "Globals.h"

struct LED {
  int led;
  boolean fxStatus;
  void turnOff(boolean fx) {
    digitalWrite(led, LOW);
    if (fx) fxStatus = 0;
  }
  void turnOn(boolean fx) {
    digitalWrite(led, HIGH);
    if (fx) fxStatus = 1;
  }
};

struct ChannelSetting {
  int channel;
  boolean fx1;
  boolean fx2;
  boolean fx3;
  boolean getFx(int idx) {
    if(idx == 0) return fx1;
    else if(idx == 1) return fx2;
    else if(idx == 2) return fx3;
  }
  void setFx(int idx, boolean value) {
    if(idx == 0) fx1 = value;
    else if(idx == 1) fx2 = value;
    else if(idx == 2) fx3 = value;
  }
};

struct Message {
  int pcChannel;
  int ccMessage;

  void sendMessage(boolean isControl, boolean status) {
    if (!isControl) {
      if (debug) {
        Serial.println("send pc message");
        Serial.println(pcChannel);
      } else {
        MIDI.sendProgramChange(pcChannel, MIDI_CHANNEl);
      }
    } else if (isControl && status) {
      if (debug) {
        Serial.println("send cc message on");
        Serial.println(ccMessage);
      } else {
        MIDI.sendControlChange(ccMessage, ccOn, MIDI_CHANNEl);
      }
    } else if (isControl && !status) {
      if (debug) {
        Serial.println("send cc message off");
        Serial.println(ccMessage);
      } else {
        MIDI.sendControlChange(ccMessage, ccOff, MIDI_CHANNEl);
      }
    }
  }
};

struct FOOTSWITCH {
  int button;
  LED led;
  boolean func;
  Message message;
};


