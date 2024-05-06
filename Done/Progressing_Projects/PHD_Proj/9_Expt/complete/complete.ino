
#define LCD_RD A0     // LCD Read goes to Analog 0
#define LCD_WR A1     // LCD Write goes to Analog 1
#define LCD_CD A2     // Command/Data goes to Analog 2
#define LCD_CS A3     // Chip Select goes to Analog 3
#define LCD_RESET A4  // Can alternately just connect to Arduino's reset pin

#include <elapsedMillis.h>
#include "pitches.h"
#include <SPI.h>           // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"  // Hardware-specific library
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
MCUFRIEND_kbv tft;

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 100
#define TS_MINY 180
#define TS_MAXX 950
#define TS_MAXY 860

#define MINPRESSURE 10
#define MAXPRESSURE 1000
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
uint16_t xpos, ypos;

#define WHITE 0x0000
#define YELLOW 0x001F
#define SKY 0xF800
#define PINK 0x07E0
#define RED 0x07FF
#define GREEN 0xF81F
#define BLUE 0xFFE0
#define BLACK 0xFFFF

#define P2 23
#define P4 25
#define P5 27
#define P6 29
#define P8 31
#define P3 33
#define P1 35
#define P7 37
#define P9 39

#define DFT_SWITCH 41
#define SFT_SWITCH 43
#define AIM_SWITCH 47
#define MAZE_SWITCH 45

#define DFT1 49
#define DFT2 51
#define BUZZER 52
#define SFT 53
#define PROBE A15

long int Old_SFT_Counter = 0;
long int SFT_Counter = 0;
bool SFT_State = true;
long int Old_DFT_Counter = 0;
long int DFT_Counter = 0;
bool DFT_State = true;

int note = 0;
int size = 0;

int P2_Val;
int P4_Val;
int P5_Val;
int P6_Val;
int P8_Val;
int P3_Val;
int P1_Val;
int P7_Val;
int P9_Val;
int DFT_SWITCH_Val;
int SFT_SWITCH_Val;
int MAZE_SWITCH_Val;
int AIM_SWITCH_Val;
int SFT_Val;
int DFT1_Val;
int DFT2_Val;
int PROBE_Val;

int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

int durations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

bool No_Game = false;
bool Aim_Game = false;
bool Maze_Game = false;
bool SFT_Game = false;
bool DFT_Game = false;


bool Aim_Info = true;
bool Aim_Play = true;
bool Aim_Once = true;

bool Aim_Result = true;
long Old_Aim_Counter = 1;
long Aim_Counter = 1;
long Old_Aim_RandNumber;
long Aim_RandNumber;
bool Another_Aim = true;
//bool Aim_Reset=true;



bool Maze_Info = true;
bool Maze_Result = true;
bool Maze_Play = true;
bool Maze_Once = true;


bool SFT_Info = true;
bool SFT_Result = true;
bool SFT_Play = true;
bool SFT_Once = true;


bool DFT_Info = true;
bool DFT_Result = true;
bool DFT_Play = true;
bool DFT_Once = true;

int Count = 0;
int Old_Score = 0;
int Score = 0;
bool Black_Screen = true;


