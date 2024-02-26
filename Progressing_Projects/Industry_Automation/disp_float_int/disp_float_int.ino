#include <SoftwareSerial.h>
const byte rxPin = 9;
const byte txPin = 8;
const byte analogPin = A0;

SoftwareSerial dwinSerial(rxPin, txPin);

unsigned char incomingData[100];
unsigned char textString[100];         // Chars to send
unsigned char receivedFloatArray[50];  // Array created from the useful part of the received char
float receivedFloat;                   // float converted from the above array using atof ( )

int analogReading;
float floatVoltageValue;  // ADC analog value converted into voltage (stored as float)
long adcTimer;            //Read and update ADC value every x milliseconds only

void setup() {
  Serial.begin(9600);
  Serial.println("DWIN — display — printing numbers");
  // Set the baud rate for the SoftwareSeria1 object
  dwinSerial.begin(115200);  //software Serial does not like 115200,
  // setting up the TX and RX pins
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  delay(500);
}



void loop() {
 fetchText();
  readADC();
}


void readADC() {
  if (millis() - adcTimer > 100) {
    analogReading = analogRead(analogPin);
    floatVoltageValue = analogReading / 1023.0 * 3.3;
    Serial.println(floatVoltageValue);

    sendIntNumber (analogReading); // send int to display
    sendFloatNumber (floatVoltageValue) ; // Send to display
    adcTimer = millis();
  }
}



void fetchText() 
{
  if (dwinSerial.available() > 0)  // available() returns the number of bytes stored in the buffer
  {
    int i = 0;
    while (dwinSerial.available() > 0)  // empty the buffer into our array
    {
      char incomingByte = dwinSerial.read();  // read 1 character from the dwin display
      delay(2);
      incomingData[i] = incomingByte;
      i++;
    }
    if (incomingData[3] == (byte)0x83)  // VP read instruction is in the returned char array
    {
      int k = 7;
      int j = 0;

      while (incomingData[k] != 0xFF) {
        receivedFloatArray[j] = incomingData[k];
        k++;
        j++;
      }

      receivedFloat = atof(receivedFloatArray);
      Serial.print("Received float");
      Serial.println(receivedFloat, 5);
      memset(incomingData, 0, sizeof(incomingData));
      memset(receivedFloatArray, 0, sizeof(receivedFloatArray));
    }
  }
}



void sendIntNumber(int numberToSend) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(2 + 1 + 2);
  dwinSerial.write(0x82);
  dwinSerial.write(0x10);
  dwinSerial.write((byte)0X00);  // Write address
  dwinSerial.write(highByte(numberToSend));
  dwinSerial.write(lowByte(numberToSend));
}


void sendFloatNumber(float floatValue)
{
dwinSerial.write(0x5A);
dwinSerial.write(0xA5);
dwinSerial.write(0x07);
dwinSerial.write(0x82);
dwinSerial.write(0x11);
dwinSerial.write((byte)0x00);  // Write address
byte hex[4] = { 0 };           // create a hex array for the 4 bytes
FloatToHex(floatValue, hex);   // convert the float to hex array
dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
dwinSerial.write(hex[2]);
dwinSerial.write(hex[1]);
dwinSerial.write(hex[0]);
}
void FloatToHex(float f, byte* hex) 
{
  byte* f_byte = reinterpret_cast<byte*>(&f);
  memcpy(hex, f_byte, 4);
}
