#include "Message.h"

struct FOOTSWITCH {
  int button;
  LED led;
  boolean func;
  Message message;
};

FOOTSWITCH fsw1 = { button1, led1, false, Message { channel1.channel, fx1 } };
FOOTSWITCH fsw2 = { button2, led2, false, Message { channel2.channel, fx2 } };
FOOTSWITCH fsw3 = { button3, led3, false, Message { channel3.channel, fx3 } };
FOOTSWITCH fsw4 = { button4, led4, true, Message { 0, 0 } };

FOOTSWITCH footswitches[] = { fsw1, fsw2, fsw3, fsw4 };
