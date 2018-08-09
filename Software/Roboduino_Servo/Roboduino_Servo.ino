/*
    Description : The servo motor sweeps the aera
    library : https://www.arduino.cc/en/reference/servo
*/
#include <Servo.h>

Servo myservo; //Init lib servo

int pos = 0; //Initialise position 

void setup() {
  myservo.attach(12); //Connect servo to pin 12
  myservo.write(pos);
}

void loop() {
  //sweep servo between 0 and 130 degrees
  
  for (pos = 0; pos <= 130; pos += 1) { 
    myservo.write(pos);
    delay(15); 
  }
  
  for (pos = 130; pos >= 0; pos -= 1) { 
    myservo.write(pos);
    delay(15); 
  }
}
