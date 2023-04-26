int EMGPin = 13;
int EMGVal = 0;

void setup() {
Serial.begin(9600);
}

void loop() {
EMGVal = analogRead(EMGPin);
Serial.println(EMGVal);
delay(100);
}
