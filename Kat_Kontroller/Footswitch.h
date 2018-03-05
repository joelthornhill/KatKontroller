#include "Message.h"

struct FOOTSWITCH {
  int button;
  LED led;
  boolean func;
  Message message;
};

FOOTSWITCH fsw1 = { 2, led1, false, Message { default1.channel, fx1 } };
FOOTSWITCH fsw2 = { 3, led2, false, Message { default2.channel, fx2 } };
FOOTSWITCH fsw3 = { 4, led3, false, Message { default3.channel, fx3 } };
FOOTSWITCH fsw4 = { 5, led4, true, Message { 0, 0 } };

FOOTSWITCH footswitches[] = { fsw1, fsw2, fsw3, fsw4 };
