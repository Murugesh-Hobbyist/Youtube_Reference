#include <IRremote.h>

int Sensor_Pin = A0;
IRrecv Sensor_Pin_Value(Sensor_Pin);
decode_results results;

void setup()
{
  Serial.begin(9600);
  Sensor_Pin_Value.enableIRIn();
  pinMode(8, OUTPUT);
}

void loop() 
{ 
  if (Sensor_Pin_Value.decode(&results))
     {
     Serial.println(results.value, HEX);
     
     if (results.value == 0x4F58748B) 
        {digitalWrite(8, HIGH);}
     if (results.value == 0x4F587887) 
        {digitalWrite(8, LOW);}
       
     Sensor_Pin_Value.resume();} //Restart the ISR state machine and Receive the next value 
}


Why is 0x used for hex?
The prefix 0x is used in code to indicate that the number is being written in hex. But what is 'B' doing in there? 
The hexadecimal format has a base of 16, which means that each digit can represent up to 16 different values. Unfortunately, 
we run out of numerical digits after '9,' so we start using letters.
