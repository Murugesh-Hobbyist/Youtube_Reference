int motor1pin1 = 5;
int motor1pin2 = 6;
int xx=10;
int yy=60;
void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:   
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  delay(xx);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  delay(yy);
}
