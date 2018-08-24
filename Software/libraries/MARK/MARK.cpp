#include "MARK.h" //include the declaration for this class

Grove_LED_Bar bar(5, 4, 0);
rgb_lcd lcd;
Ultrasonic usFront(8);
Ultrasonic usBack(10);
Servo myServo;
LSM6DS3 myIMU( I2C_MODE, 0x6A );
Encoder knobLeft(18, 29);
Encoder knobRight(27, 19);


//volatiles variables for interruptions
volatile byte stateBumperLeft = LOW;
volatile byte stateBumperRight = LOW ;
volatile byte interruptFlag = LOW;
volatile long left_timestamp; //used to stamp start time of an IR pulse
volatile long left_timestampdiff; //used to stamp start time of an IR pulse
volatile long right_timestamp; //used to stamp start time of an IR pulse
volatile long right_timestampdiff; //used to stamp start time of an IR pulse

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
	Serial.println("LED BAR ");
	bar.begin();	

	//<<LCD>>
	Serial.println("- LCD ");
	lcd.begin(16, 2); //init lcd
  
	//<<MOTOR>>
	Serial.println("- MOTOR ");
	Motor.begin(I2C_ADDRESS); //init motors
	
	//<<WIFI>>
	Serial.println("- WIFI ");
	Serial3.begin(115200); //Init serial connection on port 3 for wifi
	Wire.begin();

	//<<BUMPERS>>
	Serial.println("- BUMPERS ");
	if(digitalRead(bumperRight)>126){
		stateBumperRight = !stateBumperRight;
	}
	if(digitalRead(bumperLeft)>126){
		stateBumperLeft = !stateBumperLeft;
	}

	attachInterrupt(digitalPinToInterrupt(bumperLeft), leftCB, CHANGE);
	attachInterrupt(digitalPinToInterrupt(bumperRight), rightCB, CHANGE);

	//<Servo>
	Serial.println("- SERVO ");
	myServo.attach(pinServo);

	//<IMU>
	Serial.println("- IMU ");
	myIMU.begin();
	
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
    stateBumperLeft = !stateBumperLeft;
    interruptFlag=HIGH;
	
    left_timestamp = micros() ;
  }
}
 
  void MARK::rightCB(void){
  right_timestampdiff =  micros() - right_timestamp ;
  if (right_timestampdiff > 10000)
  {
    stateBumperRight=!stateBumperRight;
    interruptFlag=HIGH;
	right_timestamp = micros() ;
  }
}

byte MARK::getBumper(String _side){
	if(_side == "Right" || _side == "right" || _side == "RIGHT" || _side == "r" || _side == "R"){
		return(stateBumperRight);
	}
	if(_side == "Left" || _side == "left" || _side == "LEFT" || _side == "l" || _side == "L"){
		return(stateBumperLeft);
	}
}

byte MARK::getInterruptFlag(void){
	return(interruptFlag);
	
}
void MARK::resetInterruptFlag(void){
	interruptFlag = LOW;
	
}
/***************************************************/
/**************** MOTOR ****************************/
/***************************************************/
void MARK::setLeftMotor(int _speed){
	Motor.speed(MOTOR1, _speed);
}

void MARK::setRightMotor(int _speed){
	Motor.speed(MOTOR2, _speed);
}

void MARK::stopLeftMotor(void){
	Motor.stop(MOTOR1);
}

void MARK::stopRightMotor(void){
	Motor.stop(MOTOR2);
}

/***************************************************/
/************** INFRARED ***************************/
/***************************************************/
bool MARK::getInfrared(void){
	return(digitalRead(infrared));
}

/***************************************************/
/************** BATTERY ****************************/
/***************************************************/
float MARK::getVoltage(void){
	float voltage = analogRead(battery);
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
/************** JOYSTICK ***************************/
/***************************************************/
int MARK::getJoystickY(void){
	return(analogRead(joystickY));
}

int MARK::getJoystickX(void){
		return(analogRead(joystickX));
}

bool MARK::getJoystickClic(void){
	if(analogRead(joystickX) == 1023){
		return(true);
	}
	else {return(false);}
}

/***************************************************/
/************** SERVO ******************************/
/***************************************************/
void MARK::setServo(int _pos){
	myServo.write(_pos);
}

int MARK::getServo(void){
	return(myServo.read());
}

/***************************************************/
/************** ACCELEROMETER **********************/
/***************************************************/
float MARK::getAccelX(void){
	return(myIMU.readFloatAccelX());
}
float MARK::getAccelY(void){
	return(myIMU.readFloatAccelY());
}
float MARK::getAccelZ(void){
	return(myIMU.readFloatAccelZ());
}
float MARK::getGyroX(void){
	return(myIMU.readFloatGyroX());
}
float MARK::getGyroY(void){
	return(myIMU.readFloatGyroY());
}
float MARK::getGyroZ(void){
	return(myIMU.readFloatGyroZ());
}
float MARK::getTemp(void){
	return(myIMU.readTempC());
}

/***************************************************/
/************** ENCODER ****************************/
/***************************************************/
long MARK::getEncoder(String _side){
	if(_side == "Right" || _side == "right" || _side == "RIGHT" || _side == "r" || _side == "R"){
		return(knobRight.read());
	}
	if(_side == "Left" || _side == "left" || _side == "LEFT" || _side == "l" || _side == "L"){
		return(knobLeft.read());
	}
}

void MARK::resetEncoder(String _side){
	if(_side == "Right" || _side == "right" || _side == "RIGHT" || _side == "r" || _side == "R"){
		knobRight.write(0);
	}
	if(_side == "Left" || _side == "left" || _side == "LEFT" || _side == "l" || _side == "L"){
		knobLeft.write(0);
	}
}

/***************************************************/
/***************** WIFI ****************************/
/***************************************************/
void MARK::sendWifiCmd(char *cmd){
	Serial.println(cmd);
   // if(NULL == cmd)return;
    Serial3.println(cmd);
}
void MARK::waitWifiResult(void)
{
	ap_cnt = 0;
    while(1)
    {
LOOP1:
        char c1=0;
        if(Serial3.available()>=2)
        {
            c1 = Serial3.read();
            if(c1 == 'O' && 'K' == Serial3.read()){
            	return;       // OK means over
            }
        }
        
        if('('==c1)
        {
            while(Serial3.available()<3);
            Serial3.read();
            Serial3.read();
            Serial3.read();

            int d = 0;
            while(1)
            {
                if(Serial3.available() && '"' == Serial3.read());      // find "
                {
                    while(1)
                    {
                        if(Serial3.available())
                        {
                            char c = Serial3.read();
                            ap_buf[ap_cnt][d++] = c; //save datas on buffer
                            if(c == '"' || d==16)
                            {
                                ap_buf[ap_cnt][d-1] = '\0';
                                ap_cnt++;
                                goto LOOP1;
                            }
                        }
                    }
                }
            }
        }
    }
}

void MARK::displayWifiAnswer(void)
{
    char strtmp[16];
    Serial.println(strtmp);        // Print the String

    int cnt = ap_cnt;
    int offset = 0;
    while(1)
    {
        if(cnt>=8)
        {
            for(int i=0; i<8; i++)
            {
                Serial.println(ap_buf[8*offset+i]);
            }
            cnt-=8;
            offset++;
        }
        else 
        {
            for(int i=0; i<cnt; i++)
            {
                Serial.println(ap_buf[8*offset+i]);
            }
            return;
        }
        delay(2000);
    }
}