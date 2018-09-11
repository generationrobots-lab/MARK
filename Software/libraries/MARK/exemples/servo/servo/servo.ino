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
  myrobot.setServo(0);
  delay(1000);
  myrobot.setServo(80);
  delay(1000);
  myrobot.setServo(160);
  delay(1000);
  myrobot.setServo(80);
  delay(1000);
}
