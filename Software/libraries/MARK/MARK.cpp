#include "MARK.h" //include the declaration for this class

Grove_LED_Bar bar(5, 4, 0);
//<<constructor>> 
MARK::MARK(void){
	ledLevel =0;
}
 	
//<<destructor>>
MARK::~MARK(void){/*nothing to destruct*/}
 
 bool MARK::setup(){
	bar.begin();
	bar.setBits(0x3ff);	
	
	return true;
}
 
/***************************************************/
/**************LED BAR******************************/
/***************************************************/

int MARK::getLedBarLevel(){
         return(ledLevel);
}
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
/**************TO DELETE AT THE END*****************/
/***************************************************/
 
 bool MARK::test(){
	setLedBarLevel(10);
	delay(300);
	setLedBarLevel(5);
	delay(300);
	setLedBarLevel(0);
	delay(300);
	return true;
}