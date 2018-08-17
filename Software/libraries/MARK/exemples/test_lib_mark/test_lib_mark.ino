#include <MARK.h>

MARK myrobot;//initialize an instance of the class
//Servo mservo;
int pos;
bool parechoc = 0;
bool joy = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("init done");
  myrobot.begin();
  /*nothing to setup*/
  //mservo.attach(12);
}

void loop() {
  //bumper();
  //accelerometer();
  Voltage();
  //servo();
  //joystick();
  delay(100);
}

/*void bumper() {
  if (myrobot.getBumperR() == 0) {
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
    Serial.println(map(myrobot.getJoystickY(), 268, 775, 100, -100));
    myrobot.setLeftMotor(map(myrobot.getJoystickY(), 268, 775, 100, -100));
    myrobot.setRightMotor(map(myrobot.getJoystickY(), 268, 775, 100, -100));
  } else {
    joy = 0;
    myrobot.stopLeftMotor();
    myrobot.stopRightMotor();
  }
  }
  void servo() {
  myrobot.servoWrite(map(myrobot.getJoystickX(), 210, 755, 180, 0));
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
  Serial.println(myrobot.getTempC());
  }*/

void Voltage(void) {
  myrobot.lcdClear();
  myrobot.lcdHome();
  myrobot.lcdPrint(myrobot.getVoltage());
  Serial.println(myrobot.getBatteryLevel());
  myrobot.setLedBarLevel(myrobot.getBattery() / 10);
}
/*void getUltrasonic(void) {
  Serial.print("US front \n value : ");
  Serial.print(myrobot.getUsFront());
  Serial.print(" Distance : ");
  Serial.println(myrobot.getUsDistFront());

  Serial.print("US back \n value : ");
  Serial.print(myrobot.getUsBack());
  Serial.print(" Distance : ");
  Serial.println(myrobot.getUsDistBack());
  }*/

void setScreenOff(void) {
  Serial.print("Bar Level : ");
  Serial.println(myrobot.getLedBarLevel());

}

