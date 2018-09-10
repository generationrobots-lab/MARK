/*
   _____ _____  _               ____  
  / ____|  __ \| |        /\   |  _ \ 
 | |  __| |__) | |       /  \  | |_) |
 | | |_ |  _  /| |      / /\ \ |  _ < 
 | |__| | | \ \| |____ / ____ \| |_) |
  \_____|_|  \_\______/_/    \_\____/

  */
#include "Arduino.h"
#include "Wire.h"
#include "Grove_LED_Bar.h"
#include "SparkFunLSM6DS3.h"
#include "rgb_lcd.h"
#include "Grove_I2C_Motor_Driver.h"
#include "Ultrasonic.h"
#include "Servo.h"
#include "Encoder.h"


#ifndef MARK_H
#define MARK_H
#define I2C_ADDRESS 0x0f
#endif

class MARK {
public:
	//<<functions>>	
	MARK(void);
	~MARK(void);
	bool begin(); //return true if done
	//led bar
	bool setLedBarLevel(int level);
	int getLedBarLevel();
	//LCD
	void setLcdRGB(unsigned char r, unsigned char g, unsigned char b); //set lcd color, return true if done
	void lcdPrint(String text);
	void lcdPrint(float data);
	void setLcdCursor(uint8_t, uint8_t);
	void lcdHome();
	void lcdClear();
	//Motors
	void setLeftMotor(int speed);
	void setRightMotor(int speed);
	void stopLeftMotor();
	void stopRightMotor();
	//Infrared
	bool getInfrared();
	//Battery
	float getVoltage(void);
	int getBatteryLevel(void);
	//Ultrasonic
	int getUsDist(String pos);
	//Bumper
	byte getBumper(String side);
	byte getInterruptFlag();
	void resetInterruptFlag();
	//Joystick
	int getJoystickY(void);
	int getJoystickX(void);
	bool getJoystickClic(void);
	//Servo
	void setServo(int);
	int getServo(void);
	//Accelerometer
	float getAccelX(void);
	float getAccelY(void);
	float getAccelZ(void);
	float getGyroX(void);
	float getGyroY(void);
	float getGyroZ(void);
	float getTemp(void);
	//Encoder
	long getEncoder(String side);
	void resetEncoder(String side);
	// WIFI
	void sendWifiCmd(char *cmd);
	void waitWifiResult(void);
	void displayWifiAnswer(void);
	//test
	void test(void);
	
private:

	//<<vars>>
	int ledLevel;
	const byte bumperLeft = 2;
	const byte bumperRight = 3;
	const byte infrared = 6;
	const byte leftEncoA = 18;
	const byte leftEncoB = 29;
	const byte rightEncoA = 27;
	const byte rightEncoB = 19;
	const byte pinUsFront = 8;
	const byte pinUsBack =	10;
	const byte pinServo = 12;
	const byte battery = A0;
	const byte joystickX = A2;
	const byte joystickY = A3;
	char ap_buf[30][16];
	int ap_cnt =0;
	





	//<<functions>>	
	static void leftCB ();
	static void rightCB ();
	void waitSerial(void);
	void testEncoderBackL(void);
	void testEncoderBackR(void);

	
};

extern MARK mark;



