int analogPin =9;
long int sensorValue = 0;

void setup() 
{
  Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);            //Configure LED as output
}

void loop() 
{ 
    sensorValue = analogRead(analogPin);
    if (sensorValue == HIGH)
    {digitalWrite(LED_BUILTIN, sensorValue);}; //Turn ON LED
   // delay(1000);
    if (sensorValue == LOW) 
    {digitalWrite(LED_BUILTIN, sensorValue);};  //Turn LOW LED
  //  delay(1000);
}
