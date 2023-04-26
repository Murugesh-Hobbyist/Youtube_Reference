int Heart_rate_Pin = 27;
int Heart_rate_Val = 0;
int H_Count=0;
void setup() {
Serial.begin(9600);
}

void loop() {
Heart_rate_Val = analogRead(Heart_rate_Pin);
Heart_rate_Val = Heart_rate_Val-2500;
if ((300<Heart_rate_Val<325))
{  if (Heart_rate_Val>300)
  H_Count=H_Count+1;
}

//Serial.println(Heart_rate_Val);
Serial.println(H_Count);

delay(100);
}
