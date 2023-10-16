#include <DigiMouse.h>
void setup() 
{   
  pinMode(1, OUTPUT);DigiMouse.begin(); 
}

void loop() 
{       
  digitalWrite(1, HIGH); 
  DigiMouse.setButtons(1<<0); //left click
  DigiMouse.delay(50);  
  DigiMouse.setButtons(0); //unclick all
  DigiMouse.delay(50);    
  delay (300);
  digitalWrite(1, LOW);    
  delay (4700);
}
