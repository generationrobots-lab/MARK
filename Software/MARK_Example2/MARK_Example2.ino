/*
 * This is an example of navigation. All time go forward with regulation proportianal.
 * When bumper touch something robot go backward and turn right.
 * Led bar show battery level. And you can see on LCD distance between the robot and wall.
 * Vitesse is the speed of the robot.  
 * 
 *  Wiki accelerometer : http://wiki.seeedstudio.com/Grove-6-Axis_AccelerometerAndGyroscope/
 *  this sensor use IMU's sparkfun library you can find it here : https://learn.sparkfun.com/tutorials/lsm6ds3-breakout-hookup-guide
 *  Wiki LCD : http://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
 *  Wiki wire : https://www.arduino.cc/en/reference/wire
 *  Wiki encoder : https://www.pjrc.com/teensy/td_libs_Encoder.html
 *  Wiki voltage : http://wiki.seeedstudio.com/Grove-Voltage_Divider/
 *  Wiki driver motor : http://wiki.seeedstudio.com/Grove-I2C_Motor_Driver_V1.3/
 *  Wiki ultrasonic : http://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/
 *  
 *  Copyright Generation Robots
*/

#include "Grove_I2C_Motor_Driver.h"
#include <Encoder.h>
#include <Grove_LED_Bar.h>
#include "Ultrasonic.h"
#include <Wire.h>
#include "rgb_lcd.h"

// default I2C address is 0x0f
#define I2C_ADDRESS 0x0f

//LED indicator
Grove_LED_Bar bar(5, 4, 0);  // Clock pin, Data pin, Orientation
long sumVoltage = 0;
byte ledbar;
volatile long  voltage_timestampdiff=0;

//encoder
Encoder knobLeft(18, 29);
Encoder knobRight(19, 27);
long newLeft, newRight;
long positionLeft  = -999;
long positionRight = -999;

//bumper
const byte bumperLeft = 2;
const byte bumperRight = 3;
volatile byte stateBumperLeft = LOW;
volatile byte stateBumperRight = LOW;
volatile long left_timestamp = 0; //used to stamp start time of an IR pulse
volatile long left_timestampdiff = 0; //used to stamp start time of an IR pulse
volatile long right_timestamp = 0; //used to stamp start time of an IR pulse
volatile long right_timestampdiff = 0; //used to stamp start time of an IR pulse
bool flag = false;

//LCD declaration
rgb_lcd lcd;
const int colorR = 100;
const int colorG = 100;
const int colorB = 200;

//Us
Ultrasonic ultrasonic(8);

void setup() {
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test:");
  
  bar.begin();
  bar.setBits(0x3ff);

  Motor.begin(I2C_ADDRESS);
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
  
  pinMode(bumperLeft, INPUT_PULLUP);
  pinMode(bumperRight, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(bumperLeft), leftCB, RISING  );//Interrupt on bumper
  attachInterrupt(digitalPinToInterrupt(bumperRight), rightCB, RISING  );//Interrupt on bumper

  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.setCursor(0, 0);
}

void rightCB() {
  right_timestampdiff =  micros() - right_timestamp ;
  if (right_timestampdiff > 10000){
    flag = true;
    right_timestamp = micros() ;
  }
}

void leftCB() {
  left_timestampdiff =  micros() - left_timestamp ;
  if (left_timestampdiff > 10000){
    flag = true;
    left_timestamp = micros() ;
  }
}

//compute and print batery level on led indicator
void Voltage(){
  voltage_timestampdiff =  micros() - voltage_timestampdiff ;
  if (voltage_timestampdiff > 1000000){
    long  voltage = 0;
    voltage = analogRead(A0);
  
    voltage = (3 * voltage * 4980 / 1023.00);
    voltage =  map(voltage, 6000, 8500, 0, 10); //6000 mV (min for 2s) to 8500mV (max)
    bar.setLevel(voltage);
  }
}

void ResetEncoder(){
  // reset both back to zero.
  knobLeft.write(0);
  knobRight.write(0);
}

void RefrechEncoder(){
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    positionLeft = newLeft;
    positionRight = newRight;
  }
}

void GoForward(int value, int errorLeft, int errorRight){
  int correctionLeft = errorLeft*0.1;
  int correctionRight = errorRight*0.1;

  //if you want go forward use the correction else only use set speed
  Motor.speed(MOTOR1, value-correctionLeft);
  Motor.speed(MOTOR2, value+correctionRight);
}

void loop(){
  int vitesse = 100;
  Voltage();
  RefrechEncoder();
  lcd.setCursor(0, 1);
  lcd.print(ultrasonic.MeasureInCentimeters());
  lcd.print(" cm    ");
  
  
  if(flag){
    Motor.stop(MOTOR1);
    Motor.stop(MOTOR2);
    delay(1000);
    Motor.speed(MOTOR1, -20);
    Motor.speed(MOTOR2, -20);
    delay(1000);
    Motor.stop(MOTOR1);
    Motor.stop(MOTOR2);
    delay(1000);
    Motor.speed(MOTOR1, 20);
    Motor.speed(MOTOR2, -20);
    delay(1000);
    Motor.stop(MOTOR1);
    Motor.stop(MOTOR2);
    delay(1000);
    Motor.speed(MOTOR1, 30);
    Motor.speed(MOTOR2, 30);
    ResetEncoder();
    flag = false;
  }
  else if(ultrasonic.MeasureInCentimeters()<100){
    lcd.setRGB(255, 132, 10);
    
    if (ultrasonic.MeasureInCentimeters()<20){
      lcd.setRGB(255, 0, 0);
      GoForward(map(ultrasonic.MeasureInCentimeters(), 0, 20, 20, vitesse),positionLeft-positionRight, positionRight-positionLeft);
    }
    else{
      GoForward(vitesse,positionLeft-positionRight, positionRight-positionLeft);
    }
    delay(10);
  }else{
    lcd.setRGB(0, 255, 0);
    GoForward(vitesse,positionLeft-positionRight, positionRight-positionLeft);
 }
}