void setup(void) {
  tft.reset();
  tft.begin(tft.readID());
  Serial.begin(9600);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
  pinMode(P4, INPUT_PULLUP);
  pinMode(P5, INPUT_PULLUP);
  pinMode(P6, INPUT_PULLUP);
  pinMode(P7, INPUT_PULLUP);
  pinMode(P8, INPUT_PULLUP);
  pinMode(P9, INPUT_PULLUP);

  pinMode(DFT_SWITCH, INPUT);
  pinMode(SFT_SWITCH, INPUT);
  pinMode(MAZE_SWITCH, INPUT);
  pinMode(AIM_SWITCH, INPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(DFT1, INPUT);
  pinMode(DFT2, INPUT);
  pinMode(SFT, INPUT);
  pinMode(PROBE, INPUT);
  digitalWrite(BUZZER, HIGH);

  tft.fillScreen(BLACK);
  tft.setRotation(3);
  //tft.fillScreen(BLACK);
  //tft.fillRect(190, 130, 100, 60, SKY);


  tft.setCursor(160, 100);
  tft.setTextColor(YELLOW);
  tft.setTextSize(4);
  tft.print("Welcome");
  tft.setCursor(160, 150);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.print("Comrade !");
  tft.fillScreen(BLACK);
  tft.setCursor(70, 140);
  tft.setTextColor(SKY);
  tft.setTextSize(3);
  tft.print("Equipment activated!");
}

void loop(void)

{
  Read_Pins();
  //  Print_Pins();
  //  tft.print("Equipment activated!");

  if ((AIM_SWITCH_Val == LOW) && (MAZE_SWITCH_Val == LOW) && (SFT_SWITCH_Val == LOW) && (DFT_SWITCH_Val == LOW)) {
    while (No_Game == false) {
      tft.fillScreen(BLACK);
      No_Game = true;
      Aim_Game = false;
      Maze_Game = false;
      SFT_Game = false;
      DFT_Game = false;

                    Old_SFT_Counter = 1;
                    SFT_Counter = 1;
                    Old_DFT_Counter = 1;
                    DFT_Counter = 0;
                    Old_Aim_Counter = 1;
                    Aim_Counter = 1;
                    Old_SFT_Counter = 1;
                    SFT_Counter = 0;

    }
    tft.setCursor(70, 60);    tft.setTextColor(SKY);    tft.setTextSize(3);    tft.print("ARM ABILITY TRAINING");    
    tft.setCursor(30, 120);    tft.setTextColor(WHITE);    tft.setTextSize(3);    tft.print("Motor Learning Principle");
    tft.setCursor(110, 190);    tft.setTextColor(YELLOW);    tft.setTextSize(3);    tft.print("Please Switch ON");
    tft.setCursor(160, 240);    tft.setTextColor(GREEN);    tft.setTextSize(3);    tft.print("Any Game");
    Another_Aim = true;
    //  Black_Screen = true;
    //  Aim_Reset=true;
  }


  if ((AIM_SWITCH_Val == HIGH) && (MAZE_SWITCH_Val == LOW) && (SFT_SWITCH_Val == LOW) && (DFT_SWITCH_Val == LOW)) {
    while (Aim_Game == false && AIM_SWITCH_Val == HIGH) {
      tft.fillScreen(BLACK);
      Aim_Game = true;
      No_Game = false;
      Maze_Game = false;
      SFT_Game = false;
      DFT_Game = false;Aim_Once = true;

    }
    //Aim_Home();
    //Aim_Once=true;


    while (Aim_Game == true && AIM_SWITCH_Val == HIGH) {
      //Aim_Home();
      AIM_SWITCH_Val = digitalRead(AIM_SWITCH);



  while (Aim_Once == true)
   {
          tft.setTextSize(3);
          tft.setTextColor(SKY);  tft.setCursor(185, 50);  tft.println("AIMING"); 
          tft.setTextColor(YELLOW);  tft.setCursor(90, 90);  tft.println("(Random Practice)"); 
          tft.setTextColor(WHITE);  tft.setCursor(80, 130);  tft.println("Improves Attention"); 
      tft.fillRect(60, 200, 160, 60, GREEN);
      tft.fillRect(260, 200, 160, 60, GREEN);

      tft.setTextSize(3);
      tft.setTextColor(RED);
      tft.setCursor(105, 215);
      tft.print("Info");
      tft.setTextSize(3);
      tft.setTextColor(RED);
      tft.setCursor(305, 215);
      tft.print("Play");
      Aim_Info = true;
      Aim_Result = true;
      Aim_Play = true;
Aim_Once = false;

  }


      TSPoint p = ts.getPoint();
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
        ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);

        if ((xpos >= 60) && (xpos <= 220) && (ypos >= 200) && (ypos <= 260)) {  //////////info click
        Aim_Once = true;

          tft.drawRect(60, 200, 160, 60, RED);
          delay(200);
          tft.fillScreen(BLACK);
      //tft.setTextSize(2);
          tft.setTextColor(PINK);  tft.setCursor(90, 50);  tft.println("20 Random Numbers");          
          tft.setTextColor(SKY);  tft.setCursor(70, 90);  tft.println("Be Ready with Probe"); 
          tft.setTextColor(WHITE);  tft.setCursor(70, 130);  tft.println("Now! Hit the Target");          
          tft.setTextColor(WHITE);  tft.setCursor(135, 170);  tft.println("as Displayed");          


          tft.fillRect(160, 220, 160, 60, GREEN);           tft.setTextColor(RED);          tft.setCursor(173, 238);          tft.println("Got You!");  

          while (Aim_Info == true && AIM_SWITCH_Val == HIGH) {  ///////////////back home release
            AIM_SWITCH_Val = digitalRead(AIM_SWITCH);

            TSPoint p = ts.getPoint();
            pinMode(XM, OUTPUT);
            pinMode(YP, OUTPUT);
            if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
              xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
              ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);
              Serial.print("(");
              Serial.print(xpos);
              Serial.print(", ");
              Serial.print(ypos);
              Serial.println(")");
              if ((xpos >= 160) && (xpos <= 320) && (ypos >= 220) && (ypos <= 280)) {
                tft.drawRect(160, 220, 160, 60, RED);
                tft.fillScreen(BLACK);
                Aim_Info = false;
                delay(1000);
                xpos = 0;
                ypos = 0;
              }
            }
          }
        }

        if ((xpos >= 260) && (xpos <= 320) && (ypos >= 200) && (ypos <= 260)) {
          Aim_Once = true;

          tft.drawRect(260, 200, 160, 60, RED);
          delay(200);
          tft.fillScreen(BLACK);
          tft.setTextSize(2);
          tft.setTextColor(PINK);
          tft.setCursor(150, 20);
          tft.println("Touch the values");

          while (Aim_Play == true && AIM_SWITCH_Val == HIGH) {
            AIM_SWITCH_Val = digitalRead(AIM_SWITCH);

            //   Aim_Play=false;
            if (Another_Aim == true) {
              Aim_RandNumber = random(1, 10);
              Another_Aim = false;
              AIM_DISPLAY_PRINT();
              Serial.println("random is -- ");
              Serial.println(Aim_RandNumber);
            }
            P2_Val = digitalRead(23);
            P4_Val = digitalRead(25);
            P5_Val = digitalRead(27);
            P6_Val = digitalRead(29);
            P8_Val = digitalRead(31);
            P3_Val = digitalRead(33);
            P1_Val = digitalRead(35);
            P7_Val = digitalRead(37);
            P9_Val = digitalRead(39);
            AIM_SWITCH_Val = digitalRead(AIM_SWITCH);


            if (P1_Val == LOW && Aim_RandNumber == 9) {
              Old_Aim_Counter = Aim_Counter;
              Aim_Counter = Aim_Counter + 1;
              Another_Aim = true;
              Old_Aim_RandNumber = Aim_RandNumber;
              digitalWrite(BUZZER, LOW);
              delay(200);
              digitalWrite(BUZZER, HIGH);
            }
            if (P2_Val == LOW && Aim_RandNumber == 8) {
              Old_Aim_Counter = Aim_Counter;
              Aim_Counter = Aim_Counter + 1;
              Another_Aim = true;
              Old_Aim_RandNumber = Aim_RandNumber;
              digitalWrite(BUZZER, LOW);
              delay(200);
              digitalWrite(BUZZER, HIGH);
            }
            if (P3_Val == LOW && Aim_RandNumber == 7) {
              Old_Aim_Counter = Aim_Counter;
              Aim_Counter = Aim_Counter + 1;
              Another_Aim = true;
              Old_Aim_RandNumber = Aim_RandNumber;
              digitalWrite(BUZZER, LOW);
              delay(200);
              digitalWrite(BUZZER, HIGH);
            }
            if (P4_Val == LOW && Aim_RandNumber == 6) {
              Old_Aim_Counter = Aim_Counter;
              Aim_Counter = Aim_Counter + 1;
              Another_Aim = true;
              Old_Aim_RandNumber = Aim_RandNumber;
              digitalWrite(BUZZER, LOW);
              delay(200);
              digitalWrite(BUZZER, HIGH);
            }
            if (P5_Val == LOW && Aim_RandNumber == 5) {
              Old_Aim_Counter = Aim_Counter;
              Aim_Counter = Aim_Counter + 1;
              Another_Aim = true;
              Old_Aim_RandNumber = Aim_RandNumber;
              digitalWrite(BUZZER, LOW);
              delay(200);
              digitalWrite(BUZZER, HIGH);
            }
            if (P6_Val == LOW && Aim_RandNumber == 4) {
              Old_Aim_Counter = Aim_Counter;
              Aim_Counter = Aim_Counter + 1;
              Another_Aim = true;
              Old_Aim_RandNumber = Aim_RandNumber;
              digitalWrite(BUZZER, LOW);
              delay(200);
              digitalWrite(BUZZER, HIGH);
            }
            if (P7_Val == LOW && Aim_RandNumber == 3) {
              Old_Aim_Counter = Aim_Counter;
              Aim_Counter = Aim_Counter + 1;
              Another_Aim = true;
              Old_Aim_RandNumber = Aim_RandNumber;
              digitalWrite(BUZZER, LOW);
              delay(200);
              digitalWrite(BUZZER, HIGH);
            }
            if (P8_Val == LOW && Aim_RandNumber == 2) {
              Old_Aim_Counter = Aim_Counter;
              Aim_Counter = Aim_Counter + 1;
              Another_Aim = true;
              Old_Aim_RandNumber = Aim_RandNumber;
              digitalWrite(BUZZER, LOW);
              delay(200);
              digitalWrite(BUZZER, HIGH);
            }
            if (P9_Val == LOW && Aim_RandNumber == 1) {
              Old_Aim_Counter = Aim_Counter;
              Aim_Counter = Aim_Counter + 1;
              Another_Aim = true;
              Old_Aim_RandNumber = Aim_RandNumber;
              digitalWrite(BUZZER, LOW);
              delay(200);
              digitalWrite(BUZZER, HIGH);
            }

            if (Old_Aim_Counter >= 20) {
              /*
              tft.fillScreen(BLACK);
              Old_Aim_Counter = 1;
              Aim_Counter = 1;
              tft.setTextSize(2);
              tft.setTextColor(PINK);
              tft.setCursor(150, 20);
              tft.println("Touch the values");
              */
              tft.fillScreen(BLACK);
              delay(200);
              tft.setTextSize(4);
              tft.setTextColor(PINK);
              tft.setCursor(190, 60);
              tft.println("Hey!");
              
              tft.setTextColor(SKY);  tft.setCursor(65, 110);   tft.println("Your Target Aim");
              
              tft.setTextColor(SKY);  tft.setCursor(160, 160);  tft.println("Reached");

              tft.fillRect(160, 220, 160, 60, GREEN);          tft.setTextColor(RED);          tft.setTextSize(3); tft.setCursor(195, 238);          tft.println("Reset");  

              while (Aim_Result == true && AIM_SWITCH_Val == HIGH) {  ///////////////back home release
                AIM_SWITCH_Val = digitalRead(AIM_SWITCH);

                TSPoint p = ts.getPoint();
                pinMode(XM, OUTPUT);
                pinMode(YP, OUTPUT);
                if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
                  xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
                  ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);
                  Serial.print("(");
                  Serial.print(xpos);
                  Serial.print(", ");
                  Serial.print(ypos);
                  Serial.println(")");
                  if ((xpos >= 160) && (xpos <= 320) && (ypos >= 220) && (ypos <= 280)) {
                    tft.drawRect(160, 220, 160, 60, RED);
                    tft.fillScreen(BLACK);
                    Aim_Play = false;
                    Aim_Result = false;
                    delay(100);
                    xpos = 0;
                    ypos = 0;
                    Old_Aim_Counter = 1;
                    Aim_Counter = 1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  // tft.setTextSize(2);  tft.setTextColor(PINK);    tft.setCursor(150, 20);
  //tft.println("Touch the values");





  if ((AIM_SWITCH_Val == LOW) && (MAZE_SWITCH_Val == HIGH) && (SFT_SWITCH_Val == LOW) && (DFT_SWITCH_Val == LOW)) {

    while (Maze_Game == false && MAZE_SWITCH_Val == HIGH) {
      tft.fillScreen(BLACK);
      Aim_Game = false;
      No_Game = false;
      Maze_Game = true;
      SFT_Game = false;
      DFT_Game = false;Maze_Once = true;
    }

    // Serial.println(PROBE_Val);

    //  PROBE_Val = map(PROBE_Val,140,630,0,100);
    while (Maze_Game == true && MAZE_SWITCH_Val == HIGH) {
      MAZE_SWITCH_Val = digitalRead(MAZE_SWITCH);
  while (Maze_Once == true)
   {


          tft.setTextColor(SKY);   tft.setTextSize(3); tft.setCursor(185, 50);  tft.println("MAZING"); 
          tft.setTextColor(YELLOW);tft.setTextSize(3);  tft.setCursor(40, 90);  tft.println("(Distributed Practice)"); 
          tft.setTextColor(WHITE); tft.setTextSize(3); tft.setCursor(40, 130);  tft.println("Improves Concentration"); 
                    
      tft.fillRect(60, 200, 160, 60, GREEN);
      tft.fillRect(260, 200, 160, 60, GREEN);

      tft.setTextSize(3);
      tft.setTextColor(RED);
      tft.setCursor(105, 215);
      tft.print("Info");
      tft.setTextSize(3);
      tft.setTextColor(RED);
      tft.setCursor(305, 215);
      tft.print("Play");
      Maze_Info = true;
      Maze_Result = true;
      Maze_Play = true;
Maze_Once =false;}

      TSPoint p = ts.getPoint();
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
        ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);

        if ((xpos >= 60) && (xpos <= 220) && (ypos >= 200) && (ypos <= 260)) {  //////////info click
        Maze_Once = true;
          tft.drawRect(60, 200, 160, 60, RED);
          delay(200);
          tft.fillScreen(BLACK);
          
          tft.setTextColor(PINK);  tft.setCursor(70, 50);  tft.println("Be Ready with Probe");       
          tft.setTextColor(SKY);  tft.setCursor(60, 90);  tft.println("Move Along the Track"); 
          tft.setTextColor(WHITE);  tft.setCursor(75, 130);  tft.println("Now! Reach the End");          
          tft.setTextColor(YELLOW);  tft.setCursor(60, 170);  tft.println("Don't break the Music");          

                   tft.fillRect(160, 220, 160, 60, GREEN);          tft.setTextColor(RED);          tft.setCursor(173, 238);          tft.println("Got You!");  



          while (Maze_Info == true && MAZE_SWITCH_Val == HIGH) {  ///////////////back home release
            MAZE_SWITCH_Val = digitalRead(MAZE_SWITCH);

            TSPoint p = ts.getPoint();
            pinMode(XM, OUTPUT);
            pinMode(YP, OUTPUT);
            if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
              xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
              ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);
              Serial.print("(");
              Serial.print(xpos);
              Serial.print(", ");
              Serial.print(ypos);
              Serial.println(")");
              if ((xpos >= 160) && (xpos <= 320) && (ypos >= 220) && (ypos <= 280)) {
                tft.drawRect(160, 220, 160, 60, RED);
                tft.fillScreen(BLACK);
                Maze_Info = false;
                delay(1000);
                xpos = 0;
                ypos = 0;
              }
            }
          }
        }

        if ((xpos >= 260) && (xpos <= 320) && (ypos >= 200) && (ypos <= 260)) {
          Maze_Once = true;
          tft.drawRect(260, 200, 160, 60, RED);
          delay(200);
          tft.fillScreen(BLACK);
          
                    
              tft.setTextSize(4);
          tft.setTextColor(YELLOW);  tft.setCursor(70, 80);  tft.println("Focus !");       
          tft.setTextColor(SKY);  tft.setCursor(140, 150);  tft.println("Focus !!"); 
          tft.setTextColor(WHITE);  tft.setCursor(210, 220);  tft.println("Focus !!!");          


          while (Maze_Play == true && MAZE_SWITCH_Val == HIGH) {
            MAZE_SWITCH_Val = digitalRead(MAZE_SWITCH);


            PROBE_Val = analogRead(PROBE);
            Serial.println(PROBE_Val);

            if (PROBE_Val > 175 && PROBE_Val < 810) {
              while (PROBE_Val > 175 && PROBE_Val < 810) {
                PROBE_Val = analogRead(PROBE);
                int size = sizeof(durations) / sizeof(int);
                note = 0;
                while (PROBE_Val > 175 && PROBE_Val < 810 && note < size) {
                  PROBE_Val = analogRead(PROBE);
                  PROBE_Val = analogRead(PROBE);
                  int duration = 1000 / durations[note];
                  tone(BUZZER, melody[note], duration);
                  int pauseBetweenNotes = duration * 2.1;
                  delay(pauseBetweenNotes);
                  noTone(BUZZER);
                  Serial.println(PROBE_Val);
                  note = note + 1;
                }
              }
              digitalWrite(BUZZER, HIGH);
            }
            Serial.println(PROBE_Val);
            //Serial.print(" AIM switch on ");
            //MAZE_DISPLAY_PRINT();

            if (PROBE_Val > 810) {
              /*
      tft.setTextSize(5);
      tft.fillScreen(BLACK);
      tft.setTextColor(SKY);
      tft.setCursor(100, 60);
      tft.println("Congrats !!!");
    */

              tft.fillScreen(BLACK);
              delay(200);
              tft.setTextSize(4);
              
              tft.setTextColor(SKY);  tft.setCursor(160,60);   tft.println("Awesome!");
              tft.setTextColor(YELLOW);  tft.setCursor(30,120);    tft.println("Landed Destination");

                       tft.fillRect(160, 220, 160, 60, GREEN);          tft.setTextColor(RED);           tft.setTextSize(3); tft.setCursor(195, 238);          tft.println("Reset");  

              while (Maze_Result == true && MAZE_SWITCH_Val == HIGH) {  ///////////////back home release
                MAZE_SWITCH_Val = digitalRead(MAZE_SWITCH);

                TSPoint p = ts.getPoint();
                pinMode(XM, OUTPUT);
                pinMode(YP, OUTPUT);
                if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
                  xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
                  ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);
                  Serial.print("(");
                  Serial.print(xpos);
                  Serial.print(", ");
                  Serial.print(ypos);
                  Serial.println(")");
                  if ((xpos >= 160) && (xpos <= 320) && (ypos >= 220) && (ypos <= 280)) {
                    tft.drawRect(160, 220, 160, 60, RED);
                    tft.fillScreen(BLACK);
                    Maze_Play = false;
                    Maze_Result = false;
                    delay(100);
                    xpos = 0;
                    ypos = 0;
                  }
                }
              }
            }
          }
        }
      }
    }
  }



  if ((AIM_SWITCH_Val == LOW) && (MAZE_SWITCH_Val == LOW) && (SFT_SWITCH_Val == HIGH) && (DFT_SWITCH_Val == LOW)) {
    while (SFT_Game == false && SFT_SWITCH_Val == HIGH) {
      tft.fillScreen(BLACK);
      Aim_Game = false;
      No_Game = false;
      Maze_Game = false;
      SFT_Game = true;
      DFT_Game = false;SFT_Once = true;
    }






    while (SFT_Game == true && SFT_SWITCH_Val == HIGH) {
      SFT_SWITCH_Val = digitalRead(SFT_SWITCH);

 while(SFT_Once == true){
      tft.setTextSize(3);


          tft.setTextColor(SKY);   tft.setTextSize(3); tft.setCursor(60, 50);  tft.println("Single Finger Tapping"); 
          tft.setTextColor(YELLOW);tft.setTextSize(3);  tft.setCursor(80, 90);  tft.println("(Blocked Practice)"); 
          tft.setTextColor(WHITE); tft.setTextSize(3); tft.setCursor(120, 130);  tft.println("Improves Pace"); 
                    
      tft.fillRect(60, 200, 160, 60, GREEN);
      tft.fillRect(260, 200, 160, 60, GREEN);

      tft.setTextSize(3);
      tft.setTextColor(RED);
      tft.setCursor(105, 215);
      tft.print("Info");
      tft.setTextSize(3);
      tft.setTextColor(RED);
      tft.setCursor(305, 215);
      tft.print("Play");
      SFT_Info = true;
      SFT_Result = true;
      SFT_Play = true;
      SFT_Once =false;
 }
      TSPoint p = ts.getPoint();
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
        ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);

        if ((xpos >= 60) && (xpos <= 220) && (ypos >= 200) && (ypos <= 260)) {  //////////info click
        SFT_Once = true;
          tft.drawRect(60, 200, 160, 60, RED);
          delay(200);
          tft.fillScreen(BLACK);
          tft.setTextColor(SKY); tft.setTextSize(3); tft.setCursor(95, 50);  tft.println("Place your Finger");          
          tft.setTextColor(SKY);  tft.setTextSize(3); tft.setCursor(100, 90);  tft.println("on the HP-SWITCH"); 
          tft.setTextColor(WHITE);tft.setTextSize(3); tft.setCursor(90, 130);  tft.println("Now! Tap 50 Times");          
          tft.setTextColor(WHITE);tft.setTextSize(3); tft.setCursor(200, 170);  tft.println("ASAP!");          



                   tft.fillRect(160, 220, 160, 60, GREEN);          tft.setTextColor(RED);          tft.setCursor(173, 238);          tft.println("Got You!");  

          while (SFT_Info == true && SFT_SWITCH_Val == HIGH) {  ///////////////back home release
            SFT_SWITCH_Val = digitalRead(SFT_SWITCH);

            TSPoint p = ts.getPoint();
            pinMode(XM, OUTPUT);
            pinMode(YP, OUTPUT);
            if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
              xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
              ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);
              Serial.print("(");
              Serial.print(xpos);
              Serial.print(", ");
              Serial.print(ypos);
              Serial.println(")");
              if ((xpos >= 160) && (xpos <= 320) && (ypos >= 220) && (ypos <= 280)) {
                tft.drawRect(160, 220, 160, 60, RED);
                tft.fillScreen(BLACK);
                SFT_Info = false;
                delay(1000);
                xpos = 0;
                ypos = 0;
              }
            }
          }
        }


        if ((xpos >= 260) && (xpos <= 320) && (ypos >= 200) && (ypos <= 260)) {
          SFT_Once = true;
          tft.drawRect(260, 200, 160, 60, RED);
          delay(200);
          tft.fillScreen(BLACK);
          tft.setTextSize(2);
          tft.setTextColor(PINK);
          tft.setCursor(120, 20);
          tft.println("Fast Tap the Switch");

          while (SFT_Play == true && SFT_SWITCH_Val == HIGH) {
            SFT_Val = digitalRead(53);

            SFT_SWITCH_Val = digitalRead(SFT_SWITCH);

            if (SFT_Val == HIGH && SFT_State == true && SFT_SWITCH_Val == HIGH) {
              delay(30);
              Old_SFT_Counter = SFT_Counter;
              SFT_Counter = SFT_Counter + 1;
              Serial.println(SFT_Counter);
              delay(1);
              digitalWrite(BUZZER, LOW);
              SFT_State = false;
              // SFT_DISPLAY_PRINT();{
              tft.setTextSize(18);
              tft.setTextColor(BLACK);
              tft.setCursor(200, 90);
              tft.println(Old_SFT_Counter);
              tft.setTextColor(SKY);
              tft.setCursor(200, 90);
              tft.println(SFT_Counter);
            }
            if (SFT_Val == LOW && SFT_State == false && SFT_SWITCH_Val == HIGH) {
              delay(30);
              SFT_State = true;
              digitalWrite(BUZZER, HIGH);
            }



            if (Old_SFT_Counter >=49) {

              digitalWrite(BUZZER, HIGH);
              tft.fillScreen(BLACK);
              delay(200);

              tft.setTextColor(SKY);    tft.setTextSize(3);     tft.setCursor(145,60);   tft.println("Well Done!");
              tft.setTextColor(YELLOW); tft.setTextSize(3);     tft.setCursor(100,120);    tft.println("Target Achieved");


                       tft.fillRect(160, 220, 160, 60, GREEN);          tft.setTextColor(RED);          tft.setTextSize(3); tft.setCursor(195, 238);          tft.println("Reset");   

              while (SFT_Result == true && SFT_SWITCH_Val == HIGH ) {  ///////////////back home release
                SFT_SWITCH_Val = digitalRead(SFT_SWITCH);

                TSPoint p = ts.getPoint();
                pinMode(XM, OUTPUT);
                pinMode(YP, OUTPUT);
                if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
                  xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
                  ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);
                  Serial.print("(");
                  Serial.print(xpos);
                  Serial.print(", ");
                  Serial.print(ypos);
                  Serial.println(")");
                  if ((xpos >= 160) && (xpos <= 320) && (ypos >= 220) && (ypos <= 280)) {
                    tft.drawRect(160, 220, 160, 60, RED);
                    tft.fillScreen(BLACK);
                    SFT_Play = false;
                    SFT_Result = false;
                    delay(100);
                    xpos = 0;
                    ypos = 0;
                    Old_SFT_Counter = 1;
                    SFT_Counter = 1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }




  if ((AIM_SWITCH_Val == LOW) && (MAZE_SWITCH_Val == LOW) && (SFT_SWITCH_Val == LOW) && (DFT_SWITCH_Val == HIGH)) {
    while (DFT_Game == false && DFT_SWITCH_Val == HIGH) {
      tft.fillScreen(BLACK);
      Aim_Game = false;
      No_Game = false;
      Maze_Game = false;
      SFT_Game = false;
      DFT_Game = true;DFT_Once = true;
    }




    while (DFT_Game == true && DFT_SWITCH_Val == HIGH) {
      DFT_SWITCH_Val = digitalRead(DFT_SWITCH);

while (DFT_Once == true){
   

          tft.setTextColor(SKY);   tft.setTextSize(3); tft.setCursor(60, 50);  tft.println("Double Finger Tapping"); 
          tft.setTextColor(YELLOW);tft.setTextSize(3);  tft.setCursor(95, 90);  tft.println("(Serial Practice)"); 
          tft.setTextColor(WHITE); tft.setTextSize(3); tft.setCursor(50, 130);  tft.println("Improves Co-ordination"); 


      tft.fillRect(60, 200, 160, 60, GREEN);
      tft.fillRect(260, 200, 160, 60, GREEN);

      tft.setTextSize(3);
      tft.setTextColor(RED);
      tft.setCursor(105, 215);
      tft.print("Info");
      tft.setTextSize(3);
      tft.setTextColor(RED);
      tft.setCursor(305, 215);
      tft.print("Play");
      DFT_Info = true;
      DFT_Result = true;
      DFT_Play = true;DFT_Once =false;
}
      TSPoint p = ts.getPoint();
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
        ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);

        if ((xpos >= 60) && (xpos <= 220) && (ypos >= 200) && (ypos <= 260)) {  //////////info click
        DFT_Once =true;
          tft.drawRect(60, 200, 160, 60, RED);
          delay(200);
          tft.fillScreen(BLACK);
        
          tft.setTextColor(SKY); tft.setTextSize(3); tft.setCursor(90, 40);  tft.println("Place your Fingers");          
          tft.setTextColor(SKY);  tft.setTextSize(2); tft.setCursor(140, 70);  tft.println("(Index & Middle)"); 
          tft.setTextColor(WHITE);tft.setTextSize(3); tft.setCursor(80, 110);  tft.println("on the HP-SWITCHES");     
          tft.setTextColor(YELLOW);tft.setTextSize(3); tft.setCursor(90, 145);  tft.println("Now! Tap 50 Times");          
          tft.setTextColor(YELLOW);tft.setTextSize(3); tft.setCursor(120, 180);  tft.println("Alternatively!");          

                   tft.fillRect(160, 220, 160, 60, GREEN);          tft.setTextColor(RED);          tft.setCursor(173, 238);          tft.println("Got You!");  


          while (DFT_Info == true && DFT_SWITCH_Val == HIGH) {  ///////////////back home release
            DFT_SWITCH_Val = digitalRead(DFT_SWITCH);

            TSPoint p = ts.getPoint();
            pinMode(XM, OUTPUT);
            pinMode(YP, OUTPUT);
            if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
              xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
              ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);
              Serial.print("(");
              Serial.print(xpos);
              Serial.print(", ");
              Serial.print(ypos);
              Serial.println(")");
              if ((xpos >= 160) && (xpos <= 320) && (ypos >= 220) && (ypos <= 280)) {
                tft.drawRect(160, 220, 160, 60, RED);
                tft.fillScreen(BLACK);
                DFT_Info = false;
                delay(1000);
                xpos = 0;
                ypos = 0;
              }
            }
          }
        }




        if ((xpos >= 260) && (xpos <= 320) && (ypos >= 200) && (ypos <= 260)) {
                  DFT_Once =true;
          tft.drawRect(260, 200, 160, 60, RED);
          delay(200);
          tft.fillScreen(BLACK);
          tft.setTextSize(2);
          tft.setTextColor(PINK);
          tft.setCursor(120, 20);
          tft.println("Fast Tap the Switch");

          while (DFT_Play == true && DFT_SWITCH_Val == HIGH) {

            DFT1_Val = digitalRead(51);
            DFT2_Val = digitalRead(49);
            DFT_SWITCH_Val = digitalRead(DFT_SWITCH);

            if (DFT1_Val == HIGH && DFT2_Val == LOW && DFT_State == true) {
              DFT_State = false;
              digitalWrite(BUZZER, LOW);
            }
            if (DFT1_Val == LOW && DFT2_Val == HIGH && DFT_State == false) {
              Old_DFT_Counter = DFT_Counter;
              DFT_Counter = DFT_Counter + 1;
              Serial.println(DFT_Counter);
              delay(1);
              digitalWrite(BUZZER, HIGH);
              DFT_State = true;
              tft.setTextSize(18);
              tft.setTextColor(BLACK);
              tft.setCursor(200, 90);
              tft.println(Old_DFT_Counter);
              tft.setTextColor(SKY);
              tft.setCursor(200, 90);
              tft.println(DFT_Counter);
              // SFT_DISPLAY_PRINT();
            }


            if (Old_DFT_Counter >= 49) {

              digitalWrite(BUZZER, HIGH);
              tft.fillScreen(BLACK);

              tft.setTextColor(SKY);    tft.setTextSize(3);     tft.setCursor(140,60);   tft.println("Great Effort!");
              tft.setTextColor(YELLOW); tft.setTextSize(3);     tft.setCursor(60,120);    tft.println("Mission Accomplished");


              tft.fillRect(160, 220, 160, 60, GREEN);  tft.setTextColor(RED);              tft.setTextSize(3); tft.setCursor(195, 238);          tft.println("Reset");  

              while (DFT_Result == true && DFT_SWITCH_Val == HIGH) {  ///////////////back home release
                DFT_SWITCH_Val = digitalRead(DFT_SWITCH);

                TSPoint p = ts.getPoint();
                pinMode(XM, OUTPUT);
                pinMode(YP, OUTPUT);
                if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
                  xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
                  ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);
                  Serial.print("(");
                  Serial.print(xpos);
                  Serial.print(", ");
                  Serial.print(ypos);
                  Serial.println(")");
                  if ((xpos >= 160) && (xpos <= 320) && (ypos >= 220) && (ypos <= 280)) {
                    tft.drawRect(160, 220, 160, 60, RED);
                    tft.fillScreen(BLACK);
                    DFT_Play = false;
                    DFT_Result = false;
                    delay(100);
                    xpos = 0;
                    ypos = 0;
                    Old_DFT_Counter = 1;
                    DFT_Counter = 0;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}




void AIM_DISPLAY_PRINT() {
  tft.setTextSize(18);
  tft.setTextColor(BLACK);
  tft.setCursor(200, 90);
  tft.println(Old_Aim_RandNumber);
  tft.setTextColor(SKY);
  tft.setCursor(200, 90);
  tft.println(Aim_RandNumber);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(420, 270);
  tft.println(Old_Aim_Counter);
  tft.setTextColor(RED);
  tft.setCursor(420, 270);
  tft.println(Aim_Counter);
}

void MAZE_DISPLAY_PRINT() {
  tft.setTextSize(18);
  tft.setTextColor(BLACK);
  tft.setCursor(200, 60);
  tft.println("Congrats !!!");
}


void SFT_DISPLAY_PRINT() {


  // tft.fillScreen(BLACK);
  tft.setTextColor(BLACK);
  tft.setCursor(200, 60);
  tft.setTextSize(2);
  tft.println(Old_Score);

  tft.setTextColor(GREEN);
  // tft.setCursor(200, 80);
  // tft.setTextSize(1);
  // tft.println("AIM switch on");
  tft.setCursor(200, 60);
  tft.setTextColor(SKY);
  //  tft.setTextSize(2);
  tft.println(Score);


  tft.fillScreen(BLACK);
  tft.setCursor(200, 80);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.println("SFT switch on");
  tft.setCursor(200, 60);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println(Score);
}





void Read_Pins() {
  P2_Val = digitalRead(23);
  P4_Val = digitalRead(25);
  P5_Val = digitalRead(27);
  P6_Val = digitalRead(29);
  P8_Val = digitalRead(31);
  P3_Val = digitalRead(33);
  P1_Val = digitalRead(35);
  P7_Val = digitalRead(37);
  P9_Val = digitalRead(39);
  DFT_SWITCH_Val = digitalRead(DFT_SWITCH);
  SFT_SWITCH_Val = digitalRead(SFT_SWITCH);
  MAZE_SWITCH_Val = digitalRead(MAZE_SWITCH);
  AIM_SWITCH_Val = digitalRead(AIM_SWITCH);
  SFT_Val = digitalRead(53);
  DFT1_Val = digitalRead(51);
  DFT2_Val = digitalRead(49);
  PROBE_Val = analogRead(PROBE);
}
void Print_Pins() {
  Serial.print(P1_Val);
  Serial.print("  ");
  Serial.print(P2_Val);
  Serial.print("  ");
  Serial.print(P3_Val);
  Serial.print("  ");
  Serial.print(P4_Val);
  Serial.print("  ");
  Serial.print(P5_Val);
  Serial.print("  ");
  Serial.print(P6_Val);
  Serial.print("  ");
  Serial.print(P7_Val);
  Serial.print("  ");
  Serial.print(P8_Val);
  Serial.print("  ");
  Serial.print(P9_Val);
  Serial.print("  ");

  Serial.print(AIM_SWITCH_Val);
  Serial.print("  ");
  Serial.print(MAZE_SWITCH_Val);
  Serial.print("  ");
  Serial.print(SFT_SWITCH_Val);
  Serial.print("  ");
  Serial.print(DFT_SWITCH_Val);
  Serial.print("  ");

  Serial.print(SFT_Val);
  Serial.print("  ");
  Serial.print(DFT1_Val);
  Serial.print("  ");
  Serial.print(DFT2_Val);
  Serial.print("  ");
  Serial.println(PROBE_Val);
  Serial.println("  ");
}


void testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(BLACK);
  tft.fillScreen(SKY);
  tft.fillScreen(GREEN);
  tft.fillScreen(BLUE);
  tft.fillScreen(BLACK);
  return micros() - start;
}

void Black_Screenx() {
  if (Black_Screen == true) {
    tft.fillScreen(BLACK);
    Black_Screen = false;
  }
}


void Aim_Home() {
  while (Aim_Once == true)
    tft.setTextSize(3);
  tft.setTextColor(PINK);
  tft.setCursor(100, 60);
  tft.println("You are selected");
  tft.setTextSize(3);
  tft.setTextColor(PINK);
  tft.setCursor(100, 95);
  tft.println("Aiming Challenge");
  tft.fillRect(60, 200, 160, 60, GREEN);
  tft.fillRect(260, 200, 160, 60, GREEN);

  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.setCursor(105, 215);
  tft.print("Info");
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.setCursor(305, 215);
  tft.print("Play");
  Aim_Once = false;
}