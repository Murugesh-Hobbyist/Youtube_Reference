#include <SoftwareSerial.h>
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;
const byte rxPin = 9;
const byte txPin = 8;
const byte analogPin = A0;
unsigned char Buffer[9];
const int averageValue = 50;
long int sensorValue = 0;


byte green[]={0x5A,0xA5,0x05,0x82,0x53,0x00,0x00,0x08};
byte red[]={0x5A,0xA5,0x05,0x82,0x53,0x00,0x00,0x09};
byte textoff[]={0x5A,0xA5,0x08,0x82,0x20,0x00,0x00,0x00,0x00,0x00,0x00};

SoftwareSerial dwinSerial(rxPin, txPin);

unsigned char incomingData[100];
unsigned char textString[100];         // Chars to send
unsigned char receivedFloatArray[50];  // Array created from the useful part of the received char
float receivedFloat;                   // float converted from the above array using atof ( )
int check = 1;
float setval=0;
int analogReading;
float floatVoltageValue;  // ADC analog value converted into voltage (stored as float)
long adcTimer;            //Read and update ADC value every x milliseconds only
bool isit = true;
float tolerance=0;
void setup() {
  //Serial.begin(9600);

  Serial.println("DWIN — display — printing numbers");
  // Set the baud rate for the SoftwareSeria1 object
  dwinSerial.begin(115200);  //software Serial does not like 115200,
  // setting up the TX and RX pins
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);


  Serial.begin(115200);
  ads.setGain(GAIN_ONE);
  //   ads.setGain();
  //  ads.setGain(GAIN_SIXTEEN);

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  // Setup 3V comparator on channel 0
  ads.startComparator_SingleEnded(0, 1000);


  delay(500);
}

//   17780 - 2230
// 3240- 26660  5.96 97 96 96 84 84

//17600-1210
//26350 - 1800


void loop() 
{
  // check();
  fetchText();
  readADC();
}
/*
void check()
  {
       //       Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAA on");
 if(dwinSerial.available())
  {
          //    Serial.println("KKKKKKKKKKKKKKKKKKK on");
    for(int i=0;i<=8;i++)   //TO store whole frame in buffer array. 0X5A A5 06 83 55 00 01 00 01 For ON
    {
    Buffer[i]= Serial.read();
    }
    
    if(Buffer[0]==0X5A)
      {
              Serial.println("OOOOOOOOOOOOOOOOOOOOOOOOon");
              Serial.println(Buffer[4]);
              Serial.println(Buffer[8]);
        switch(Buffer[4])
        {
              Serial.println(Buffer[4]);
       
          case 0x11:  //for led
            if(Buffer[8]==30)
            {
              Serial.println("led on");
            //  Serial.write(onled,8);
               }
            else
            {
              Serial.println("led off");
            //  Serial.write(offled,8);
              }
            break;
          default:
           Serial.println("No Data");
           break;
        }
    }
  }
delay(10);
}
*/
void readADC() 
{
if (check == 0 && isit == true) 
{
    if (millis() - adcTimer > 50) {
    analogReading = ads.getLastConversionResults();
    //  Serial.print(analogReading);    Serial.print("---");
      floatVoltageValue = map(analogReading, 2000, 26600, 0, 1000);
     floatVoltageValue = (floatVoltageValue / 100);
      setval = floatVoltageValue;
      adcTimer = millis();
      check=1;
    }
    }

    if (millis() - adcTimer > 50) {
    analogReading = ads.getLastConversionResults();
    floatVoltageValue = map(analogReading, 2000, 26600, 0, 1000);
    floatVoltageValue = (floatVoltageValue / 100)-setval;
   // Serial.println(floatVoltageValue, 2);
    Serial.println(tolerance);
if (tolerance>0)
{
  if (tolerance/2 > abs(floatVoltageValue) && tolerance/2 != abs(floatVoltageValue))
  {Serial.println("ookkk");
  dwinSerial.write(green,sizeof(green));
  }
if (tolerance/2 <= abs(floatVoltageValue))
{Serial.println("Nooooooooooooooooooo");
  dwinSerial.write(red,sizeof(red));
  }
}
sendFloatNumber2(tolerance); 
    sendFloatNumber1(floatVoltageValue);  // Send to display
    adcTimer = millis();
  }
}



void fetchText() {
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
  dwinSerial.write(textoff,sizeof(textoff));
  dwinSerial.write(textoff,sizeof(textoff));
      receivedFloat = atof(receivedFloatArray);
      if (receivedFloat == 0){check = receivedFloat;}
      if (receivedFloat > 0) {tolerance=receivedFloat;}
      Serial.print("Received float");
      Serial.println(receivedFloat, 2);
      memset(incomingData, 0, sizeof(incomingData));
      memset(receivedFloatArray, 0, sizeof(receivedFloatArray));
    }
  }
}

/*

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

*/

void sendFloatNumber1(float floatValue) {
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
void FloatToHex(float f, byte* hex) {
  byte* f_byte = reinterpret_cast<byte*>(&f);
  memcpy(hex, f_byte, 4);
}



void sendFloatNumber2(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x13);
  dwinSerial.write((byte)0x00);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}
