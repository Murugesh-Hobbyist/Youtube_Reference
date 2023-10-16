#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 //--> OLED display width, in pixels
#define SCREEN_HEIGHT 32 //--> OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long previousMillisGetHR = 0; //--> will store the last time Millis (to get Heartbeat) was updated.
unsigned long previousMillisResultHR = 0; //--> will store the last time Millis (to get BPM) was updated.
const long intervalGetHR = 20; //--> Interval for reading heart rate (Heartbeat) = 10ms.
const long intervalResultHR = 10000; //--> The reading interval for the result of the Heart Rate calculation is in 10 seconds.
int PulseSensorSignal; //--> Variable to accommodate the signal value from the sensor
const int PulseSensorHRWire = 13; //--> PulseSensor connected to ANALOG PIN 0 (A0 / ADC 0).
int UpperThreshold = 550; //--> Determine which Signal to "count as a beat", and which to ingore.
int LowerThreshold = 500; 
int cntHB = 0; //--> Variable for counting the number of heartbeats.
boolean ThresholdStat = true; //--> Variable for triggers in calculating heartbeats.
int BPMval = 0; //--> Variable to hold the result of heartbeats calculation.
int x=0; //--> Variable axis x graph values to display on OLED
int y=0; //--> Variable axis y graph values to display on OLED
int lastx=0; //--> The graph's last x axis variable value to display on the OLED
int lasty=0; //--> The graph's last y axis variable value to display on the OLED
const unsigned char Heart_Icon [] PROGMEM = 
{
  0x00, 0x00, 0x18, 0x30, 0x3c, 0x78, 0x7e, 0xfc, 0xff, 0xfe, 0xff, 0xfe, 0xee, 0xee, 0xd5, 0x56, 
  0x7b, 0xbc, 0x3f, 0xf8, 0x1f, 0xf0, 0x0f, 0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01, 0x00, 0x00, 0x00
};

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int PulseSensorPurplePin = 36;
int Signal;
int Change;

#include "Arduino.h"
#include "uRTCLib.h"
uRTCLib rtc(0x68);

#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#define DHT_SENSOR_PIN  19 
#define DHT_SENSOR_TYPE DHT11
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);


void setup() 
{  pinMode(23, OUTPUT);
  dht_sensor.begin(); // initialize the DHT sensor

  Serial.begin(9600); //--> Set's up Serial Communication at certain speed.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); //--> Don't proceed, loop forever
  }
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 12); //--> (x position, y position)
  display.print("     Please wait");
  display.setCursor(0, 22); //--> (x position, y position)
  display.print("     10  seconds");
  display.setCursor(0, 32); //--> (x position, y position)
  display.print("       to get");
  display.setCursor(0, 42); //--> (x position, y position)
  display.print(" the Heart Rate value");
  display.display(); 
  delay(3000);
  display.clearDisplay(); //--> for Clearing the display
  display.drawBitmap(0, 47, Heart_Icon, 16, 16, WHITE); //--> display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawLine(0, 43, 127, 43, WHITE); //--> drawLine(x1, y1, x2, y2, color)
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 48); //--> (x position, y position)
  display.print(": 0 BPM");
  display.display();
  Serial.println();
  Serial.println("Please wait 10 seconds to get the BPM Value");


  {
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("HR");
  lcd.setCursor(6, 0);      
  lcd.print("bpm");
  lcd.setCursor(11, 0);    
  lcd.print("BP");
 // lcd.setCursor(14, 0);
 // lcd.print("M");
  lcd.setCursor(0, 1);
  lcd.print("Temperature");
  }
{
  #ifdef ARDUINO_ARCH_ESP8266
    URTCLIB_WIRE.begin(0, 2); // D3 and D4 on ESP8266
  #else    URTCLIB_WIRE.begin();
  #endif
//  rtc.set(0, 42, 16, 6, 2, 5, 15);
//  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
}

}

