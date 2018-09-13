/*
   Description : This code displays the X accelerometer value on LCD screen
   press bumper right and left to change the value printed on LCD screen

   more informations : http://wiki.seeedstudio.com/Grove-6-Axis_AccelerometerAndGyroscope/
   this sensor use IMU's sparkfun library you can find it here : https://learn.sparkfun.com/tutorials/lsm6ds3-breakout-hookup-guide
  
   wiki LCD : http://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
   wiki wire : https://www.arduino.cc/en/reference/wire
*/

#include <Wire.h>
#include "SPI.h"
#include "SparkFunLSM6DS3.h"
#include "rgb_lcd.h"

rgb_lcd lcd;
LSM6DS3 myIMU( I2C_MODE, 0x6A );  //I2C device address 0x6A
const byte bumperLeft = 2;
const byte bumperRight = 3;
volatile byte stateBumperLeft = LOW;
volatile byte stateBumperRight = LOW;

volatile long left_timestamp = 0; //used to stamp start time of an IR pulse
volatile long left_timestampdiff = 0; //used to stamp start time of an IR pulse

volatile long right_timestamp = 0; //used to stamp start time of an IR pulse
volatile long right_timestampdiff = 0; //used to stamp start time of an IR pulse

volatile int case_var = 0; //used to stamp start time of an IR pulse


void setup()
{
  lcd.begin(16, 2); //init lcd
  lcd.setRGB(100, 100, 150); //set color to blue

  pinMode(bumperLeft, INPUT_PULLUP);
  pinMode(bumperRight, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(bumperLeft), leftCB, FALLING); // Call leftCB() when bumper Left is pulled
  attachInterrupt(digitalPinToInterrupt(bumperRight), rightCB, FALLING);// Call rightCB() when bumper Right is pulled

  lcd.setCursor(0, 0);

  if ( myIMU.begin() != 0 )// test if IMU is started
  {
    lcd.print("Device error");
  }
  else
  {
    lcd.print("Device OK!");
  }
  delay(2000);
  lcd.clear();
}


void loop()
{
  lcd.setCursor(0, 0); // places the cursor in the top left corner
  switch (case_var) {  // display datas
    case 0:
      lcd.print("Accel X  ");
      lcd.setCursor(0, 1);
      lcd.print(myIMU.readFloatAccelX(), 4);
      break;
    case 1:
      lcd.print("Accel Y  ");
      lcd.setCursor(0, 1);
      lcd.print(myIMU.readFloatAccelY(), 4);
      break;
    case 2:
      lcd.print("Accel Z  ");
      lcd.setCursor(0, 1);
      lcd.print(myIMU.readFloatAccelZ(), 4);
      break;
    case 3:
      lcd.print("Gyro X  ");
      lcd.setCursor(0, 1);
      lcd.print(myIMU.readFloatGyroX(), 4);
      break;
    case 4:
      lcd.print("Gyro Y  ");
      lcd.setCursor(0, 1);
      lcd.print(myIMU.readFloatGyroY(), 4);
      break;
    case 5:
      lcd.print("Gyro Z  ");
      lcd.setCursor(0, 1);
      lcd.print(myIMU.readFloatGyroZ(), 4);
      break;
    case 6:
      lcd.print("Temp     ");
      lcd.setCursor(0, 1);
      lcd.print(myIMU.readTempC(), 4);
      break;
    default:
      lcd.print("Error ..   ");
      break;
  }
  delay(250);
}
void rightCB() { //decrasses case_var value to switch the display in loop()
  right_timestampdiff =  micros() - right_timestamp ;
  if (right_timestampdiff > 1000000)
  {
    if (case_var <= 0) {
      case_var = 0;
    }
    else {
      case_var -= 1;
    }
    right_timestamp = micros() ;

  }
}

void leftCB() { //incrasses case_var value to switch the display in loop()
  left_timestampdiff =  micros() - left_timestamp ;
  if (left_timestampdiff > 1000000)
  {
    if (case_var >= 6) {
      case_var = 6;
    }
    else {
      case_var += 1;
    }
    left_timestamp = micros() ;

  }
}
