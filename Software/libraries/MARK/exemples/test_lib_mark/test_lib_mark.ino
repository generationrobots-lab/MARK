#include "MARK.h"
 
MARK myrobot;//initialize an instance of the class
 
void setup(){Serial.begin(9600); myrobot.begin(setScreenOff);Serial.println("init done");/*nothing to setup*/}
 
void loop(){
  myrobot.test();
  Serial.println(myrobot.getLedBarLevel());
  delay(1000);
}   

void setScreenOff(void){
  Serial.print("Bar Level : ");
  Serial.println(myrobot.getLedBarLevel());

}

