#include "MARK.h" //include the declaration for this class

Grove_LED_Bar bar(5, 4, 0);
rgb_lcd lcd;
Ultrasonic usFront(8);
Ultrasonic usBack(10);

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
	
	pinMode(infrared, INPUT);
	
	pinMode(battery, INPUT);
}

//<<destructor>>
MARK::~MARK(void){/*nothing to destruct*/}
 
 bool MARK::begin(void){
	 
	//<<LED BAR>>
	bar.begin();	
	//<<LCD>>
	lcd.begin(16, 2); //init lcd
  
	//<<MOTOR>>
	Motor.begin(I2C_ADDRESS); //init motors
	
	//<<BUMPERS>>
	/*attachInterrupt(digitalPinToInterrupt(bumperLeft), leftCB, CHANGE);
	attachInterrupt(digitalPinToInterrupt(bumperRight), rightCB, CHANGE);*/
	
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
    //Serial.println("Left");
	(*leftBumperInterruptionAdress)();
    left_timestamp = micros() ;
  }
}
 
  void MARK::rightCB(void){
  right_timestampdiff =  micros() - right_timestamp ;
  if (right_timestampdiff > 10000)
  {
    //Serial.println("Right");
	right_timestamp = micros() ;
  }
}

bool MARK::getBumper(String _side){
	if(_side == "Right" || _side == "right" || _side == "RIGHT" || _side == "r" || _side == "R"){
		return(digitalRead(bumperRight));
	}
	if(_side == "Left" || _side == "left" || _side == "LEFT" || _side == "l" || _side == "L"){
		return(digitalRead(bumperLeft));
	}
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
/************** INFRARED ***************************/
/***************************************************/
bool MARK::gedInfrared(void){
	return(digitalRead(infrared));
}

/***************************************************/
/************** BATTERY ****************************/
/***************************************************/
float MARK::getVoltage(void){
	float voltage = analogRead(A0);
	return((3 * voltage * 4980 / 1023.00)); //set gain to 3 on divider board
}
int MARK::getBatteryLevel(void){
	return(map(getVoltage(), 6500, 8400, 0, 100));
}

/***************************************************/
/************** ULTRASONIC *************************/
/***************************************************/
int MARK::getUsDist(String _pos){
	if(_pos == "Front" || _pos == "front" || _pos == "FRONT" ||_pos == "F" || _pos == "f"){
		return(usFront.MeasureInCentimeters());
	}
	if(_pos == "Back" || _pos == "back" || _pos == "BACK" || _pos == "B" ||_pos == "b"){
		return(usBack.MeasureInCentimeters());
	}
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