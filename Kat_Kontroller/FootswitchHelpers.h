#include "Footswitch.h"

/*
   Save fx settings so that when switching between modes, correct leds and statuses are shown
   - first find the settings associated with the current channel
   - check which button was pressed and update associated setting
   - TODO: link button to setting better to avoid ifs
*/
void updateFx(boolean value, FOOTSWITCH &fsw) {
  for (int i = 0; i < 3; i = i + 1) {
    if (settings[i] -> channel == currentChannel) {
      if (fsw.button == 2) {
        settings[i] -> fx1 = value;
      }
      else if (fsw.button == 3) {
        settings[i] -> fx2 = value;
      }
      else if (fsw.button == 4) {
        settings[i] -> fx3 = value;
      }
    }
  }
}

/*
   Turn off fx with midi message, turn off led and save settings
*/
void turnFxOff(FOOTSWITCH &fsw) {
  fsw.led.turnOff(true);
  fsw.message.sendMessage(MODE, false);
  updateFx(false, fsw);
}


/*
   Turn on fx with midi message, turn on led and save settings
*/
void turnFxOn(FOOTSWITCH &fsw) {
  fsw.message.sendMessage(MODE, true);
  fsw.led.turnOn(true);
  updateFx(true, fsw);
}

/*
   When channel is changed Katana does not store fx statuses
   Therefore reset back to defaults
   TODO: Fire off cc messages along with channel change to avoid this
*/
void resetFx() {
  for (int i = 0; i < 3; i = i + 1) {
    settings[i] -> fx1 = defaults[i].fx1;
    settings[i] -> fx2 = defaults[i].fx2;
    settings[i] -> fx3 = defaults[i].fx3;
  }
}

/*
   Switch the Katana channel
   - reset fx to the default
   - turn off leds except selected channel
   - send midi message
   - set currentChannel to the new channel
*/
void setChannel(FOOTSWITCH &fsw) {
  // switch channel and reset fx settings
  resetFx();
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
void turnOnFxLeds() {
  for (int i = 0; i < 3; i = i + 1) {
    if (settings[i] -> channel == currentChannel) {
      if (settings[i] -> fx1) footswitches[0].led.turnOn(true);
      if (settings[i] -> fx2) footswitches[1].led.turnOn(true);
      if (settings[i] -> fx3) footswitches[2].led.turnOn(true);
    }
  }
}

/*
   Switches mode between channel and fx
   If channel mode then turn off fx leds
   If fx mode turn on fx leds and the mode led
   TODO: Can I remove the turnOffLeds line?
*/
void changeMode(FOOTSWITCH &fsw) {
  turnOffLeds(false);
  MODE = !MODE; // switch controller MODE
  if (!MODE) {
    turnOffFxLeds();
  }
  else {
    turnOnFxLeds();
    fsw.led.turnOn(false);
  }
}

/*
   Footswitch is turned on, multiple options
   If PC mode and not a function press -> set channel
   If function press -> change mode
   otherwise turn on fx
*/
void footswitchOn(FOOTSWITCH &fsw) {
  if (!MODE && !fsw.func) setChannel(fsw);
  else if (fsw.func) changeMode(fsw);
  else turnFxOn(fsw);
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
void checkFootswitch(FOOTSWITCH &fsw) {
  if ((!MODE) || (!fsw.led.fxStatus && MODE) || fsw.func) {
    footswitchOn(fsw);
  }
  else if (fsw.led.fxStatus && MODE) {
    turnFxOff(fsw);
  }
}


/*
   Reads the footswitch with a software de-bounce
*/
void readFootswitch(FOOTSWITCH &fsw) {
  if (digitalRead(fsw.button) == HIGH) {
    delay(10);
    if (digitalRead(fsw.button) == HIGH) {
      checkFootswitch(fsw);
      delay(250);
    }
  }
}
