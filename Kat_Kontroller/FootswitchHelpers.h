#include "Footswitch.h"

struct helper {
  FOOTSWITCH &fsw;
  int &currentChannel;
  LED &currentLed;

  /*
    When channel is changed Katana does not store fx statuses
    Therefore reset back to defaults
    TODO: Fire off cc messages along with channel change to avoid this
  */
  void resetFx(ChannelSetting *settings[]) {
    for (int i = 0; i < 3; i = i + 1) {
      for (int j = 0; j < 3; j = j + 1) {
        settings[i] -> setFx(j, defaults[i].getFx(j));
      }
    }
  }

  /*
     Turn off fx with midi message, turn off led and save settings
  */
  void turnFxOff() {
    fsw.led.turnOff(true);
    fsw.message.sendMessage(MODE, false);
  }

  /*
     Save fx settings so that when switching between modes, correct leds and statuses are shown
     - find the settings associated with the current channel
     - check which button was pressed and update associated setting
  */
  void updateFx(boolean value, ChannelSetting *settings[]) {
    for (int i = 0; i < 3; i = i + 1) {
      for (int j = 0; j < 3; j = j + 1) {
        if (settings[i] -> channel == currentChannel && fsw.button == footswitches[j].button) {
          settings[i] -> setFx(j, value);
        }
      }
    }
  }

  /*
     Turn on fx with midi message, turn on led and save settings
  */
  void turnFxOn(ChannelSetting *settings[]) {
    fsw.message.sendMessage(MODE, true);
    fsw.led.turnOn(true);
    updateFx(true, settings);
  }

  /*
     Switch the Katana channel
     - reset fx to the default
     - turn off leds except selected channel
     - send midi message
     - set currentChannel to the new channel
  */
  void setChannel(ChannelSetting *settings[]) {
    resetFx(settings);
    turnOffLeds(true);
    currentLed = fsw.led;
    fsw.message.sendMessage(MODE, true);
    fsw.led.turnOn(false);
    currentChannel = fsw.message.pcChannel;
  }


  /*
     Find settings for current channel
     For each fx turn on led if associated setting is set to true
  */
  void turnOnFxLeds(ChannelSetting *settings[]) {
    for (int i = 0; i < 3; i = i + 1) {
      for (int j = 0; j < 3; j = j + 1) {
        if (settings[i] -> channel == currentChannel && settings[i] -> getFx(j)) {
          footswitches[j].led.turnOn(true);
        }
      }
    }
  }

  /*
     Switches mode between channel and fx
     If channel mode then turn off fx leds
     If fx mode turn on fx leds and the mode led
     TODO: Can I remove the turnOffLeds line?
  */
  void changeMode(ChannelSetting *settings[]) {
    turnOffLeds(false);
    MODE = !MODE; // switch controller MODE
    if (!MODE) {
      turnOffFxLeds(currentLed);
    }
    else {
      turnOnFxLeds(settings);
      fsw.led.turnOn(false);
    }
  }

  /*
     Footswitch is turned on, multiple options
     If PC mode and not a function press -> set channel
     If function press -> change mode
     otherwise turn on fx
  */
  void footswitchOn(ChannelSetting *settings[]) {
    if (!MODE && !fsw.func) setChannel(settings);
    else if (fsw.func) changeMode(settings);
    else turnFxOn(settings);
  }


  /*
     Decides what type of press happened
     - If PC mode
     - OR CC mode AND fxStatus is 0
     - OR function press
        then footswitch on
     - If CC mode and fxStatus is 1
        then footswitch off
  */
  void checkFootswitch(ChannelSetting *settings[]) {
    if ((!MODE) || (!fsw.led.fxStatus && MODE) || fsw.func) {
      footswitchOn(settings);
    }
    else if (fsw.led.fxStatus && MODE) {
      updateFx(false, settings);
      turnFxOff();
    }
  }

};

/*
   Reads the footswitch with a software de-bounce
*/
void readFootswitch(FOOTSWITCH &fsw, int &currentChannel, LED &currentLed, ChannelSetting *settings[]) {
  if (digitalRead(fsw.button) == HIGH) {
    delay(10);
    if (digitalRead(fsw.button) == HIGH) {
      helper h = { fsw, currentChannel, currentLed };
      h.checkFootswitch(settings);
      delay(250);
    }
  }
}
