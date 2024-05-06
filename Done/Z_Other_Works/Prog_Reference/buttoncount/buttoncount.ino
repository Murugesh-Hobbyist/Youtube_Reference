#define sensor 53
byte Touch_State = 0;
byte Previous_Touch_State = 0;
byte counter = 0;

void setup() {
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  Serial.println("RCWL-0516 Sensor Test");
}

void loop() {
  Touch_State = digitalRead(sensor);
  if (Touch_State == HIGH && Previous_Touch_State == LOW)
  {
    Serial.println("Motion detected !!");
    counter++;
    Serial.println(counter);
  }
  Previous_Touch_State = Touch_State;
}