int Sensor_Pin = A0;

void setup()
{
  Serial.begin(9600);
  pinMode(Sensor_Pin, INPUT);
  pinMode(8, OUTPUT);
}

void loop() 
{      
    int Sensor_Value = analogRead(Sensor_Pin);
    Serial.println(Sensor_Value);
  
    if (Sensor_Value < 600)
       {digitalWrite(8, HIGH);}
    if (Sensor_Value > 600) 
       {digitalWrite(8, LOW);}
}
