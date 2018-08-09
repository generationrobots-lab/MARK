/*
 * Description : the LDC color is blue when the left bumper is activate, orange when it is right, and white when both are pushed.
 * 
 * wiki LCD : http://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
 * wiki wire : https://www.arduino.cc/en/reference/wire
 */

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

//const byte ledPin = 13;
const byte bumperLeft = 2;
const byte bumperRight = 3;
volatile byte stateBumperLeft = LOW;
volatile byte stateBumperRight = LOW;

volatile long left_timestamp = 0; //used to stamp start time of an IR pulse
volatile long left_timestampdiff = 0; //used to stamp start time of an IR pulse

volatile long right_timestamp = 0; //used to stamp start time of an IR pulse
volatile long right_timestampdiff = 0; //used to stamp start time of an IR pulse


void setup() {
  lcd.begin(16, 2);
  pinMode(bumperLeft, INPUT_PULLUP);
  pinMode(bumperRight, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(bumperLeft), leftCB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(bumperRight), rightCB, CHANGE);
}

void loop() {
  int r = 0;
  int g = 0;
  int b = 0;

  if (stateBumperLeft) {
    r = 255;
    g += 125;
  }
  if (stateBumperRight) {
    b = 255;
    g += 125;
  }
  lcd.setRGB(r, g, b);
}

//2 functions of interruption 
void rightCB() {
  right_timestampdiff =  micros() - right_timestamp ;
  if (right_timestampdiff > 10000)
  {
    stateBumperRight = !stateBumperRight;
    right_timestamp = micros() ;
  }
}

void leftCB() {
  left_timestampdiff =  micros() - left_timestamp ;
  if (left_timestampdiff > 10000)
  { 
    stateBumperLeft = !stateBumperLeft;
    left_timestamp = micros() ;
  }
}

