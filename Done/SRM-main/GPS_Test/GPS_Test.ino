#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <math.h>

// ===================== GPS UART =====================
#define GPS_RX_PIN 18
#define GPS_TX_PIN 17
#define GPS_BAUD   115200

HardwareSerial gpsSerial(1);

// ===================== COMPASS I2C =====================
#define COMPASS_SDA_PIN 37
#define COMPASS_SCL_PIN 38
#define QMC5883_ADDR    0x0D

// QMC5883L Registers
#define QMC_X_LSB       0x00
#define QMC_STATUS      0x06
#define QMC_TEMP_LSB    0x07
#define QMC_CONTROL_1   0x09
#define QMC_CONTROL_2   0x0A
#define QMC_SET_RESET   0x0B

// Set your local magnetic declination in degrees
// Chennai area is roughly around +0.7 to +1.0 degrees
// Adjust later if needed
#define MAG_DECLINATION_DEG 0.8

// ===================== GPS UBX PARSER =====================
enum ParserState {
  WAIT_SYNC1,
  WAIT_SYNC2,
  WAIT_CLASS,
  WAIT_ID,
  WAIT_LEN1,
  WAIT_LEN2,
  WAIT_PAYLOAD,
  WAIT_CK_A,
  WAIT_CK_B
};

ParserState state = WAIT_SYNC1;

uint8_t msgClass = 0;
uint8_t msgID = 0;
uint16_t payloadLen = 0;
uint16_t payloadIndex = 0;
uint8_t ckA = 0;
uint8_t ckB = 0;
uint8_t rxCkA = 0;
uint8_t rxCkB = 0;
uint8_t payload[128];

// ===================== GLOBAL DATA =====================
struct GPSData {
  bool valid = false;
  uint8_t fixType = 0;
  uint8_t numSV = 0;

  double latitude = 0.0;
  double longitude = 0.0;
  double altitudeM = 0.0;
  double speedKmph = 0.0;
  double headingDeg = 0.0;

  uint16_t year = 0;
  uint8_t month = 0;
  uint8_t day = 0;
  uint8_t hour = 0;
  uint8_t minute = 0;
  uint8_t second = 0;
} gpsData;

struct CompassData {
  bool valid = false;
  int16_t x = 0;
  int16_t y = 0;
  int16_t z = 0;
  int16_t tempRaw = 0;
  uint8_t status = 0;
  double headingDeg = 0.0;
} compassData;

unsigned long lastPrintTime = 0;

// ===================== UTILS =====================
uint16_t u2(const uint8_t *p) {
  return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}

uint32_t u4(const uint8_t *p) {
  return (uint32_t)p[0] |
         ((uint32_t)p[1] << 8) |
         ((uint32_t)p[2] << 16) |
         ((uint32_t)p[3] << 24);
}

int32_t i4(const uint8_t *p) {
  return (int32_t)u4(p);
}

int16_t makeInt16(uint8_t lsb, uint8_t msb) {
  return (int16_t)((msb << 8) | lsb);
}

const char* fixTypeText(uint8_t fixType) {
  switch (fixType) {
    case 0: return "No Fix";
    case 1: return "Dead Reckoning";
    case 2: return "2D Fix";
    case 3: return "3D Fix";
    case 4: return "GNSS+DR";
    case 5: return "Time Only";
    default: return "Unknown";
  }
}

// ===================== COMPASS FUNCTIONS =====================
bool compassWriteRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(QMC5883_ADDR);
  Wire.write(reg);
  Wire.write(value);
  return (Wire.endTransmission() == 0);
}

bool compassReadRegisters(uint8_t startReg, uint8_t *buffer, uint8_t len) {
  Wire.beginTransmission(QMC5883_ADDR);
  Wire.write(startReg);
  if (Wire.endTransmission(false) != 0) {
    return false;
  }

  uint8_t count = Wire.requestFrom(QMC5883_ADDR, len);
  if (count != len) {
    return false;
  }

  for (uint8_t i = 0; i < len; i++) {
    buffer[i] = Wire.read();
  }

  return true;
}

