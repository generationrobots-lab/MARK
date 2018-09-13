/*
   This code is a line flowwer example, using the IR sensor.
   IR sensor is plugged into port digital 6 then use digitalRead only

  Wiki for lcd : http://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
*/

#include "rgb_lcd.h"

rgb_lcd lcd;

const byte infrared = 6;

void setup() {
  lcd.begin(16, 2);
  delay(10);
}

void loop() {
  if (digitalRead(infrared)) {
    lcd.setRGB(0, 255, 0);
  }
  else {
    lcd.setRGB(255, 0, 0);
  }


}



