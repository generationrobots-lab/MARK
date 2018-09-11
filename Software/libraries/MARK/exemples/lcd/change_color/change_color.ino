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
  myrobot.setLcdRGB(255, 0, 0); //red
  delay(1000);
  myrobot.setLcdRGB(0, 255, 0); // green
  delay(1000);
  myrobot.setLcdRGB(0, 0, 255); // blue
  delay(1000);
}