bool initCompass() {
  Wire.begin(COMPASS_SDA_PIN, COMPASS_SCL_PIN);
  Wire.setClock(100000);
  delay(50);

  Wire.beginTransmission(QMC5883_ADDR);
  if (Wire.endTransmission() != 0) {
    return false;
  }

  // Soft reset
  if (!compassWriteRegister(QMC_CONTROL_2, 0x80)) return false;
  delay(10);

  // Set/reset period
  if (!compassWriteRegister(QMC_SET_RESET, 0x01)) return false;
  delay(10);

  // Control 1:
  // OSR = 512
  // RNG = 8G
  // ODR = 10Hz
  // MODE = Continuous
  if (!compassWriteRegister(QMC_CONTROL_1, 0b00010001)) return false;
  delay(10);

  return true;
}

bool readCompass() {
  uint8_t raw[9];

  if (!compassReadRegisters(QMC_X_LSB, raw, 9)) {
    compassData.valid = false;
    return false;
  }

  compassData.x = makeInt16(raw[0], raw[1]);
  compassData.y = makeInt16(raw[2], raw[3]);
  compassData.z = makeInt16(raw[4], raw[5]);
  compassData.status = raw[6];
  compassData.tempRaw = makeInt16(raw[7], raw[8]);

  double heading = atan2((double)compassData.y, (double)compassData.x) * 180.0 / PI;
  heading += MAG_DECLINATION_DEG;

  if (heading < 0) heading += 360.0;
  if (heading >= 360.0) heading -= 360.0;

  compassData.headingDeg = heading;
  compassData.valid = true;
  return true;
}

// ===================== GPS PARSER FUNCTIONS =====================
void resetParser() {
  state = WAIT_SYNC1;
  msgClass = 0;
  msgID = 0;
  payloadLen = 0;
  payloadIndex = 0;
  ckA = 0;
  ckB = 0;
  rxCkA = 0;
  rxCkB = 0;
}

void addChecksum(uint8_t b) {
  ckA = ckA + b;
  ckB = ckB + ckA;
}

void parseNavPvt(const uint8_t *p, uint16_t len) {
  if (len < 92) return;

  gpsData.year   = u2(&p[4]);
  gpsData.month  = p[6];
  gpsData.day    = p[7];
  gpsData.hour   = p[8];
  gpsData.minute = p[9];
  gpsData.second = p[10];

  gpsData.fixType = p[20];
  gpsData.numSV   = p[23];

  int32_t lon     = i4(&p[24]);
  int32_t lat     = i4(&p[28]);
  int32_t hMSL    = i4(&p[36]);
  int32_t gSpeed  = i4(&p[60]);
  int32_t headMot = i4(&p[64]);

  gpsData.longitude  = lon / 10000000.0;
  gpsData.latitude   = lat / 10000000.0;
  gpsData.altitudeM  = hMSL / 1000.0;
  gpsData.speedKmph  = (gSpeed / 1000.0) * 3.6;
  gpsData.headingDeg = headMot / 100000.0;
  gpsData.valid = true;
}

void processGPSByte(uint8_t b) {
  switch (state) {
    case WAIT_SYNC1:
      if (b == 0xB5) state = WAIT_SYNC2;
      break;

    case WAIT_SYNC2:
      if (b == 0x62) {
        state = WAIT_CLASS;
        ckA = 0;
        ckB = 0;
      } else {
        state = WAIT_SYNC1;
      }
      break;

    case WAIT_CLASS:
      msgClass = b;
      addChecksum(b);
      state = WAIT_ID;
      break;

    case WAIT_ID:
      msgID = b;
      addChecksum(b);
      state = WAIT_LEN1;
      break;

    case WAIT_LEN1:
      payloadLen = b;
      addChecksum(b);
      state = WAIT_LEN2;
      break;

    case WAIT_LEN2:
      payloadLen |= ((uint16_t)b << 8);
      addChecksum(b);

      if (payloadLen > sizeof(payload)) {
        resetParser();
      } else if (payloadLen == 0) {
        state = WAIT_CK_A;
      } else {
        payloadIndex = 0;
        state = WAIT_PAYLOAD;
      }
      break;

    case WAIT_PAYLOAD:
      payload[payloadIndex++] = b;
      addChecksum(b);
      if (payloadIndex >= payloadLen) {
        state = WAIT_CK_A;
      }
      break;

    case WAIT_CK_A:
      rxCkA = b;
      state = WAIT_CK_B;
      break;

    case WAIT_CK_B:
      rxCkB = b;

      if (rxCkA == ckA && rxCkB == ckB) {
        if (msgClass == 0x01 && msgID == 0x07) {
          parseNavPvt(payload, payloadLen);
        }
      }

      resetParser();
      break;
  }
}

