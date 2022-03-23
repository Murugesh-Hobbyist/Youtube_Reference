int motor_PWM = 11;
int Speed = 0;
int changeAmount = 2;

void setup()
{
  pinMode(motor_PWM, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  analogWrite(motor_PWM, Speed);
  Speed = Speed + changeAmount;
  
  if (Speed <= 0 || Speed >= 255) 
  {changeAmount = -changeAmount;}
  delay(200);
  Serial.println(Speed);
}
