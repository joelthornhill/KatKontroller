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
  boolean fx1B;
  boolean fx2B;
  boolean fx3B;

  boolean getFx(int idx, boolean bank) {
    if (idx == 0) return decideFx(&fx1, &fx1B, bank);
    else if (idx == 1) return decideFx(&fx2, &fx2B, bank);
    else if (idx == 2) return decideFx(&fx3, &fx3B, bank);
  }
  void setFx(int idx, boolean value, boolean bank) {
    if(idx == 0) decideFx(&fx1, &fx1B, bank) = value;
    else if(idx == 1) decideFx(&fx2, &fx2B, bank) = value;
    else if (idx == 2) decideFx(&fx3, &fx3B, bank) = value;
  }

  boolean& decideFx(boolean *fx, boolean *bankfx, boolean bank) {
    if (bank) return *bankfx;
    else return *fx;
  }
};

struct Message {
  int pcChannel;
  int ccMessage;

  void sendMessage(boolean isControl, boolean status, boolean bank) {
    if (!isControl) {
      int channel;
      if(bank) channel = pcChannel + 5;
      else channel = pcChannel;
      if (debug) {
        Serial.println("send pc message");
        Serial.println(channel);
      } else {
        MIDI.sendProgramChange(channel, MIDI_CHANNEl);
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
  String func;
  Message message;
};


