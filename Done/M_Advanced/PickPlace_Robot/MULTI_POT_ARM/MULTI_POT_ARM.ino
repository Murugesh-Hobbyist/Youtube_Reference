void setup() 
{
  Serial.begin(9600);
 // digitalWrite(4, HIGH);
}

void loop() 
{
{
      int sensorValue_A0 = analogRead(A0);
      int sensorValue_A1 = analogRead(A1);
      int sensorValue_A2 = analogRead(A2);
      int sensorValue_A3 = analogRead(A3);
      int sensorValue_A4 = analogRead(A4);
      int sensorValue_A5 = analogRead(A5);
      int sensorValue_B1 = digitalRead(8);
      int sensorValue_B2 = digitalRead(7);
      int sensorValue_B3 = digitalRead(4);
  //  int sensorValue = digitalRead(A0);
 // Serial.print("sensorValue ");
 // Serial.print(sensorValue);
 // Serial.print("   ");
 // sensorValue = map(sensorValue, 0, 100, 0, 1023);
  Serial.print("   A0 -> ");
  Serial.print(sensorValue_A0);
  Serial.print( "  " );
  Serial.print(" A1 -> ");
  Serial.print(sensorValue_A1);
  Serial.print( "  " );
  Serial.print(" A2 -> ");
  Serial.print(sensorValue_A2);
  Serial.print( "  " );
  Serial.print(" A3 -> ");
  Serial.print(sensorValue_A3);
  Serial.print( "  " );
  Serial.print(" A4 -> ");
  Serial.print(sensorValue_A4);
  Serial.print( "  " );
  Serial.print(" A5 -> ");
  Serial.print(sensorValue_A5);
  Serial.print( "  " );
  Serial.print(" B1 -> ");
  Serial.print(sensorValue_B1);
  Serial.print( "  " );
  Serial.print(" B2 -> ");
  Serial.print(sensorValue_B2);
  Serial.print( "  " );
  Serial.print(" B3 -> ");
  Serial.print(sensorValue_B3);
  Serial.println( "  " );
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
