#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_ADDR 0x3C   // Address may be different for your module, also try with 0x3D if this doesn't work
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//For more hardware details, visit https://iotforgeeks.com/interface-i2c-oled-display-ssd1306-with-nodemcu
//SCL - D1
//SDA - D2
void setup() 
{
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
  display.setTextSize(1);  
  display.setCursor(30, 0);
  display.println("Smart Weld");
  display.setTextSize(1);           // Set text size
  display.println("Delay --> 5S");
  display.setTextSize(2);
 // display.setCursor(0, 15);         // Set cursor
  display.print("Spark");
  display.display();                // Always required when changes are made and when you have to display them
  while(1) delay(50);               

}

void loop() {
}
