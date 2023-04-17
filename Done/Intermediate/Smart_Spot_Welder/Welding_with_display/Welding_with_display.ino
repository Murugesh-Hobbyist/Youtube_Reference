#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_ADDR 0x3C   // Address may be different for your module, also try with 0x3D if this doesn't work
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//SCL - D1
//SDA - D2

int Pot = A0;
int Relay = D6;
int Pot_Val = 0;
int Relay_Delay = 0;
int Off_Delay = 5000* Relay_Delay;


void setup() 
{
  pinMode(Pot, INPUT);
  pinMode(Relay, OUTPUT);
  Serial.begin(9600);
//-----------------------------------------------------------------
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);delay(50);
 
  display.setTextSize(1);  
  display.setCursor(30, 0);
  display.println("Smart Weld");
  
  display.setTextSize(1);
  display.println("Delay --> 5S");
  display.setTextSize(2);
  display.print("Spark");
  display.display();
              
}

void loop() 
{
  Pot_Val = analogRead(Pot);
  Relay_Delay = map(Pot_Val,0,1024,500,0);
//  Serial.print("Pot_Val  -----> ");  Serial.println(Pot_Val);
  Serial.print("Relay_Delay --> ");  Serial.println(Relay_Delay);
  Serial.println("-----------------------------------------------------------------"); 
    
  display.clearDisplay();
  display.setTextSize(1);  
  display.setCursor(30, 0);
  display.println("Smart Weld");
  
  display.setTextSize(1);
  display.println("Delay --> 3S");
  display.setTextSize(2);
  display.print("Spark"); 
 
  display.setCursor(80,15); 
  display.print(Relay_Delay);
  display.display();   

  
  digitalWrite(Relay, LOW); 
  delay(3000);                     
  digitalWrite(Relay, HIGH); 
  delay(Relay_Delay);   


}
