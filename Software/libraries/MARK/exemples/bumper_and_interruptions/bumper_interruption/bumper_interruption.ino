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
  myrobot.setRightMotor(50);
  myrobot.setLeftMotor(50);
}

void loop() {
  if (myrobot.getInterruptFlag()) {
    myrobot.stopLeftMotor();
    myrobot.stopRightMotor();
  }
}
