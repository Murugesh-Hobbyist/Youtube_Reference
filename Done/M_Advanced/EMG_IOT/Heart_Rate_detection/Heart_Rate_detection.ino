
int PulseSensorPurplePin = 36;
int Signal;
int Change;

void setup() 
{ Serial.begin(9600); }

void loop() 
{
Signal = analogRead(PulseSensorPurplePin);
if (Signal < 500)
  {
    Change = 75;
    Serial.println(Change);
    delay(1000);
  }

if (Signal > 2500)
  {
    Change = 0;
    Serial.println(Change);
  }
}
