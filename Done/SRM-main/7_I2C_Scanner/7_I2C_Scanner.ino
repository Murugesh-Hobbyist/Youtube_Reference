#include <Wire.h>

#define TF_LUNA_ADDR 0x10
#define SDA_PIN 8
#define SCL_PIN 9

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

  Serial.println("TF-Luna I2C Read Test");
}

void loop() {
  uint8_t data[6];

  if (readBytes(0x00, data, 6)) {
    uint16_t dist = data[0] | (data[1] << 8);
    uint16_t amp  = data[2] | (data[3] << 8);
    uint16_t tempRaw = data[4] | (data[5] << 8);

    float tempC = (tempRaw / 100.0);

    Serial.print("Distance: ");
    Serial.print(dist);
    Serial.print(" cm | Amp: ");
    Serial.print(amp);
    Serial.print(" | Temp: ");
    Serial.print(tempC);
    Serial.println(" C");
  } else {
    Serial.println("Read failed");
  }

  delay(200);
}