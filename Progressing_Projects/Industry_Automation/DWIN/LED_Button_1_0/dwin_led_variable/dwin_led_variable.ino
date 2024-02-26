//https://www.youtube.com/watch?v=UIH0ghxAj4Q
#include <SoftwareSerial.h>
unsigned char Buffer[9];
byte onled[]={0x5A,0xA5,0x05,0x82,0x55,0x00,0x00,0x01};
byte offled[]={0x5A,0xA5,0x05,0x82,0x55,0x00,0x00,0x00};
int led=13;
void setup() 
{
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);
  Serial.println("Touch 1 on DWIN to ON LED , 0 to OFF....");
}

void loop() 
{
       //       Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAA on");
 if(Serial.available())
  {
              Serial.println("KKKKKKKKKKKKKKKKKKK on");
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
       
          case 0x53:  //for led
            if(Buffer[8]==1)
            { digitalWrite(led,HIGH);
              Serial.println("led on");
              Serial.write(onled,8); }
            else
            {digitalWrite(led,LOW);
              Serial.println("led off");
              Serial.write(offled,8);
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