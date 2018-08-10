#include "MARK.h" //include the declaration for this class

Grove_LED_Bar bar(5, 4, 0);
rgb_lcd lcd;


//<<constructor>> 
MARK::MARK(void){
	
	//LED BAR
	ledLevel =0;
}
 	
//<<destructor>>
MARK::~MARK(void){/*nothing to destruct*/}
 
 bool MARK::setup(){
	 
	//<<LED BAR>>
	bar.begin();
	bar.setBits(0x3ff);	
	
	//<<LCD>>
	lcd.begin(16, 2); //init lcd
  
	
	
	
	return true;
}
 
/***************************************************/
/**************LED BAR******************************/
/***************************************************/

//<<getter>>
int MARK::getLedBarLevel(){
         return(ledLevel);
}

//<<setter>>
bool MARK::setLedBarLevel(int data){
	if(data<=10){
	ledLevel=data;
	bar.setLevel(ledLevel);
	 
	 return true;
	}
    else{
		return false;
	} 
}
/***************************************************/
/**************** LCD ******************************/
/***************************************************/
 
 bool MARK::setLcdRGB(int R, int G, int B){
	   lcd.setRGB(R, G, B); 

         return true;
}

  
 
/***************************************************/
/**************TO DELETE AT THE END*****************/
/***************************************************/
 
 bool MARK::test(){
	setLedBarLevel(10);
	setLcdRGB(255,0,0);
	Serial.println("test");
	delay(300);
	setLcdRGB(0,255,0);
	setLedBarLevel(5);
	delay(300);
	setLcdRGB(0,0,255);
	setLedBarLevel(0);
	delay(300);
	return true;
}