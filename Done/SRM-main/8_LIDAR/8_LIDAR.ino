#include <Wire.h>

#define TF_LUNA_ADDR 0x10
#define SDA_PIN 41
#define SCL_PIN 42

// Application -> https://www.youtube.com/shorts/hfnSJWHEOTU

//TF-Luna Pin 1 → 5V
//TF-Luna Pin 2 → ESP32 SDA
//TF-Luna Pin 3 → ESP32 SCL
//TF-Luna Pin 4 → GND
//TF-Luna Pin 5 → GND

//Amp = signal strength of the reflected laser return.
//From the TF-Luna manual:
//distance is unreliable when Amp < 100
//distance is also unreliable when Amp = 65535
//if Amp > 32768, it can indicate ambient light overexposure, like strong sunlight

bool readBytes(uint8_t reg, uint8_t *buf, uint8_t len) {
  Wire.beginTransmission(TF_LUNA_ADDR);
  Wire.write(reg);

  if (Wire.endTransmission(false) != 0) {
    return false;
  }

  uint8_t count = Wire.requestFrom(TF_LUNA_ADDR, len);
  if (count != len) {
    return false;
  }

  for (uint8_t i = 0; i < len; i++) {
    buf[i] = Wire.read();
  }

  return true;
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);

  Serial.println("TF-Luna I2C Distance Test Started");
  Serial.print("Using SDA: ");
  Serial.print(SDA_PIN);
  Serial.print(" | SCL: ");
  Serial.println(SCL_PIN);
  Serial.print("Using I2C address: 0x");
  Serial.println(TF_LUNA_ADDR, HEX);
}

void loop() {
  uint8_t data[6];

  if (readBytes(0x00, data, 6)) {
    uint16_t distance = data[0] | (data[1] << 8);
    uint16_t amp = data[2] | (data[3] << 8);
    uint16_t tempRaw = data[4] | (data[5] << 8);

    float tempC = (tempRaw / 100.0);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm");

    Serial.print(" | Amp: ");
    Serial.print(amp);

    Serial.print(" | Temp: ");
    Serial.print(tempC);
    Serial.println(" C");
  } else {
    Serial.println("TF-Luna read failed");
  }

  delay(2);
}