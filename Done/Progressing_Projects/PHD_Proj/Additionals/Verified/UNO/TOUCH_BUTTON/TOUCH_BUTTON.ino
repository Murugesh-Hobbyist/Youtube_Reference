#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

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

void setup(void) 
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x9341); 
  tft.fillScreen(BLACK);

  tft.fillRect(100, 200, 30, 60, RED);
 // tft.drawRect(100, 200, 30, 60, WHITE);
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000

void loop()
{
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
  {
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY,  0,tft.height());
    
    Serial.print("("); Serial.print(p.x);
    Serial.print(", "); Serial.print(p.y);
    Serial.println(")");
    
   if((p.x >= 100) && (p.x <= 130) && (p.y >= 200) && (p.y <= 260) )
   {
  tft.drawRect(100, 200, 30, 60, WHITE);digitalWrite(13, HIGH);
   delay(1000);digitalWrite(13, LOW);tft.drawRect(100, 200, 30, 60, RED);}
 //  else if ((p.x >= 0) && (p.x <= 320) && (p.y >= 30) && (p.y <= 60) )
 //  {digitalWrite(13, LOW);}
   


  
}}

