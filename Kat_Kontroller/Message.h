#include "LedHelpers.h"

struct Message {
  int pcChannel;
  int ccMessage;
  void sendMessage(boolean isControl, boolean status) {
    if (!isControl) {
      Serial.println("send pc message");
      Serial.println(pcChannel);
//            MIDI.sendProgramChange(pcChannel, MIDI_CHANNEl);
    }
    else if (isControl && status) {
      Serial.println("send cc message");
      Serial.println(ccMessage);
      Serial.println(127);
      //      MIDI.sendControlChange(ccMessage, 127, MIDI_CHANNEl);
    }
    else if (isControl && !status) {
      Serial.println("send cc message");
      Serial.println(ccMessage);
      Serial.println(0);
      //      MIDI.sendControlChange(ccMessage, 0, MIDI_CHANNEl);
    }
  }
};
