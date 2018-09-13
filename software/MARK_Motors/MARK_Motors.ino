/*
   Description : the robot advances until collision, and then backs off and turns, and advances again.
   more info about I2C motor driver : http://wiki.seeedstudio.com/Grove-I2C_Motor_Driver_V1.3/
*/
#include "Grove_I2C_Motor_Driver.h"

#define I2C_ADDRESS 0x0f

void setup() {
  Motor.begin(I2C_ADDRESS);
  delay(10);
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
  delay(1000);
}

void loop() {
  Motor.speed(MOTOR1, 30);
  Motor.speed(MOTOR2, 30);
  delay(1000);
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
  delay(1000);
  Motor.speed(MOTOR1, -30);
  Motor.speed(MOTOR2, -30);
  delay(1000);
  Motor.stop(MOTOR1);
  delay(1000);
}

