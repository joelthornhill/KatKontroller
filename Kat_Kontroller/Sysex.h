


struct Sysex {
  int curr;
  byte * getMessage() {

    byte message[13];

    for (int i = 0; i < 7; i = i + 1) {
      message[i] = prefix[i];
      curr = curr + 1;
    }

    for (int i = 0; i < 7; i = i + 1) {
      message[i] = prefix[i];
      curr = curr + 1;
    }


    message[curr] = calculateChecksum();

    message;
  }

  byte calculateChecksum() {
    0x79
  }
};
