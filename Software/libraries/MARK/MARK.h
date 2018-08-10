#include "Arduino.h"
#include "Wire.h"
#include "Grove_LED_Bar.h"
#include "SparkFunLSM6DS3.h"
#include "rgb_lcd.h"


#ifndef MARK_H
#define MARK_H
#endif



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
	static void leftCB ();
	static void rightCB ();
	
	
	
	
};


