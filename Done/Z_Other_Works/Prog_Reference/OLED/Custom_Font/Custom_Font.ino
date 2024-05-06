/*****************************************************************************
Author: Ashish Adhikari
Version: 1.0
Blog:   http://diyfactory007.blogspot.com.au
******************************************************************************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "COOPBL5pt7b.h"

define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
const int x = 0;
void setup()   { 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   // initialize with the I2C addr 0x3C (for the 128x64)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setFont(&COOPBL5pt7b);
}



void loop() { 
  display.setCursor(x,6);
  display.print("Charge  -> "); 
  display.display();  
  delay(1000);
  
  display.setCursor(x,14);  
  display.print("Level        -> "); 
  display.display();  
  delay(1000);
   
  display.setCursor(x,22);  
  display.print("Voltage -> "); 
  display.display();         
  delay(1000);
 
  display.setCursor(x,30);  
  display.print("Temp      -> "); 
  display.display();  
  delay(1000);
  
}
