#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
//#include <SPFD5408_TouchScreen.h>
#include <TouchScreen.h>
#include <TFTSevenSegmentClockDisplay.h>


#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSerifBold18pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>

#include <Fonts/FreeSerif9pt7b.h>
long a = 0;

boolean toggleSeparator = false;

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TFTSevenSegmentClockDisplay clockDisplayD(&tft, 120, 30, 8, 12, YELLOW, tft.color565(20, 20, 20), 1, true, 1);
TFTSevenSegmentClockDisplay clockDisplayA(&tft, 80, 30, 40, 80, YELLOW, tft.color565(20, 20, 20), 10, false, 1.7);

const int Start_Peg = 10;  
const int Stop_Peg = 11;
const int Power = 12;

bool Timer = false;
bool Reset = false;
int time=0;

void setup(void) 
{
  
  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextSize(6);

 Serial.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(Start_Peg, INPUT_PULLUP);
  pinMode(Stop_Peg, INPUT_PULLUP);
  pinMode(Power, OUTPUT);

    digitalWrite(Start_Peg,HIGH);
    digitalWrite(Stop_Peg,HIGH);
    digitalWrite(Power,LOW);

      tft.reset();
      tft.begin(0x9341);
      tft.fillScreen(BLACK);      
  tft.fillRect(50,120, 60, 240, RED);
 // tft.fillRect(250, 200, 30, 60, GREEN);
      tft.setRotation(1); 
   //tft.setCursor(140,265);
      tft.setCursor(170,255);

  tft.setTextColor(WHITE);  tft.setTextSize(2.9);
  tft.println("Reset");
    clockDisplayA.displaySeconds(time, toggleSeparator);

}
#define MINPRESSURE 10
#define MAXPRESSURE 1000
void(* resetFunc) (void) = 0;

void loop(void) 
{   
  int sensorValue1 = digitalRead(Start_Peg);  int sensorValue2 = digitalRead(Stop_Peg);
  // Serial.print("sensorValue1-->");Serial.print(sensorValue1);Serial.print("    ");Serial.print("sensorValue2-->");Serial.println(sensorValue2);
  // time = time+1;   

  while ((digitalRead(Start_Peg) == HIGH) && (digitalRead(Stop_Peg) == HIGH) && (Timer == false)) //Not homed
  {
   tft.setCursor(120,155);
  tft.setTextColor(WHITE);  tft.setTextSize(2.9);
  tft.println("Please Keep the pegs in home position");
  }

  while ((digitalRead(Start_Peg) == LOW) && (digitalRead(Stop_Peg) == HIGH) && (Timer == false)) //homed
  {
  tft.setCursor(50,155);
  tft.setTextColor(WHITE);  tft.setTextSize(2.9);
  tft.println("Homing ready Please Proceed");

    while ((digitalRead(Start_Peg) == HIGH) && (digitalRead(Stop_Peg) == HIGH) && (Timer == false)) // moved
  {
    time = time+1;
    clockDisplayA.displaySeconds( time, toggleSeparator);
  }
  }

  while ((digitalRead(Start_Peg) == LOW) && (digitalRead(Stop_Peg) == LOW) && (Timer == false))
  {
    tft.setCursor(120, 100); tft.setTextColor(WHITE, BLACK); tft.print(time);
    Serial.println("Final Time");
    Serial.println(time); 
    Timer = true; Reset = true;
  }
  
  if (Reset == true) //resetFunc();
    {
      TSPoint p = ts.getPoint();
      pinMode(XM, OUTPUT);      pinMode(YP, OUTPUT);
  
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
        {
          p.x = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
          p.y = map(p.y, TS_MINY, TS_MAXY,  0,tft.width());
          Serial.print("("); Serial.print(p.x);    Serial.print(", "); Serial.print(p.y);    Serial.println(")");

            if((p.x >= 50) && (p.x <= 110) && (p.y >= 120) && (p.y <= 360) )
              { 
                tft.setRotation(0); tft.drawRect(50,120, 60, 240,  WHITE);
                digitalWrite(Power,HIGH);delay (500);
                digitalWrite(Power,LOW); delay (500);
                tft.drawRect(50,120, 60, 240,  RED);tft.setRotation(1); 
                Reset = false;Timer = false;time=0;
              }/*
            else if ((p.x >= 250) && (p.x <= 280) && (p.y >= 400) && (p.y <= 460) )
              {
                tft.drawRect(100, 400, 30, 60, WHITE);digitalWrite(13, LOW);
              }*/
        }
    }

          TSPoint p = ts.getPoint();
      pinMode(XM, OUTPUT);      pinMode(YP, OUTPUT);
  
        if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
        {
          p.x = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
          p.y = map(p.y, TS_MINY, TS_MAXY,  0,tft.width());
       //   Serial.print("("); Serial.print(p.x);    Serial.print(", "); Serial.print(p.y);    Serial.println(")");

            if((p.x >= 50) && (p.x <= 110) && (p.y >= 120) && (p.y <= 360) )
              { 
   tft.setCursor(120,155);
  tft.setTextColor(WHITE);  tft.setTextSize(2.9);
  tft.println("Please Keep the pegs in home position");
              }
        }
}






























