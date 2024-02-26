#include <Arduino.h>
#include <MsTimer2.h>  //串口输出使用了定时器

//
unsigned char tcount = 0;
unsigned char Buffer[80];  //建立缓冲区
unsigned char Buffer_Len = 0;
bool pushButtonPWM;   // 创建布尔型变量用来存储PWM开关状态
bool pushButtonSW;   // 创建布尔型变量用来存储测距仪开关状态
int ledPinPWM = 13;        //PWMLED引脚号
int brightness = 128;  //PWMLED亮度参数

//
unsigned char b[7]={
	0X5A,0XA5,0X06,0X82,0X21,0X00,0X00 //串口输出前缀
};
long a;                  //测距输出结果变量

float checkdistance_5_4(){      //测距函数
 digitalWrite(5,LOW);
 delayMicroseconds(2);
 digitalWrite(5,HIGH);
 delayMicroseconds(10);
 digitalWrite(5,LOW);
 float distance = pulseIn(4,HIGH)/58.00;
 delay(10);
 return distance;
 }

void Timer2Interrupt()    //定时器函数
{
  if(tcount>0)
    tcount--;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);      //波特率设置为115200  
  pinMode(6,OUTPUT);              
  pinMode(7,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
 
  //
  pinMode(5,OUTPUT);
pinMode(4,INPUT);
//
  MsTimer2::set(5, Timer2Interrupt);//定时器设置，每一步进为5ms
  MsTimer2::start();
//COM SETUP

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
 // Serial.println("llllllllllllllllllllllllll: ");
    Buffer[Buffer_Len] = Serial.read();
    Buffer_Len++;
    tcount = 5;
  }
  else
  {
    if(tcount==0)
   { if(Buffer[0]==0X5A){             //通讯帧头判定
switch(Buffer[4]){

case 0x52 :                      //PWMLED亮度控制
   brightness=Buffer[8];delay(10);analogWrite(ledPinPWM, brightness);
  break;
case 0x53:                      //LED亮灭控制
   if(Buffer[8]==1){digitalWrite(13, HIGH);}else
{digitalWrite(13, LOW);}
  break;
case 0x54:
   if(Buffer[8]==1){digitalWrite(13, HIGH);}else
{digitalWrite(13, LOW);}
break;
  case 0x55:
   if(Buffer[8]==1){digitalWrite(13, HIGH);}else
{digitalWrite(13, LOW);}
break;
  case 0x56:
   if(Buffer[8]==1){digitalWrite(13, HIGH);}else
{digitalWrite(13, LOW);}
break; 
  case 0x51:                   //测距仪开关
  pushButtonSW = Buffer[8];
break;
case 0x57:                     //测距仪清零
  if(Buffer[8]==1){a = 0;
  long c = a>>8;
  long d = a>>16;
  Serial.write(b,7);
  Serial.write(d);
  Serial.write(c&0x0000FF);
  Serial.write(a&0x0000FF);}
  
break;
      
      //
      }
      
      Buffer_Len = 0;      //缓存清空
    }
if(pushButtonSW){a = long(checkdistance_5_4()*100);  //测距输出
  long c = a>>8;
  long d = a>>16;
  Serial.write(b,7);
  Serial.write(d);
  Serial.write(c&0x0000FF);
  Serial.write(a&0x0000FF);

  }                                        
                                
  }}
  //2021/12/7
  }
        
  