void loop() 
{
  GetHeartRate(); //--> Calling the GetHeartRate() subroutine
    
{
 Signal = analogRead(PulseSensorPurplePin);
 if (Signal < 500)
  {
    Change = 75;
    Serial.println(Change);
    delay(1000);
  }

 if (Signal > 2500)
  {
    Change = 0;
    Serial.println(Change);
  }
}
{
  float tempC = dht_sensor.readTemperature();
  lcd.setCursor(3, 0);
     if (Change == 0)
      {digitalWrite(23, LOW);
        lcd.print("00");
        lcd.setCursor(14, 0);  
        lcd.print("L");  
        }; 
           if (Change == 75)
          {  digitalWrite(23, HIGH);
             lcd.print(Change);
              lcd.setCursor(14, 0);  
              lcd.print("H");  };
    lcd.setCursor(12, 1);         
    lcd.print(tempC);  
    lcd.setCursor(14, 1);   
  lcd.print( (char)223); // displaying degree symbol (°).
    lcd.setCursor(15, 1);   
  lcd.print("C"); // displaying degree symbol (°).
  }
  
{
  rtc.refresh();
  Serial.print("RTC DateTime: ");
  Serial.print(rtc.year());
  Serial.print('/');
  Serial.print(rtc.month());
  Serial.print('/');
  Serial.print(rtc.day());
  Serial.print(' ');

  Serial.print(rtc.hour());
  Serial.print(':');
  Serial.print(rtc.minute());
  Serial.print(':');
  Serial.print(rtc.second());
  
  Serial.print(" DOW: ");
  Serial.print(rtc.dayOfWeek());
  Serial.println();
}


}

void GetHeartRate() 
{
  
  unsigned long currentMillisGetHR = millis();
  if (currentMillisGetHR - previousMillisGetHR >= intervalGetHR) {
    previousMillisGetHR = currentMillisGetHR;
    PulseSensorSignal = analogRead(PulseSensorHRWire); //--> holds the incoming raw data. Signal value can range from 0-1024
    if (PulseSensorSignal > UpperThreshold && ThresholdStat == true) {
      cntHB++;
      ThresholdStat = false;
    }
    if (PulseSensorSignal < LowerThreshold) {
      ThresholdStat = true;
    }
    DrawGraph(); //--> Calling the DrawGraph() subroutine
  }
  unsigned long currentMillisResultHR = millis();
  if (currentMillisResultHR - previousMillisResultHR >= intervalResultHR) {
    previousMillisResultHR = currentMillisResultHR;
    BPMval = cntHB * 6; //--> The taken heart rate is for 10 seconds. So to get the BPM value, the total heart rate in 10 seconds x 6.
    //Serial.print("BPM : ");
    //Serial.println(BPMval);
    display.fillRect(20, 48, 108, 18, BLACK);
    display.drawBitmap(0, 47, Heart_Icon, 16, 16, WHITE); //--> display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)   
    display.drawLine(0, 43, 127, 43, WHITE); //--> drawLine(x1, y1, x2, y2, color)
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20, 48); //--> (x position, y position)
    display.print(": ");
    display.print(BPMval);
    display.print(" BPM");
    display.display(); 
    cntHB = 0;
  }
}

void DrawGraph() 
{
  if (x > 127) 
  {
    display.fillRect(0, 0, 128, 42, BLACK);
    x = 0;
    lastx = 0;
  }
  int ySignal = PulseSensorSignal; 
  if (ySignal > 850) ySignal = 850;
  if (ySignal < 350) ySignal = 350;
//  int ySignalMap = map(ySignal, 350, 850, 0, 40); //--> The y-axis used on OLEDs is from 0 to 40
    int ySignalMap = map(ySignal, 0, 1023, 0, 40); //--> The y-axis used on OLEDs is from 0 to 40

  y = 40 - ySignalMap;
  display.writeLine(lastx,lasty,x,y,WHITE);
  display.display(); 
  lastx = x;
  lasty = y;
  x++;
}
