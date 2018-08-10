#include "MARK.h" //include the declaration for this class

Grove_LED_Bar bar(5, 4, 0);
rgb_lcd lcd;

//volatiles variables for interruptions
volatile long left_timestamp; //used to stamp start time of an IR pulse
volatile long left_timestampdiff; //used to stamp start time of an IR pulse
volatile long right_timestamp; //used to stamp start time of an IR pulse
volatile long right_timestampdiff; //used to stamp start time of an IR pulse

void * (*leftBumperInterruptionAdress)(void)=NULL;

//<<constructor>> 
MARK::MARK(void){
	
	//LED BAR
	ledLevel =0;
	
	//BUMPERS
	left_timestamp = 0; //used to stamp start time of an IR pulse
	left_timestampdiff = 0; //used to stamp start time of an IR pulse

	right_timestamp = 0; //used to stamp start time of an IR pulse
	right_timestampdiff = 0; //used to stamp start time of an IR pulse

	pinMode(bumperLeft, INPUT_PULLUP);
	pinMode(bumperRight, INPUT_PULLUP);
	
	

}

//<<destructor>>
MARK::~MARK(void){/*nothing to destruct*/}
 
 bool MARK::begin(void){
	 
	//<<LED BAR>>
	bar.begin();
	bar.setBits(0x3ff);	
	
	//<<LCD>>
	lcd.begin(16, 2); //init lcd
  
	//MOTOR
	Motor.begin(I2C_ADDRESS); //init motors
	
	//BUMPERS
	attachInterrupt(digitalPinToInterrupt(bumperLeft), leftCB, CHANGE);
	attachInterrupt(digitalPinToInterrupt(bumperRight), rightCB, CHANGE);
	
	return true;
}

 bool MARK::begin(void (*ptrfonction)(void)){
	
	begin();
	leftBumperInterruptionAdress=ptrfonction;
	return true;
}
/***************************************************/
/**************LED BAR******************************/
/***************************************************/

//<<getter>>
int MARK::getLedBarLevel(void){
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
 
 void MARK::setLcdRGB(unsigned char r, unsigned char g, unsigned char b){
	lcd.setRGB(r, g, b);      
}

 void MARK::setLcdCursor(uint8_t position, uint8_t line){
	lcd.setCursor(position, line);
}

 void MARK::lcdPrint(String data){
	lcd.print(data);    
}
 void MARK::lcdPrint(float data){
	lcd.print(data);    
}

 void MARK::lcdHome(void){
	lcd.home();
}

 void MARK::lcdClear(void){
	lcd.clear();    
}

/***************************************************/
/**************** BUMPERS **************************/
/***************************************************/

 void MARK::leftCB(void){
  left_timestampdiff =  micros() - left_timestamp ;
  if (left_timestampdiff > 10000)
  { 
    Serial.println("Left");
	(*leftBumperInterruptionAdress)();
    left_timestamp = micros() ;
  }
}
 
  void MARK::rightCB(void){
  right_timestampdiff =  micros() - right_timestamp ;
  if (right_timestampdiff > 10000)
  {
    Serial.println("Right");
	
    right_timestamp = micros() ;
  }
}

void MARK::leftCB(){
	//right_timestampdiff =  micros() - right_timestamp ;
	//if (right_timestampdiff > 10000)
	//{
	//	Serial.print("left");
	//	right_timestamp = micros() ;
	//}
	Serial.print("bonjour");
}
 
void MARK::rightCB(){
	//Serial.print("right");
}

/***************************************************/
/**************** MOTOR ****************************/
/***************************************************/
void MARK::setLeftMotor(int _speed){
	Motor.speed(MOTOR1, _speed);
}

void MARK::setRighMotor(int _speed){
	Motor.speed(MOTOR2, _speed);
}

void MARK::stopLeftMotor(){
	Motor.stop(MOTOR1);
}

void MARK::stopRightMotor(){
	Motor.stop(MOTOR2);
}


/***************************************************/
/**************TO DELETE AT THE END*****************/
/***************************************************/
 
 bool MARK::test(void){
	lcdClear();
	setLedBarLevel(10);
	setLcdRGB(255,0,0);
	Serial.println("test");
	delay(300);
	setLcdRGB(0,255,0);
	setLedBarLevel(5);
	delay(300);
	setLcdRGB(0,0,255);
	setLedBarLevel(0);
	delay(1000);
	setLcdCursor(0,0);
	lcdPrint("Salut");
	return true;
}