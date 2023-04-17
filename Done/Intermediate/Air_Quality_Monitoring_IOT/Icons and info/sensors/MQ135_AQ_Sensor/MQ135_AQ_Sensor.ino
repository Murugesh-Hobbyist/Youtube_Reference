#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeMonoOblique9pt7b.h>
#define AQ_Sensor    A0 
int GasLevel = 0;         //int variable for gas level
String quality =""; 

void air_sensor()
{
  GasLevel = analogRead(AQ_Sensor);

  if(GasLevel<=820){
    quality = "  GOOD!";
  }
  else if (GasLevel >820 && GasLevel<=880){
    quality = "  Poor!";
  }
  else if (GasLevel >880 && GasLevel<920){
    quality = "Very bad!";
  }
    else{
    quality = " Toxic";   
}
   // Serial.print("sensor = ");
  Serial.println(GasLevel);
}

void setup() {
  Serial.begin(9600);
  pinMode(AQ_Sensor,INPUT);
}

void loop() {
air_sensor();
}