// ===================== PRINT =====================
void printAllData() {
  Serial.println();
  Serial.println("=============== GPS + COMPASS DATA ===============");

  if (gpsData.valid) {
    Serial.print("Fix Type        : ");
    Serial.print(fixTypeText(gpsData.fixType));
    Serial.print(" (");
    Serial.print(gpsData.fixType);
    Serial.println(")");

    Serial.print("Satellites      : ");
    Serial.println(gpsData.numSV);

    Serial.print("Latitude        : ");
    Serial.println(gpsData.latitude, 7);

    Serial.print("Longitude       : ");
    Serial.println(gpsData.longitude, 7);

    Serial.print("Altitude        : ");
    Serial.print(gpsData.altitudeM, 2);
    Serial.println(" m");

    Serial.print("Speed           : ");
    Serial.print(gpsData.speedKmph, 2);
    Serial.println(" km/h");

    if (gpsData.speedKmph > 1.0) {
      Serial.print("GPS Heading     : ");
      Serial.print(gpsData.headingDeg, 2);
      Serial.println(" deg");
    } else {
      Serial.println("GPS Heading     : Stationary / Not reliable");
    }

    Serial.print("Date            : ");
    if (gpsData.day < 10) Serial.print("0");
    Serial.print(gpsData.day);
    Serial.print("/");
    if (gpsData.month < 10) Serial.print("0");
    Serial.print(gpsData.month);
    Serial.print("/");
    Serial.println(gpsData.year);

    Serial.print("Time            : ");
    if (gpsData.hour < 10) Serial.print("0");
    Serial.print(gpsData.hour);
    Serial.print(":");
    if (gpsData.minute < 10) Serial.print("0");
    Serial.print(gpsData.minute);
    Serial.print(":");
    if (gpsData.second < 10) Serial.print("0");
    Serial.print(gpsData.second);
    Serial.println(" UTC");

    Serial.print("Google Map      : https://maps.google.com/?q=");
    Serial.print(gpsData.latitude, 7);
    Serial.print(",");
    Serial.println(gpsData.longitude, 7);
  } else {
    Serial.println("GPS             : Waiting for valid UBX NAV-PVT data...");
  }

  Serial.println();

  if (compassData.valid) {
    Serial.print("Compass X       : ");
    Serial.println(compassData.x);

    Serial.print("Compass Y       : ");
    Serial.println(compassData.y);

    Serial.print("Compass Z       : ");
    Serial.println(compassData.z);

    Serial.print("Compass Status  : 0x");
    if (compassData.status < 16) Serial.print("0");
    Serial.println(compassData.status, HEX);

    Serial.print("Compass Heading : ");
    Serial.print(compassData.headingDeg, 2);
    Serial.println(" deg");
  } else {
    Serial.println("Compass         : Read failed");
  }

  Serial.println("==================================================");
}

// ===================== SETUP / LOOP =====================
void setup() {
  Serial.begin(115200);
  delay(1500);

  Serial.println();
  Serial.println("HGLRC M100 PRO GPS + COMPASS");
  Serial.print("GPS UART RX pin : ");
  Serial.println(GPS_RX_PIN);
  Serial.print("GPS UART TX pin : ");
  Serial.println(GPS_TX_PIN);
  Serial.print("GPS Baud        : ");
  Serial.println(GPS_BAUD);
  Serial.print("Compass SDA pin : ");
  Serial.println(COMPASS_SDA_PIN);
  Serial.print("Compass SCL pin : ");
  Serial.println(COMPASS_SCL_PIN);

  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  if (initCompass()) {
    Serial.println("Compass init    : OK");
  } else {
    Serial.println("Compass init    : FAILED");
  }

  Serial.println("System started.");
}

void loop() {
  while (gpsSerial.available()) {
    uint8_t b = gpsSerial.read();
    processGPSByte(b);
  }

  readCompass();

  if (millis() - lastPrintTime >= 1000) {
    lastPrintTime = millis();
    printAllData();
  }
}