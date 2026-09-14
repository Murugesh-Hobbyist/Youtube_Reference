double channel;
void setup() 
{
  pinMode (D1,INPUT);
  Serial.begin(9600);
}

void loop() 
{
  channel = pulseIn(D1,HIGH);
//int sensorValue = analogRead(A0);
//int velocity=map(sensorValue,510,380,0,100);
  Serial.println(channel);
}
