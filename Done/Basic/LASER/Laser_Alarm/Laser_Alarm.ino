int Sensor_Pin = A0;

void setup()
{
  Serial.begin(9600);
  pinMode(Sensor_Pin, INPUT);
  pinMode(13, OUTPUT);
}

void loop() 
{      
    int Sensor_Value = analogRead(Sensor_Pin);
    Serial.println(Sensor_Value);
  
    if (Sensor_Value < 30)
       {digitalWrite(13, HIGH);
       delay(5000);}
    if (Sensor_Value <30) 
       {digitalWrite(13, LOW);}
}
