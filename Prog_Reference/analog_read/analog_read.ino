void setup() 
{
  Serial.begin(9600);

 // digitalWrite(4, HIGH);
}

void loop() 
{
{
    // int sensorValue = digitalRead(5);
   int sensorValue = analogRead(36);
 // Serial.print("sensorValue ");
 // Serial.print(sensorValue);
 // Serial.print("   ");
 // sensorValue = map(sensorValue, 0, 100, 0, 1023);
  Serial.println(sensorValue);
}
 /* 
  Serial.print("A0      ");
  
  int sensorValue1 = analogRead(A4);
  Serial.print(sensorValue1);
  
  Serial.print("A4      ");
  
  int sensorValue2 = analogRead(A5);
  Serial.print(sensorValue2);
  
  Serial.println("A5      ");
  */
}
