void setup() 
{
  Serial.begin(9600);
 // digitalWrite(4, HIGH);
}

void loop() 
{
  
  int sensorValue1 = analogRead(A1);
  Serial.print("A1 --> ");
  Serial.print(sensorValue1);
  int sensorValue2 = analogRead(A2);
  Serial.print("  A2 --> ");
  Serial.print(sensorValue2);
  int sensorValue3 = analogRead(A3);
  Serial.print("  A3 --> ");
  Serial.print(sensorValue3);
  int sensorValue4 = analogRead(A4);
  Serial.print("  A4 --> ");
  Serial.println(sensorValue4);
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
