
#include <IBusBM.h>
IBusBM ibus;

int rcCH1 = 0; // Left - Right
int rcCH2 = 0; // Forward - Reverse
int rcCH3 = 0; // Acceleration
int rcCH4 = 0; 
int rcCH5 = 0; 
int rcCH6 = 0; 

#define pwmA 2
#define in1A 4
#define in2A 5
#define pwmB 3
#define in1B 6
#define in2B 7

int MotorSpeedA = 0;
int MotorSpeedB = 0;
int MotorDirA = 1;
int MotorDirB = 1;



int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup() 
{
  Serial.begin(115200);
  ibus.begin(Serial1);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);
}

void loop() 
{

  rcCH1 = readChannel(0, -100, 100, 0);
  rcCH2 = readChannel(1, -100, 100, 0);
  rcCH3 = readChannel(2, -100, 100, 0);
  rcCH4 = readChannel(3, -100, 100, 0);
  rcCH5 = readChannel(4, -100, 100, 0);
  rcCH6 = readChannel(5, -100, 100, 0);


  // Print values to serial monitor for debugging
  Serial.print("Ch1 = ");
  Serial.print(rcCH1);
  Serial.print(" Ch2 = ");
  Serial.print(rcCH2);
  Serial.print(" Ch3 = ");
  Serial.print(rcCH3);
  Serial.print(" Ch4 = ");
  Serial.print(rcCH4);
  Serial.print(" Ch5 = ");
  Serial.print(rcCH5);
  Serial.print(" Ch6 = ");
  Serial.println(rcCH6);

  // Set speeds with channel 3 value
  MotorSpeedA = rcCH3;
  MotorSpeedB = rcCH3;


  int motorSpeedA = map(rcCH3, 0, 100, 0, 255);

if (rcCH3>20)
{
 // analogWrite(pwmA, motorSpeedA); // Send PWM signal to motor A
    digitalWrite(in1A, HIGH);
    digitalWrite(in2A, LOW);
}
if (rcCH3<-20)
{
 // analogWrite(pwmA, motorSpeedA); // Send PWM signal to motor A
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, HIGH);
}

  //analogWrite(pwmb, motorSpeedB); // Send PWM signal to motor B






























}