struct Helpers {
  FOOTSWITCH &fsw;
  int &currentChannel;
  boolean &MODE;

  void turnOffLeds(boolean fx, LED leds[]) {
    for (int i = 0; i < 4; i = i + 1) {
      leds[i].turnOff(fx);
    }
  }

  void turnOffFxLeds(LED leds[], FOOTSWITCH footswitches[]) {
    turnOffLeds(true, leds);

    for (int i = 0; i < 3; i = i + 1) {
      if (footswitches[i].message.pcChannel == currentChannel) {
        footswitches[i].led.turnOn(true);
      }
    }
  }

  /*
    When channel is changed Katana does not store fx statuses
    Therefore reset back to defaults
    TODO: Fire off cc messages along with channel change to avoid this
  */
  void resetFx(ChannelSetting *settings[], ChannelSetting defaults[]) {
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
  void updateFx(boolean value, ChannelSetting *settings[], FOOTSWITCH footswitches[]) {
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
  void turnFxOn(ChannelSetting *settings[], FOOTSWITCH footswitches[] ) {
    fsw.message.sendMessage(MODE, true);
    fsw.led.turnOn(true);
    updateFx(true, settings, footswitches);
  }

  /*
     Switch the Katana channel
     - reset fx to the default
     - turn off leds except selected channel
     - send midi message
     - set currentChannel to the new channel
  */
  void setChannel(ChannelSetting *settings[], LED leds[], ChannelSetting defaults[]) {
    resetFx(settings, defaults);
    turnOffLeds(true, leds);
    fsw.message.sendMessage(MODE, true);
    fsw.led.turnOn(false);
    currentChannel = fsw.message.pcChannel;
  }


  /*
     Find settings for current channel
     For each fx turn on led if associated setting is set to true
  */
  void turnOnFxLeds(ChannelSetting *settings[], FOOTSWITCH footswitches[]) {
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
  void changeMode(ChannelSetting *settings[], LED leds[], FOOTSWITCH footswitches[] ) {
    turnOffLeds(false, leds);
    MODE = !MODE; // switch controller MODE
    if (!MODE) {
      turnOffFxLeds(leds, footswitches);
    }
    else {
      turnOnFxLeds(settings, footswitches);
      fsw.led.turnOn(false);
    }
  }

  /*
     Footswitch is turned on, multiple options
     If PC mode and not a function press -> set channel
     If function press -> change mode
     otherwise turn on fx
  */
  void footswitchOn(ChannelSetting *settings[], LED leds[], FOOTSWITCH footswitches[], ChannelSetting defaults[]) {
    if (!MODE && !fsw.func) setChannel(settings, leds, defaults);
    else if (fsw.func) changeMode(settings, leds, footswitches);
    else turnFxOn(settings, footswitches);
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
  void checkFootswitch(ChannelSetting *settings[], LED leds[], FOOTSWITCH footswitches[], ChannelSetting defaults[]) {
    if ((!MODE) || (!fsw.led.fxStatus && MODE) || fsw.func) {
      footswitchOn(settings, leds, footswitches, defaults);
    }
    else if (fsw.led.fxStatus && MODE) {
      updateFx(false, settings, footswitches);
      turnFxOff();
    }
  }

  void blinkLeds(LED leds[]) {

    for (int i = 0; i < 4; i = i + 1) {
      digitalWrite(leds[i].led, HIGH);
      delay(200);
      digitalWrite(leds[i].led, LOW);
      delay(200);
    }


    blinkAll(leds);
    blinkAll(leds);
  }

  void blinkAll(LED leds[]) {
    allLedsOn(leds);
    delay(400);
    allLedsOff(leds);
    delay(400);
  }

  void allLedsOn(LED leds[]) {
    for (int i = 0; i < 4; i = i + 1) {
      digitalWrite(leds[i].led, HIGH);
    }
  }

  void allLedsOff(LED leds[]) {
    for (int i = 0; i < 4; i = i + 1) {
      digitalWrite(leds[i].led, LOW);
    }
  }


};
