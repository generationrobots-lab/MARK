#include "Arduino.h"
#include "Wire.h"
#include "Grove_LED_Bar.h"
#include "SparkFunLSM6DS3.h"

#ifndef MARK_H
#define MARK_H
#endif



class MARK {
public:
	MARK(void);
	~MARK(void);
	void setLedBar(int level);
	float getAccelX();
	
	
private:
	

};


