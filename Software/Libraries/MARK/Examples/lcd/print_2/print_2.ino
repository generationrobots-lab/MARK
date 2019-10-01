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

int i = 0;
void setup() {
  myrobot.begin();
}

void loop() {
  myrobot.setLcdCursor(0, 0);
  myrobot.lcdPrint(i);
  delay(1000);
  i++;
}
