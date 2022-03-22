int led = 11;//assaign
int brightness = 0;
int fadeAmount = 2;

void setup() 
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  analogWrite(led, brightness);
  brightness = brightness + fadeAmount;
  
  if (brightness <= 0 || brightness >= 255) 
  {fadeAmount = -fadeAmount;}
  
  delay(200);
  Serial.println(brightness);
}
