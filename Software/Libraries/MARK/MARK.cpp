/*
   _____ _____  _               ____  
  / ____|  __ \| |        /\   |  _ \ 
 | |  __| |__) | |       /  \  | |_) |
 | | |_ |  _  /| |      / /\ \ |  _ < 
 | |__| | | \ \| |____ / ____ \| |_) |
  \_____|_|  \_\______/_/    \_\____/

  */

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
	Serial.println("- LED BAR ");
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

byte MARK::getBumper(String side){
	if(side == "Right" || side == "right" || side == "RIGHT" || side == "r" || side == "R"){
		return(stateBumperRight);
	}
	if(side == "Left" || side == "left" || side == "LEFT" || side == "l" || side == "L"){
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
void MARK::setLeftMotor(int speed){
	Motor.speed(MOTOR1, speed);
}

void MARK::setRightMotor(int speed){
	Motor.speed(MOTOR2, speed);
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
	return(map(getVoltage(), 6000, 8400, 0, 10));
}

/***************************************************/
/************** ULTRASONIC *************************/
/***************************************************/
int MARK::getUsDist(String pos){
	if(pos == "Front" || pos == "front" || pos == "FRONT" ||pos == "F" || pos == "f"){
		return(usFront.MeasureInCentimeters()*10);
	}
	if(pos == "Back" || pos == "back" || pos == "BACK" || pos == "B" ||pos == "b"){
		return(usBack.MeasureInCentimeters()*10);
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
void MARK::setServo(int pos){
	myServo.write(pos);
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
long MARK::getEncoder(String side){
	if(side == "Right" || side == "right" || side == "RIGHT" || side == "r" || side == "R"){
		return(knobRight.read());
	}
	if(side == "Left" || side == "left" || side == "LEFT" || side == "l" || side == "L"){
		return(knobLeft.read());
	}
}

void MARK::resetEncoder(String side){
	if(side == "Right" || side == "right" || side == "RIGHT" || side == "r" || side == "R"){
		knobRight.write(0);
	}
	if(side == "Left" || side == "left" || side == "LEFT" || side == "l" || side == "L"){
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
    //sprintf(strtmp, "get %d ap : ", ap_cnt);
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

void MARK::test(void){
	//test motors
	Serial.println("Start MOTOR forward - ");
	setLeftMotor(100);
	setRightMotor(100);
	Serial.println("press enter if ok ");
	waitSerial();
	delay(5);
	stopLeftMotor();
	stopRightMotor();
	
	//test encoder
	Serial.println("Start ENCODER - ");
	int enco_left_prev = getEncoder("l");
	setLeftMotor(100);
	delay(100);
	setLeftMotor(0);
	int enco_left = getEncoder("l");
	if(enco_left_prev<enco_left){
		testEncoderBackL();
	}else{
		Serial.println("you must exchange pos of 2 data wire of left encoder ");
	}
	delay(1000);

	int enco_right_prev = getEncoder("r");
	setRightMotor(100);
	delay(100);
	setRightMotor(0);
	int enco_right = getEncoder("r");
	if(enco_right_prev<enco_right){
		testEncoderBackR();
	}else{
		Serial.println("you must exchange pos of 2 data wire of right encoder ");
	}

	//test led bar
	Serial.println("Start LED BAR - ");
	for(int i=10; i-- ;i==0){
		Serial.println(i);
		setLedBarLevel(i);
		delay(500);
	}
	Serial.println("press enter if ok ");
	waitSerial();
	setLedBarLevel(0);

	//test LCD
	Serial.println("Start LCD - ");
	int i=0;
	while(i<255){
		i++;
		setLcdRGB(i, 255, 255-i); //set lcd color, return true if done
		delay(20);
	
	}
	Serial.println("press enter if ok ");
	waitSerial();
	setLedBarLevel(0);
	
	//test accelerometer
	Serial.println("Start ACCELEROMETER - ");
	Serial.println("Turn robot x axe ");
	while(getGyroX()>-200 && getGyroX()<200){
		delay(10);
	}
	delay(500);
	Serial.println("Turn robot y axe ");
	while(getGyroY()>-200 && getGyroY()<200){
		delay(10);
	}
	delay(500);
	Serial.println("Turn robot z axe ");
	while(getGyroZ()>-200 && getGyroZ()<200){
		delay(10);
	}
	delay(500);
	Serial.println("Moove on X axe ");
	while(getAccelX()>-0.5&&getAccelX()<0.5){
		delay(10);
	}
	delay(500);
	Serial.println("Moove on Y axe ");
	while(getAccelY()>-0.5&&getAccelY()<0.5){
		delay(10);
	}
	delay(500);
	Serial.println("Moove on Z axe ");
	while(getAccelZ()>0.4&&getAccelY()<1.3){
		delay(10);
	}
	Serial.println("Accelerometer ok");
	
	//test temperature
	Serial.println("Start TEMPERATURE - ");
	Serial.print("temperature is of ");
	Serial.print(getTemp());	
	Serial.println(" degrees");
	Serial.println("press enter if ok ");
	waitSerial();
	
	//test Infrared
	Serial.println("Start INFRARED - ");
	bool infraredvalue=getInfrared();
	Serial.println("try to switch the IR sensor state ");
 	while(getInfrared()==infraredvalue){
	}
	Serial.println("Infrared ok");
	
	//test joystick
	Serial.println("Start JOYSTICK - ");
	Serial.println("Press joystick");
	while(getJoystickClic()!=1){
		delay(10);
	}
	delay(500);
	Serial.println("Moove joystick left");
	while(getJoystickX()>300){
		delay(10);
	}
	delay(500);
	Serial.println("Moove joystick right");
	while(getJoystickX()<700||getJoystickX()>1000){
		delay(10);
	}
	delay(500);
	Serial.println("Moove joystick forward");
	while(getJoystickY()>300){
		delay(10);
	}
	delay(500);
	Serial.println("Moove joystick backward");
	while(getJoystickY()<700){
		delay(10);
	}
	Serial.println("Joystick ok");
	
	//test bumper
	Serial.println("Start BUMPER - ");
	Serial.println("Press right bumper");
	while(getBumper("r")==0){
		delay(10);
	}
	delay(500);
	Serial.println("Press left bumper");
	while(getBumper("l")==0){
		delay(10);
	}
	Serial.println("Bumper ok");
	delay(500);
	
	//test ultrasonic
	Serial.println("Start ULTRASONIC - ");
	Serial.println("Put somethink under 20cm front of the robot");
	while(getUsDist("f")>20){
		delay(10);
	}
	Serial.println("Put somethink under 20cm back of the robot");
	while(getUsDist("b")>20){
		delay(10);
	}
	Serial.println("Ultrasonic ok");
	
	//test servo
	Serial.println("Start SERVO - ");
	setServo(0);
	Serial.println("set servo 0, press enter to valid");
	waitSerial();
	setServo(90);
	Serial.println("set servo 90, press enter to valid");
	waitSerial();
	setServo(180);
	Serial.println("set servo 180, press enter to valid");
	waitSerial();
	setServo(90);	
	Serial.println("press enter if ok ");
	waitSerial();
	
	
	//test diviseur de tension
	Serial.println("Start VOLTAGE DIVIDER - ");
	Serial.println("Please put battery in and set on the switch");
	if(getVoltage()>5000 && getVoltage()<9000){
		Serial.println("Voltage divider ok");
	}else{
		Serial.println("Error voltage divider or battery");
	}
	delay(1000);
	Serial.println("end of the process");

}

void MARK::testEncoderBackL(void){
	delay(1000);
	int enco_prev = getEncoder("l");
	setLeftMotor(-100);
	delay(100);
	setLeftMotor(0);
	int enco = getEncoder("l");
	if(enco_prev>enco){
		Serial.println("left encoder ok");
	}
}
void MARK::testEncoderBackR(void){
	delay(1000);
	int enco_prev = getEncoder("R");
	setRightMotor(-100);
	delay(100);
	setRightMotor(0);
	int enco = getEncoder("r");
	if(enco_prev>enco){
		Serial.println("right encoder ok");
	}
}

void MARK::waitSerial(void){
	while(Serial.read() != -1){
		
	}
	Serial.println("waiting input.. ");
	while(!Serial.available()) ;
	while(1){
 			while(Serial.available()){
			if(Serial.read()==10)return; //wait CR

		 } 
	}
}
