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
  myrobot.lcdClear();
  myrobot.setLcdCursor(0, 0);
  myrobot.lcdPrint(myrobot.getEncoder("right"));
  myrobot.setLcdCursor(0, 1);
  myrobot.lcdPrint(myrobot.getEncoder("left"));
  delay(200);
}
