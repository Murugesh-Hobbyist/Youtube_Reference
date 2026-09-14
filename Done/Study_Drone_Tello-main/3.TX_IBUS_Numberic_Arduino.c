#include <string.h>
#define IBUS_BUFFSIZE 32    // Max iBus packet size (2 byte header, 14 channels x 2 bytes, 2 byte checksum)
#define IBUS_MAXCHANNELS 10 // My TX only has 10 channels, no point in polling the rest
int Channel_1;
int Channel_2;
int Channel_3;
int Channel_4;
int Pot_5;
int Pot_6;
int Switch_A;
int Switch_B;
int Switch_C;
int Switch_D;
static uint8_t ibusIndex = 0;
static uint8_t ibus[IBUS_BUFFSIZE] = {0};
static uint16_t rcValue[IBUS_MAXCHANNELS];
static boolean rxFrameDone;

void setup() 
{
  Serial.begin(115200); 
  Serial.println("setup done!");
}

void loop() 
{
  readRx();
}

void readRx()
{
  rxFrameDone = false;
  
  if (Serial.available())
  {
    uint8_t val = Serial.read();
    // Look for 0x2040 as start of packet
    if (ibusIndex == 0 && val != 0x20)
    {
      ibusIndex = 0;
      return;
    }
    if (ibusIndex == 1 && val != 0x40) 
    {
      ibusIndex = 0;
      return;
    }

    if (ibusIndex == IBUS_BUFFSIZE)
    {
      ibusIndex = 0;
      int high=3;
      int low=2;
      for(int i=0;i<IBUS_MAXCHANNELS; i++)
      {
        //left shift away the first 8 bits of the first byte and add the whole value of the previous one
        rcValue[i] = (ibus[high] << 8) + ibus[low];
//    Serial.print(rcValue[i]);    //values between 1000 and 2000
//    Serial.print("     ");
        high += 2;
        low += 2;
      }
      
  Channel_1 = map(rcValue[0], 1000, 2000, -100, 100); 
  Channel_2 = map(rcValue[1], 1000, 2000, -100, 100);
  Channel_3 = map(rcValue[2], 1000, 2000, -100, 100);
  Channel_4 = map(rcValue[3], 1000, 2000, -100, 100);
  Pot_5 = map(rcValue[4], 1000, 2000, 0, 100);
  Pot_6 = map(rcValue[5], 1000, 2000, 0, 100);
  Switch_A = map(rcValue[6], 1000, 2000, 0, 1); 
  Switch_B = map(rcValue[7], 1000, 2000, 0, 1); 
  Switch_C = map(rcValue[8], 1000, 2000, 0, 1); 
  Switch_D = map(rcValue[9], 1000, 2000, 0, 1); 
  
//      Serial.print(Channel_3);
//    Serial.println();
      rxFrameDone = true;
      return;
    }
    else
    {
      ibus[ibusIndex] = val;
      ibusIndex++;
    }
  }
}