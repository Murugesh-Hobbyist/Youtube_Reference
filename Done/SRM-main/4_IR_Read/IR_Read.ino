#include <Arduino.h>

#define IR_1_PIN 22
#define IR_2_PIN 23

void setup() {
  Serial.begin(115200);

  pinMode(IR_1_PIN, INPUT);
  pinMode(IR_2_PIN, INPUT);

  Serial.println("IR Sensor Monitoring Started");
}

void loop() {
  int ir1 = digitalRead(IR_1_PIN);
  int ir2 = digitalRead(IR_2_PIN);

  Serial.print("IR_1 -> ");
  if (ir1 == HIGH) {
    Serial.print("Not Detected");
  } else {
    Serial.print("Detected");
  }

  Serial.print(" ; ");

  Serial.print("IR_2 -> ");
  if (ir2 == HIGH) {
    Serial.print("Not Detected");
  } else {
    Serial.print("Detected");
  }

  Serial.println();

  delay(20);  // stable output
}