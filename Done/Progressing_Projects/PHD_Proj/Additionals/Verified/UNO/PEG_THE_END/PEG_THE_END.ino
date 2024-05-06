#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_TFTLCD.h>  // Hardware-specific library
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
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TFTSevenSegmentClockDisplay clockDisplayD(&tft, 120, 30, 8, 12, YELLOW, tft.color565(20, 20, 20), 1, true, 1);
TFTSevenSegmentClockDisplay clockDisplayA(&tft, 80, 30, 40, 80, YELLOW, tft.color565(20, 20, 20), 10, false, 1.7);

const int Start_Peg = 10;
const int Stop_Peg = 11;
const int Power = 12;

bool Timer = false;
bool Reset = false;
int time = 0;
bool Check = false;
bool Clear = false;
bool Homing = false;
bool Intro1 = false;
bool Intro2 = false;
bool Thanks = false;
int Voltage = 0;
void setup(void) {

  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextSize(6);

  Serial.begin(9600);

  pinMode(A5, INPUT);
  pinMode(13, OUTPUT);
  pinMode(Start_Peg, INPUT_PULLUP);
  pinMode(Stop_Peg, INPUT_PULLUP);
  pinMode(Power, OUTPUT);

  digitalWrite(Start_Peg, HIGH);
  digitalWrite(Stop_Peg, HIGH);
  digitalWrite(Power, LOW);

  tft.reset();
  tft.begin(0x9341);
  tft.fillScreen(BLACK);
  //tft.fillRect(50,120, 60, 240, RED);
  // tft.fillRect(250, 200, 30, 60, GREEN);
  tft.setRotation(1);
  //tft.setCursor(140,265);
  //    tft.setCursor(170,255);
  // tft.setTextColor(WHITE);  tft.setTextSize(2.9);
  // tft.println("Reset");
  //  clockDisplayA.displaySeconds(time, toggleSeparator);
}
#define MINPRESSURE 10
#define MAXPRESSURE 1000
void (*resetFunc)(void) = 0;

void loop(void) 

