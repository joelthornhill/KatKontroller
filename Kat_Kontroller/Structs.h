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

