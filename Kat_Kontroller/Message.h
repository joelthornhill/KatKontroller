#include "LedHelpers.h"

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
        MIDI.sendControlChange(ccMessage, 127, MIDI_CHANNEl);
      }
    } else if (isControl && !status) {
      if (debug) {
        Serial.println("send cc message off");
        Serial.println(ccMessage);
      } else {
        MIDI.sendControlChange(ccMessage, 0, MIDI_CHANNEl);
      }
    }
  }
};