{
  int sensorValue1 = digitalRead(Start_Peg);
  int sensorValue2 = digitalRead(Stop_Peg);
  // int sensorValue1 = analogRead(A5);
  Serial.print("sensorValue1-->");
  Serial.print(sensorValue1);
  Serial.print("    ");
  Serial.print("sensorValue2-->");
  Serial.println(sensorValue2);
  // time = time+1;

  while ((digitalRead(Start_Peg) == HIGH) && (digitalRead(Stop_Peg) == HIGH) && (Timer == false))  //Not homed
  {
    tft.setTextColor(WHITE);
   // tft.setTextSize(1);  tft.setCursor(390, 26);      tft.setTextColor(GREEN);  tft.print("BT~");
        tft.setRotation(1);
   while (Intro1 == false) 
    {
       tft.setCursor(140, 90);
        tft.setTextColor(YELLOW);
        tft.setTextSize(2);
        tft.print("Modified");
        tft.setCursor(42, 140);
        tft.setTextColor(YELLOW);
        tft.print("9-Hole Peg Board ");
        tft.setCursor(215, 185);
        tft.setTextColor(GREEN);tft.setTextSize(1); 
        tft.print("With");
        tft.setCursor(120, 250);tft.setTextSize(2); 
        tft.setTextColor(WHITE);
        tft.print("Auto Timer");
        delay(1000);
      tft.fillScreen(BLACK);
      Intro1=true;
    }


        tft.setRotation(1);
       tft.setCursor(110, 100);
        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        tft.print("Please Keep ");
        tft.setCursor(80, 155);
        tft.print("All the pegs in");
        tft.setCursor(50, 220);
        tft.setTextColor(GREEN);
        tft.print("HOME POSITION");
        tft.setTextColor(WHITE);
    tft.setTextSize(1);  tft.setCursor(430, 26);      tft.setTextColor(BLACK);  tft.print(Voltage);
    Serial.print("Voltage-->");    Serial.println(analogRead(A5));   
 //   Voltage = map(analogRead(A5),850,960,1,100);
        Voltage = map(analogRead(A5),850,960,1,100);

    Serial.print("Voltage-->");    Serial.println(Voltage);   
    tft.setTextSize(1); 
   // tft.setCursor(430, 26);      tft.setTextColor(GREEN);  tft.print(Voltage/3.63);
    tft.setTextColor(WHITE);
  }

  while ((digitalRead(Start_Peg) == LOW) && (digitalRead(Stop_Peg) == HIGH) && (Timer == false))  //homed
  {
    while (Intro2 == false && Intro1==false) 
    {
       tft.setCursor(140, 90);
        tft.setTextColor(YELLOW);
        tft.setTextSize(2);
        tft.print("Modified");
        tft.setCursor(42, 140);
        tft.setTextColor(YELLOW);
        tft.print("9-Hole Peg Board ");
        tft.setCursor(215, 185);
        tft.setTextColor(GREEN);tft.setTextSize(1); 
        tft.print("With");
        tft.setCursor(120, 250);tft.setTextSize(2); 
        tft.setTextColor(WHITE);
        tft.print("Auto Timer");
        delay(1000);
      tft.fillScreen(BLACK);
      Intro2=true;
    }
    while (Clear == false) 
    {
      tft.fillScreen(BLACK);
      delay(10);
      tft.setTextSize(2);
      tft.setCursor(75, 100);
      tft.print("Homing Done!");
      tft.setCursor(78, 165);
      tft.print("Let's Proceed");
      Check = true;
      delay(1000);
        tft.setRotation(0);
        tft.fillRect(50, 120, 60, 240, RED);
        tft.setRotation(1);
       // tft.setCursor(170, 255);
       tft.setCursor(200, 255);
        tft.print("GO");

      while (Homing == false) 
      {
       TSPoint p = ts.getPoint();
       pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE ) 
    {
      p.x = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
      Serial.print("(");
      Serial.print(p.x);
      Serial.print(", ");
      Serial.print(p.y);
      Serial.println(")");

      if ((p.x >= 50) && (p.x <= 110) && (p.y >= 120) && (p.y <= 360)&& Homing == false) 
      {
        tft.setRotation(0);
        tft.drawRect(50, 120, 60, 240, WHITE);
        tft.fillScreen(BLACK);
        delay(10);
        tft.setRotation(1);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        // int sensorValue1 = analogRead(A5);

        tft.setRotation(0);
        tft.setRotation(1);Homing=true;
        //  Reset = false;Timer = false;time=0; Check = false; Clear = false;
      }}}

      tft.fillScreen(BLACK);
      clockDisplayA.displaySeconds(time, toggleSeparator);
       tft.setRotation(1);
       tft.setTextSize(1);
       tft.setCursor(125,150);
      tft.print("Min");
       tft.setTextSize(1.5);
      tft.setCursor(215,210);
      tft.print("Second(s)");
      Clear = true;
    }
    digitalWrite(Power, HIGH);
    delay(6);
    digitalWrite(Power, LOW);
    delay(6);

    while ((digitalRead(Start_Peg) == HIGH) && (digitalRead(Stop_Peg) == HIGH) && (Timer == false) && (Check == true))  // moved
    {                                                                                                                   //tft.fillScreen(BLACK);       delay(1000);
                                                                                                                        //  while (Clear == true) { tft.fillScreen(BLACK); delay(10); Clear =false;}
      time = time + 1;
      clockDisplayA.displaySeconds(time/7.41, toggleSeparator);
    }
  }

  while ((digitalRead(Start_Peg) == HIGH) && (digitalRead(Stop_Peg) == LOW) && (Timer == false)) 
  {

    while (Thanks == false) 
    {
        tft.fillScreen(BLACK);
       tft.setCursor(185, 90);
        tft.setTextColor(YELLOW);
        tft.setTextSize(2);
        tft.print("Hey !!!");
        tft.setCursor(39, 150);
        tft.setTextColor(YELLOW);
        tft.print("You Are Awesome ");
        tft.setCursor(40, 220);
        tft.setTextColor(WHITE);
        tft.print("Exceptional Work");
        delay(1000);
        tft.fillScreen(BLACK);
        Thanks=true;
    }

    tft.fillScreen(BLACK);
    delay(10);
       tft.setTextSize(2);
    tft.setCursor(120, 75);
    tft.print("Final Value ");
    tft.setCursor(170, 110);
       tft.setTextSize(1);
        tft.print("In Second(s)");
tft.setCursor(150, 175);
       tft.setTextSize(3);   // tft.print((time));    

    tft.print((time/7.41));    
    
   // tft.setCursor(100, 180);
  //  tft.print(time*.08);
    tft.setRotation(0);
    tft.fillRect(50, 120, 60, 240, RED);
    tft.setRotation(1);
    tft.setCursor(170, 255);
       tft.setTextSize(2);
    tft.print("Reset");
    Timer = true;
    Reset = true;
  }

  if (Reset == true)  //resetFunc();
  {
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      p.x = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
      Serial.print("(");
      Serial.print(p.x);
      Serial.print(", ");
      Serial.print(p.y);
      Serial.println(")");

      if ((p.x >= 50) && (p.x <= 110) && (p.y >= 120) && (p.y <= 360) && (digitalRead(Start_Peg) == HIGH) && (digitalRead(Stop_Peg) == LOW)) {
        tft.setRotation(0);
        tft.drawRect(50, 120, 60, 240, WHITE);
        //    digitalWrite(Power,HIGH);delay (100);
        //   digitalWrite(Power,LOW); delay (100);
        tft.fillScreen(BLACK);
        delay(10);


        tft.setRotation(1);
       tft.setCursor(110, 60);
        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        tft.print("Please Keep ");
        tft.setCursor(80, 115);
        tft.print("All the pegs in");
        tft.setCursor(50, 180);
        tft.setTextColor(GREEN);
        tft.print("HOME POSITION");
        tft.setTextColor(WHITE);

        // int sensorValue1 = analogRead(A5);
        tft.setRotation(0);
        tft.fillRect(50, 120, 60, 240, RED);
        tft.setRotation(1);
        tft.setCursor(170, 255);
        tft.print("Reset");

        tft.setRotation(0);
        tft.drawRect(50, 120, 60, 240, RED);
        tft.setRotation(1);
        //  Reset = false;Timer = false;time=0; Check = false; Clear = false;
      }



      if ((p.x >= 50) && (p.x <= 110) && (p.y >= 120) && (p.y <= 360) && (digitalRead(Start_Peg) == LOW) && (digitalRead(Stop_Peg) == LOW)) 
      {
        tft.setRotation(0);
        tft.drawRect(50, 120, 60, 240, WHITE);
        digitalWrite(Power, HIGH);
        delay(100);
        digitalWrite(Power, LOW);
        delay(100);
        tft.fillScreen(BLACK);
        delay(10);


        tft.setRotation(1);
        tft.setCursor(100, 120);
        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        Reset = false;
        Timer = false;
        time = 0;
        Check = false;
        Clear = false;Homing =false;Intro1=false; Intro2=false;Thanks=false;
      }
    }
  }//    */
}
