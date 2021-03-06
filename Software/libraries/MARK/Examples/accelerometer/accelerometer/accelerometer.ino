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
  myrobot.setLcdCursor(0, 0);
  myrobot.lcdPrint(myrobot.getAccelX());
  /*other data from IMU :
   * getAccelY()
   * getAccelZ()
   * getGyroX()
   * getGyroY()
   * getGyroZ()
   * getTemp()
   */
  myrobot.lcdPrint("   ");
}
