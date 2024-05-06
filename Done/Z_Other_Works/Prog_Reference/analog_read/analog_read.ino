void setup() 
{
      Serial.begin(9600);
  //Serial.begin(115200);

 // digitalWrite(4, HIGH);
 
    pinMode(37, INPUT_PULLUP);
}

void loop() 
{
{
     int sensorValue = digitalRead(37);
  // int sensorValue = analogRead(9);
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
