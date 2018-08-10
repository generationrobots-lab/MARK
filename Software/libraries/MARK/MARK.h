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
	bool setup(); //return true if done
	bool test(); //return true if done
	bool setLcdRGB(int R, int G, int B); //set lcd color, return true if done
private:
	int ledLevel;
};


