/*  
  Simple example of using elapsedMillis library
  
  This example does nothing more than blinking a LED... but the difference 
  here to just using delay(1000) to control the delay between blinks is that 
  you can do more in the loop - like get user input, check buttons, get sensor
  input and other tasks that take time - while you wait for the next time the 
  LED is to change state. All you need to do is add it before or after the 
  'if' statement that controls the check of the time elapsed. 
  
  This example code is in the public domain.
*/

#include <elapsedMillis.h>

elapsedMillis timeElapsed; 
unsigned int interval = 1000;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (timeElapsed < interval)
  {

      Serial.println("hioo");
  }//Serial.println("hhhhhhhhhhhhhhhhhhhh");   
  // timeElapsed = 0; // reset the counter to 0 so the counting starts over...

}
