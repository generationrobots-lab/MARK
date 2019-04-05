/*
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
 
#include <Encoder.h>
#include "Ultrasonic.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include "Grove_I2C_Motor_Driver.h"
#include <Grove_LED_Bar.h>

//init all libraryes
Encoder knobLeft(18, 29);
Encoder knobRight(19, 27 );
rgb_lcd lcd;
Ultrasonic ultrasonic(8);
Grove_LED_Bar bar(5, 4, 0);  // Clock pin, Data pin, Orientation

//define I2C adress
#define I2C_ADDRESS 0x0f

//init all variables
int count = 0;
byte ledbar;
long sumVoltage = 0;
const byte bumperLeft = 2;
const byte bumperRight = 3;
volatile byte stateBumperLeft = LOW;
volatile byte stateBumperRight = LOW;

volatile long left_timestamp = 0; //used to stamp start time of an IR pulse
volatile long left_timestampdiff = 0; //used to stamp start time of an IR pulse
volatile long right_timestamp = 0; //used to stamp start time of an IR pulse
volatile long right_timestampdiff = 0; //used to stamp start time of an IR pulse

int r = 0;
int g = 0;
int b = 0;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setRGB(200, 200, 200);
  bar.begin();
  bar.setBits(0x3ff);
  Motor.begin(I2C_ADDRESS);

  pinMode(bumperLeft, INPUT_PULLUP);
  pinMode(bumperRight, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(bumperLeft), leftCB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(bumperRight), rightCB, CHANGE);
  delay(1000);
  bar.setBits(0x0);
  lcd.setRGB(0, 00, 00);
}


void loop() {
  Serial.print("encodeurs : ");
  Serial.print(knobLeft.read());
  Serial.print(" : ");
  Serial.println(knobRight.read());

  int r = 0;
  int g = 0;
  int b = 0;

  if (stateBumperLeft) {
    Motor.speed(MOTOR2, -50);
    r = 255;
    g += 125;
  }
  else {
    Motor.stop(MOTOR2);
  }
  
  if (stateBumperRight) {
    Motor.speed(MOTOR1, -50);
    b = 255;
    g += 125;
  }
  else {
    Motor.stop(MOTOR1);
  }

  lcd.setRGB(r, g, b);
  sumVoltage = analogRead(A0) + sumVoltage ;
  
  if (count > 100) {
    int finalvalue = 0;
    sumVoltage = sumVoltage / 100;
    sumVoltage = (3 * sumVoltage * 4980 / 1023.00);
    sumVoltage =  map(sumVoltage, 6000, 8500, 0, 10);
    bar.setLevel(sumVoltage);
    count = 0;
  }
  else {
    count ++;
  }

  delay(20);
}


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
  { stateBumperLeft = !stateBumperLeft;
    left_timestamp = micros() ;

  }
}




