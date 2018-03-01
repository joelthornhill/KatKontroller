#include "Message.h"

struct FOOTSWITCH {
  int button;
  LED led;
  boolean func;
  Message message;
};

FOOTSWITCH fsw1 = { button1, led1, false, Message { 0, fx1 } };
FOOTSWITCH fsw2 = { button2, led2, false, Message { 1, fx2 } };
FOOTSWITCH fsw3 = { button3, led3, false, Message { 2, fx3 } };
FOOTSWITCH fsw4 = { button4, led4, true, Message { 0, 0 } };

FOOTSWITCH footswitches[] = { fsw1, fsw2, fsw3, fsw4 };
