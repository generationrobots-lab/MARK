/*
    _____ _____  _               ____
   / ____|  __ \| |        /\   |  _ \
  | |  __| |__) | |       /  \  | |_) |
  | | |_ |  _  /| |      / /\ \ |  _ <
  | |__| | | \ \| |____ / ____ \| |_) |
   \_____|_|  \_\______/_/    \_\____/

*/

#include <MARK.h>

MARK myrobot;

void setup() {
  myrobot.begin();
}

void loop() {
  for (int i = 0; i <= 1; ++i) {
    for (int j = 0; j <= 15; ++j) {
      myrobot.setLcdCursor(j, i);
      myrobot.lcdPrint(">>>");
      delay(200);
      myrobot.setLcdCursor(j, i);
      myrobot.lcdPrint(" ");
    }
  }
}
