

#include <elapsedMillis.h>


void setup() 
{
  Serial.begin(9600);  
  pinMode(23, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  pinMode(41, INPUT);
  pinMode(43, INPUT);
  pinMode(45, INPUT);
  pinMode(47, INPUT);
  pinMode(49, INPUT);
  pinMode(51, INPUT);
  pinMode(53, INPUT);


 // digitalWrite(4, HIGH);
}

void loop() 
{
  /*
starttime = millis();
endtime = starttime;
While ((endtime - starttime) <=1000) // do this loop for up to 1000mS
{
serial.print (loopcount,DEC);
  */
{
    int sensorValue = digitalRead(23);
    int sensorValue1 = digitalRead(25);
    int sensorValue2 = digitalRead(27);
    int sensorValue3 = digitalRead(29);
    int sensorValue4 = digitalRead(31);
    int sensorValue5 = digitalRead(33);
    int sensorValue6 = digitalRead(35);
    int sensorValue7 = digitalRead(37);
    int sensorValue8 = digitalRead(39);
    int sensorValue9 = digitalRead(41);
    int sensorValue10 = digitalRead(43);
    int sensorValue11 = digitalRead(45);
    int sensorValue12 = digitalRead(47);
    int sensorValue13 = digitalRead(49);
    int sensorValue14 = digitalRead(51);
    int sensorValue15 = digitalRead(53);
  Serial.print(sensorValue);Serial.print("  ");
  Serial.print(sensorValue1);Serial.print("  ");
  Serial.print(sensorValue2);Serial.print("  ");
  Serial.print(sensorValue3);Serial.print("  ");
  Serial.print(sensorValue4);Serial.print("  ");
  Serial.print(sensorValue5);Serial.print("  ");
  Serial.print(sensorValue6);Serial.print("  ");
  Serial.print(sensorValue7);Serial.print("  ");
  Serial.print(sensorValue8);Serial.print("  ");
  Serial.print(sensorValue9);Serial.print("  ");
  Serial.print(sensorValue10);Serial.print("  ");
  Serial.print(sensorValue11);Serial.print("  ");
  Serial.print(sensorValue12);Serial.print("  ");
  Serial.print(sensorValue13);Serial.print("  ");
  Serial.print(sensorValue14);Serial.print("  ");
  Serial.print(sensorValue15);Serial.println("  ");
}
//loopcount = loopcount+1;
//endtime = millis();
}

