#include "Arduino.h"
#include "Wire.h"
#include "Grove_LED_Bar.h"
#include "SparkFunLSM6DS3.h"
#include "rgb_lcd.h"
#include "Grove_I2C_Motor_Driver.h"


#ifndef MARK_H
#define MARK_H
#define I2C_ADDRESS 0x0f


class MARK {
public:
	//<<functions>>	
	MARK(void);
	~MARK(void);
	bool setLedBarLevel(int level);
	int getLedBarLevel();
	bool begin(); //return true if done
	void setLcdRGB(unsigned char r, unsigned char g, unsigned char b); //set lcd color, return true if done
	void lcdPrint(String text);
	void lcdPrint(float data);
	void setLcdCursor(uint8_t, uint8_t);
	void lcdHome();
	void lcdClear();
	void setLeftMotor(int _speed);
	void setRighMotor(int _speed);
	void stopLeftMotor();
	void stopRightMotor();
	static void leftCB ();
	
	
	//to delete
	bool test(); //return true if done
private:

	//<<vars>>
	int ledLevel;
	const byte bumperLeft = 2;
	const byte bumperRight = 3;
	volatile byte stateBumperLeft;
	volatile byte stateBumperRight;
	volatile long left_timestamp; //used to stamp start time of an IR pulse
	volatile long left_timestampdiff; //used to stamp start time of an IR pulse
	volatile long right_timestamp; //used to stamp start time of an IR pulse
	volatile long right_timestampdiff; //used to stamp start time of an IR pulse


	//<<functions>>	
	
	static void rightCB ();
	
};
#endif

