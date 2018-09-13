/*
   Description : the robot advances until collision, and then backs off and turns, and advances again.
   more info about I2C motor driver : http://wiki.seeedstudio.com/Grove-I2C_Motor_Driver_V1.3/
   Joystick : http://wiki.seeedstudio.com/Grove-Thumb_Joystick/
   Wiki wire : https://www.arduino.cc/en/reference/wire
   Wiki LCD : http://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/


   # My Joystick
    #     Min  Typ  Max  Click
    #  X  239  500  781  1023
    #  Y  244  522  777
*/
#include "Grove_I2C_Motor_Driver.h"
#include "rgb_lcd.h"
#include <Wire.h>

#define I2C_ADDRESS 0x0f

rgb_lcd lcd;
int r = 0;
int g = 0;
int b = 0;
int speed_left = 0, speed_right = 0;
int state = 1;


void setup() {
  Motor.begin(I2C_ADDRESS);
  delay(10);
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
  delay(1000);

  lcd.begin(16, 2);
  lcd.setRGB(200, 200, 200);
  lcd.setCursor(1,1);
  lcd.print("press to start");

}

void startMotor(){
  switch(state){
  case -1:
    Motor.speed(MOTOR1, speed_left);
    Motor.speed(MOTOR2, speed_right);
    break;
  case 1:
    Motor.stop(MOTOR1);
    Motor.stop(MOTOR2);
    break;
  }
}

void printSpeed(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Lt");
  lcd.print(speed_left);
  lcd.setCursor(8,0);
  lcd.print(" Rt");
  lcd.print(speed_right);
  if(state == 1){
    lcd.setCursor(1,1);
    lcd.print("press to start");
  }else{
    lcd.setCursor(1,1);
    lcd.print("press to stop");
  }
  delay(50);
}

void joystick(){
  if(analogRead(A4)>1020){
    state = state * -1;
    delay(100);
  }
  
  if(analogRead(A5)>230 && analogRead(A5)<790 ){
    int sensorValue1 = map(analogRead(A5), 260, 770, -10, 10);
    if(speed_right + sensorValue1 > -101 && speed_right + sensorValue1 < 101 && speed_left + sensorValue1 > -101 && speed_left + sensorValue1 < 101){
      speed_left = speed_left + sensorValue1;
      speed_right = speed_right + sensorValue1;
      delay(100);
    }
  }
  
  if(analogRead(A4)>230 && analogRead(A4)<790){
    int sensorValue2 = map(analogRead(A4), 230, 770, -10, 10);
    if(sensorValue2 > 0 && speed_right - sensorValue2 > -101 && speed_left + sensorValue2 < 101){
        speed_left = speed_left + sensorValue2;
        speed_right = speed_right - sensorValue2;
        delay(100);
    }
    if(sensorValue2 < 0 && speed_right + sensorValue2 < 101 && speed_left + sensorValue2 > -101){
       speed_left = speed_left + sensorValue2;
       speed_right = speed_right - sensorValue2;
       delay(100);
    }
  }
  printSpeed();  
}

void loop() {
  joystick();
  startMotor();
}

