#include "MARK.h" //include the declaration for this class

Grove_LED_Bar bar(5, 4, 0);

//<<constructor>> 
MARK::MARK(void){
	
	bar.begin();
	bar.setBits(0x3ff);	
}
 
//<<destructor>>
MARK::~MARK(void){/*nothing to destruct*/}
 

void MARK::setLedBar(int level){
         bar.setLevel(level);
}
 
