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
	MARK(void);
	~MARK(void);
	bool setLedBarLevel(int level);
	int getLedBarLevel();
	bool begin(); //return true if done
	void setLcdRGB(unsigned char r, unsigned char g, unsigned char b); //set lcd color, return true if done
	void lcdPrint(String text);
	void setLcdCursor(uint8_t, uint8_t);
	void lcdHome();
	void lcdClear();
	
	//to delete
	bool test(); //return true if done
private:
	int ledLevel;
};


