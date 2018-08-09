#include "MARK.h" //include the declaration for this class

Grove_LED_Bar bar(5, 4, 0);
LSM6DS3 myIMU( I2C_MODE, 0x6A );  //I2C device address 0x6A
//<<constructor>> 
MARK::MARK(void){
	
	bar.begin();
	bar.setBits(0x3ff);	
	 myIMU.begin();
}
 
//<<destructor>>
MARK::~MARK(void){/*nothing to destruct*/}
 

void MARK::setLedBar(int level){
         bar.setLevel(level);
}
 
float MARK::getAccelX(){
        return(myIMU.readFloatAccelX());
}