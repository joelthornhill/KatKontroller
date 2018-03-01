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
};

