/*
   Description : Display the value of the front ultrasonic sensor on the LCD screen
   more information : http://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/
   LCD information : http://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
*/

#include <Wire.h>  //lib for I2C connection
#include "Ultrasonic.h"
#include "rgb_lcd.h"

rgb_lcd lcd; //Init of lcd lib
Ultrasonic ultrasonic(8); //Init of ultrasonic snesor on pin 8

//set LCD color
const int colorR = 100;
const int colorG = 100;
const int colorB = 200;

void setup()
{
  lcd.begin(16, 2); //Set lcd with 16 columns and 2 rows
  lcd.setRGB(colorR, colorG, colorB); //set colors on screen
  lcd.setCursor(0, 0); //set cursor position
  lcd.print("Front Ultrasonic"); 
}
void loop()
{
  lcd.setCursor(0, 1);
  lcd.print(ultrasonic.MeasureInCentimeters()); //print value of ultrasonic measure in centimeters
  lcd.print(" cm    ");
  delay(250);
}
