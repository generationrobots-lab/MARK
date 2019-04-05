/*
  Thumb Joystick demo v1.0
  information here : http://wiki.seeedstudio.com/Grove-Thumb_Joystick/
  connect the module to A0&A1 for using;
*/

#include "rgb_lcd.h"
#include <Wire.h>

rgb_lcd lcd;

void setup()
{
    Serial.begin(9600);
    pinMode(A2,INPUT);
    pinMode(A3,INPUT); 
    lcd.begin(16, 2);
    lcd.setRGB(200, 200, 200);
}

void loop()
{
    int sensorValue1 = analogRead(A2);
    int sensorValue2 = analogRead(A3);
    lcd.setCursor(0,0);
    lcd.print("The X and Y is:");
    lcd.setCursor(0,1);
    lcd.print(sensorValue1);
    lcd.setCursor(13,1);
    lcd.println(sensorValue2);
    delay(200);
    lcd.clear();
}
