struct Helpers {
  FOOTSWITCH &fsw;
  int &currentChannel;
  boolean &MODE;
  boolean &BANK;

  int findFootswitchByChannel(FOOTSWITCH footswitches[]) {
    for (int i = 0; i < 3; i = i + 1) {
      if (footswitches[i].message.pcChannel == currentChannel) return i;
    }
  }

  int findSettingsByChannel(ChannelSetting *settings[]) {
    for (int i = 0; i < 3; i = i + 1) {
      if (settings[i] -> channel == currentChannel) return i;
    }
  }

  int findFootswitchByButton(FOOTSWITCH footswitches[]) {
    for (int i = 0; i < 3; i = i + 1) {
      if (fsw.button == footswitches[i].button) return i;
    }
  }

  void turnOffLeds(boolean fx, LED leds[]) {
    for (int i = 0; i < 5; i = i + 1) {
      leds[i].turnOff(fx);
    }

    if (BANK) leds[4].turnOn(false);
  }

  void turnOnLeds(boolean fx, LED leds[]) {
    for (int i = 0; i < 5; i = i + 1) {
      leds[i].turnOn(false);
    }
  }

  void turnOffFxLeds(LED leds[], FOOTSWITCH footswitches[]) {
    turnOffLeds(true, leds);
    int index = findFootswitchByChannel(footswitches);
    footswitches[index].led.turnOn(true);
  }

  /*
     Turn off fx with midi message, turn off led and save settings
  */
  void turnFxOff() {
    fsw.led.turnOff(true);
    fsw.message.sendMessage(MODE, false, BANK);
  }

  /*
     Save fx settings so that when switching between modes, correct leds and statuses are shown
     - find the settings associated with the current channel
     - check which button was pressed and update associated setting
  */
  void updateFx(boolean value, ChannelSetting *settings[], FOOTSWITCH footswitches[]) {
    int settingsIndex = findSettingsByChannel(settings);
    int footswitchIndex = findFootswitchByButton(footswitches);
    settings[settingsIndex] -> setFx(footswitchIndex, value, BANK);
  }

  /*
     Turn on fx with midi message, turn on led and save settings
  */
  void turnFxOn(ChannelSetting *settings[], FOOTSWITCH footswitches[] ) {
    fsw.message.sendMessage(MODE, true, BANK);
    fsw.led.turnOn(true);
    updateFx(true, settings, footswitches);
  }

  /*
     Switch the Katana channel
     - turn off leds except selected channel
     - send midi message
     - set currentChannel to the new channel
  */
  void setChannel(ChannelSetting *settings[], LED leds[], ChannelSetting defaults[], FOOTSWITCH footswitches[]) {
    turnOffLeds(true, leds);
    fsw.message.sendMessage(MODE, true, BANK);
    fsw.led.turnOn(false);
    currentChannel = fsw.message.pcChannel;
    setAllFx(settings, footswitches);
  }


  /*
     Find settings for current channel
     For each fx send update to Katana to keep in sync
     If in CC mode then also update the leds
  */
  void setAllFx(ChannelSetting *settings[], FOOTSWITCH footswitches[]) {
    int settingsIndex =  findSettingsByChannel(settings);
    for (int i = 0; i < 3; i = i + 1) {
      boolean status = settings[settingsIndex] -> getFx(i, BANK);
      
      if (status && MODE) footswitches[i].led.turnOn(true);
      else if(MODE) footswitches[i].led.turnOff(true);
      
      footswitches[i].message.sendMessage(true, status, BANK);
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
      setAllFx(settings, footswitches);
      fsw.led.turnOn(false);
    }
  }

  /*
     Switches bank between A/B for extra channels
     Does not switch mode so you can change bank in fx mode
  */
  void changeBank(ChannelSetting *settings[], FOOTSWITCH footswitches[], ChannelSetting defaults[], LED leds[]) {
    BANK = !BANK;
    if (BANK) fsw.led.turnOn(false);
    else fsw.led.turnOff(false);

    int index = findFootswitchByChannel(footswitches);
    footswitches[index].message.sendMessage(false, false, BANK);

    turnOffLeds(true, leds);

    if (!MODE) {
      footswitches[index].led.turnOn(false);
      setAllFx(settings, footswitches);
    }
    else {
      // turn on Mode leds
      footswitches[3].led.turnOn(false);
      setAllFx(settings, footswitches);
    }
  }

  /*
     Footswitch is turned on, multiple options
     If PC mode and not a function press -> set channel
     If function press -> change mode
     otherwise turn on fx
  */
  void footswitchOn(ChannelSetting *settings[], LED leds[], FOOTSWITCH footswitches[], ChannelSetting defaults[]) {
    if (!MODE && fsw.func == "") setChannel(settings, leds, defaults, footswitches);
    else if (fsw.func == "mode") changeMode(settings, leds, footswitches);
    else if (fsw.func == "bank") changeBank(settings, footswitches, defaults, leds);
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
    if ((!MODE) || (!fsw.led.fxStatus && MODE) || fsw.func != "") {
      footswitchOn(settings, leds, footswitches, defaults);
    }
    else if (fsw.led.fxStatus && MODE) {
      updateFx(false, settings, footswitches);
      turnFxOff();
    }
  }

  void blinkLeds(LED leds[]) {

    for (int i = 0; i < 5; i = i + 1) {
      leds[i].turnOn(false);
      delay(200);
      leds[i].turnOff(false);
      delay(200);
    }


    blinkAll(leds);
    blinkAll(leds);
  }

  void blinkAll(LED leds[]) {
    turnOnLeds(false, leds);
    delay(400);
    turnOffLeds(false, leds);
    delay(400);
  }

};
