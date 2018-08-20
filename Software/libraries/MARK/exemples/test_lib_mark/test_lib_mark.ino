#include <MARK.h>

MARK myrobot;//initialize an instance of the class
int pos;
bool parechoc = 0;
bool joy = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("init done");
  myrobot.begin();
}

void loop() {
  //bumper();
  //accelerometer();
  Voltage();
  //encoder();
  //distance();
  //servo();
  joystick();
  delay(300);
}

void distance(void){
  Serial.print("front us");
  Serial.println(myrobot.getUsDist("front"));
  Serial.print("back us");
  Serial.println(myrobot.getUsDist("back"));
}

void bumper() {
  Serial.print("my bumper r : ");
  Serial.print(myrobot.getBumper("r"));
  Serial.print(" my bumper l : ");
  Serial.println(myrobot.getBumper("l"));
  if (myrobot.getBumper("r") == 0) {
    myrobot.setLeftMotor(-100);
    myrobot.setRightMotor(-100);
    parechoc = 0 ;
  } else {
    parechoc = 1 ;
    if(joy==0){
      myrobot.stopLeftMotor();
      myrobot.stopRightMotor();
    }
  }
}

  void joystick() {
  if (parechoc = 1) {
    joy = 1;
    Serial.print("joy ");
    Serial.println(map(myrobot.getJoystickY(), 268, 775, -100, 100));
    myrobot.setLeftMotor(map(myrobot.getJoystickY(), 268, 775, -100, 100));
    myrobot.setRightMotor(map(myrobot.getJoystickY(), 268, 775, -100, 100));
  } else {
    joy = 0;
    myrobot.stopLeftMotor();
    myrobot.stopRightMotor();
  }
}
  
  void servo() {
  myrobot.setServo(map(myrobot.getJoystickX(), 210, 755, 180, 0));
  Serial.print("myservo :");
  Serial.println(myrobot.getServo());
  //myrobot.setLedBarLevel(map(myrobot.getJoystickX(), 200, 755, 0, 10));
  }

  void accelerometer() {
  Serial.print("Accel X  ");
  Serial.println(myrobot.getAccelX());

  Serial.print("Accel Y  ");
  Serial.println(myrobot.getAccelY());

  Serial.print("Accel Z  ");
  Serial.println(myrobot.getAccelZ());

  Serial.print("Gyro X  ");
  Serial.println(myrobot.getGyroX());

  Serial.print("Gyro Y  ");
  Serial.println(myrobot.getGyroY());

  Serial.print("Gyro Z  ");
  Serial.println(myrobot.getGyroZ());

  Serial.print("Temp     ");
  Serial.println(myrobot.getTemp());
  }

void Voltage(void) {
  myrobot.lcdClear();
  myrobot.lcdHome();
  myrobot.lcdPrint(myrobot.getVoltage());
  Serial.println(myrobot.getBatteryLevel());
  myrobot.setLedBarLevel(myrobot.getBatteryLevel() / 10);
}

void setScreenOff(void) {
  Serial.print("Bar Level : ");
  Serial.println(myrobot.getLedBarLevel());
}

void encoder(void){
  Serial.print("r encoder : ");
  Serial.println(myrobot.getEncoder("r"));
  Serial.print("l encoder : ");
  Serial.println(myrobot.getEncoder("l"));
  if(myrobot.getEncoder("l") > 1000 || myrobot.getEncoder("r") > 10000){
    myrobot.resetEncoder("r");
    myrobot.resetEncoder("l");
  }
}

