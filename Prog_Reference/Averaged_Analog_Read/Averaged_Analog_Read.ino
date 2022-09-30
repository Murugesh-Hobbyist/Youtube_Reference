int analogPin = A0;
const int averageValue = 500;
long int sensorValue = 0;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  for (int i = 0; i < averageValue; i++)
  {
    sensorValue += analogRead(analogPin);
    delay(2);
  }
  sensorValue = sensorValue / averageValue;
  Serial.print("Average Analog Value: ");
  Serial.println(sensorValue);
}
