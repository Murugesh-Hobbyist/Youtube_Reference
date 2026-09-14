#include <Arduino.h>

#define LDR_Pin 8

void setup() {
  Serial.begin(115200);
  Serial.println("LDR Analog Read Test");
}

void loop() {
  int ldrValue = analogRead(LDR_Pin);
  //Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  delay(300);
}