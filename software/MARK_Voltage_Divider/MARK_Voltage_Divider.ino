/*
   Description : the led bar indicate the batterie level.
   more informations : http://wiki.seeedstudio.com/Grove-Voltage_Divider/
*/

#include <Grove_LED_Bar.h>

Grove_LED_Bar bar(5, 4, 0);  // Clock pin, Data pin, Orientation
long sumVoltage = 0;

byte ledbar;

void setup()
{
  Serial.begin(9600); //Initialisation of serial connection. 
  bar.begin();  //Initialisation of LED bar
  bar.setBits(0x3ff); 
  delay(1000);
  bar.setBits(0x0);
}

void loop()
{
  long  sumVoltage = 0; //Variable for average

  //measure voltage 100 times
  for (int i = 0; i < 100; i++)
  {
    sumVoltage = analogRead(A0) + sumVoltage;
    delay(2);
  }
  sumVoltage = sumVoltage / 100; //divise all measure to have 
  sumVoltage = (3 * sumVoltage * 4980 / 1023.00); //set gain to 3
  sumVoltage =  map(sumVoltage, 6000, 8500, 0, 10); //6000 mV (min voltage for 2 cell battery) to 8500mV (max)
  bar.setLevel(sumVoltage); //print value on LED bar

  delay(100);
}
