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
