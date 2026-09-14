#define LED_PIN 22

int brightness = 0;   // 0–100
String input = "";

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Enter brightness (0 to 100):");
}

void loop() {

  // Read full line from serial
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      int value = input.toInt();

      if (value < 0) value = 0;
      if (value > 100) value = 100;

      brightness = value;

      Serial.print("Brightness set to: ");
      Serial.print(brightness);
      Serial.println("%");

      input = "";  // reset
    } else {
      input += c;
    }
  }

  // Software PWM
  int onTime = brightness;
  int offTime = 100 - brightness;

  digitalWrite(LED_PIN, HIGH);
  delayMicroseconds(onTime * 100);

  digitalWrite(LED_PIN, LOW);
  delayMicroseconds(offTime * 100);
}