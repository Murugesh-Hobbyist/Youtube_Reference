
#define LCD_RD A0     // LCD Read goes to Analog 0
#define LCD_WR A1     // LCD Write goes to Analog 1
#define LCD_CD A2     // Command/Data goes to Analog 2
#define LCD_CS A3     // Chip Select goes to Analog 3
#define LCD_RESET A4  // Can alternately just connect to Arduino's reset pin

#include <elapsedMillis.h>
#include <SPI.h>           // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"  // Hardware-specific library
#include <MCUFRIEND_kbv.h>
#include "pitches.h"
MCUFRIEND_kbv tft;

#define	WHITE  0x0000 
#define	YELLOW 0x001F 
#define	SKY    0xF800
#define	PINK   0x07E0 
#define ORANGE 0x07FF 
#define GREEN  0xF81F  
#define BLUE   0xFFE0  
#define BLACK  0xFFFF 

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

long int SFT_Counter = 0;
bool SFT_State = true;
long int DFT_Counter = 0;
bool DFT_State = true;

int Count = 0;
int Old_Score = 0;
int Score = 0;

int note = 0;
int size = 0;

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


elapsedMillis timeElapsed = 0; 
unsigned int interval = 20000;

void setup(void) {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);

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
}

void loop(void)

{
  /*
  {
    tft.fillScreen(BLACK);
    tft.setCursor(400, 80);
    tft.setTextColor(WHITE);  tft.setTextSize(1);    tft.println("Hello World!");
    tft.setTextColor(YELLOW); tft.setTextSize(2);    tft.println(123.45);
    tft.setTextColor(RED);    tft.setTextSize(3);    tft.println(0xDEADBEEF, HEX);
    tft.setTextColor(GREEN);  tft.setTextSize(5);    tft.println("Groop");
    tft.setTextSize(2);    tft.println("I implore thee,");
    tft.setTextSize(1);    tft.println("my foonting turlingdromes.");
  }
*/

  int P2_Val = digitalRead(23);
  int P4_Val = digitalRead(25);
  int P5_Val = digitalRead(27);
  int P6_Val = digitalRead(29);
  int P8_Val = digitalRead(31);
  int P3_Val = digitalRead(33);
  int P1_Val = digitalRead(35);
  int P7_Val = digitalRead(37);
  int P9_Val = digitalRead(39);
  int DFT_SWITCH_Val = digitalRead(DFT_SWITCH);
  int SFT_SWITCH_Val = digitalRead(SFT_SWITCH);
  int MAZE_SWITCH_Val = digitalRead(MAZE_SWITCH);
  int AIM_SWITCH_Val = digitalRead(AIM_SWITCH);
  int SFT_Val = digitalRead(53);
  int DFT1_Val = digitalRead(51);
  int DFT2_Val = digitalRead(49);
  int PROBE_Val = analogRead(PROBE);
  /*
  Serial.print(P1_Val);Serial.print("  ");
  Serial.print(P2_Val);Serial.print("  ");
  Serial.print(P3_Val);Serial.print("  ");
  Serial.print(P4_Val);Serial.print("  ");
  Serial.print(P5_Val);Serial.print("  ");
  Serial.print(P6_Val);Serial.print("  ");
  Serial.print(P7_Val);Serial.print("  ");
  Serial.print(P8_Val);Serial.print("  ");
  Serial.print(P9_Val);Serial.print("  ");

  Serial.print(AIM_SWITCH_Val);Serial.print("  ");
  Serial.print(MAZE_SWITCH_Val);Serial.print("  ");
  Serial.print(SFT_SWITCH_Val);Serial.print("  ");
  Serial.print(DFT_SWITCH_Val);Serial.print("  ");

  Serial.print(SFT_Val);Serial.print("  ");
  Serial.print(DFT1_Val);Serial.print("  ");
  Serial.print(DFT2_Val);Serial.print("  ");
  Serial.println(PROBE_Val);Serial.println("  ");
  */

  if ((AIM_SWITCH_Val == HIGH) && (MAZE_SWITCH_Val == LOW) && (SFT_SWITCH_Val == LOW) && (DFT_SWITCH_Val == LOW)) {
    if (P1_Val == LOW) {
      Old_Score = Score;
      Score = Score + 9;
      AIM_DISPLAY_PRINT();
      digitalWrite(BUZZER, HIGH);
      delay(1000);
    }
    if (P2_Val == LOW) {
      Old_Score = Score;
      Score = Score + 8;
      AIM_DISPLAY_PRINT();
      delay(1000);
    }
    if (P3_Val == LOW) {
      Old_Score = Score;
      Score = Score + 7;
      AIM_DISPLAY_PRINT();
      delay(1000);
    }
    if (P4_Val == LOW) {
      Old_Score = Score;
      Score = Score + 6;
      AIM_DISPLAY_PRINT();
      delay(1000);
    }
    if (P5_Val == LOW) {
      Old_Score = Score;
      Score = Score + 5;
      AIM_DISPLAY_PRINT();
      delay(1000);
    }
    if (P6_Val == LOW) {
      Old_Score = Score;
      Score = Score + 4;
      AIM_DISPLAY_PRINT();
      delay(1000);
    }
    if (P7_Val == LOW) {
      Old_Score = Score;
      Score = Score + 3;
      AIM_DISPLAY_PRINT();
      delay(1000);
    }
    if (P8_Val == LOW) {
      Old_Score = Score;
      Score = Score + 2;
      AIM_DISPLAY_PRINT();
      delay(1000);
    }
    if (P9_Val == LOW) {
      Old_Score = Score;
      Score = Score + 1;
      AIM_DISPLAY_PRINT();
      delay(1000);
    }
    if (Score >= 20) {
      Old_Score = Score;
      Score = 0;
      AIM_DISPLAY_PRINT();
      delay(1000);
    }
    Serial.print(" AIM switch on ");
    Serial.println(Score);
  }



  if ((AIM_SWITCH_Val == LOW) && (MAZE_SWITCH_Val == HIGH) && (SFT_SWITCH_Val == LOW) && (DFT_SWITCH_Val == LOW)) {
    //  PROBE_Val = map(PROBE_Val,140,630,0,100);
    if (PROBE_Val > 400) {

      while (PROBE_Val > 400) {
        int size = sizeof(durations) / sizeof(int);
        note = 0;

        while (PROBE_Val > 400 && note < size) {

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
    Serial.print(" AIM switch on ");
    //MAZE_DISPLAY_PRINT();
    Serial.println(PROBE_Val);
  }




  if ((AIM_SWITCH_Val == LOW) && (MAZE_SWITCH_Val == LOW) && (SFT_SWITCH_Val == HIGH) && (DFT_SWITCH_Val == LOW)) {
    if (timeElapsed < interval)
  {
    if (SFT_Val == HIGH && SFT_State == true) {
      SFT_Counter = SFT_Counter + 1;
      Serial.println(SFT_Counter);
      delay(1);
      digitalWrite(BUZZER, LOW);
      SFT_State = false;
      // SFT_DISPLAY_PRINT();
    }
    if (SFT_Val == LOW && SFT_State == false) {
      SFT_State = true;
      digitalWrite(BUZZER, HIGH);
    }
  }
  }




  if ((AIM_SWITCH_Val == LOW) && (MAZE_SWITCH_Val == LOW) && (SFT_SWITCH_Val == LOW) && (DFT_SWITCH_Val == HIGH)) {

        if (DFT1_Val == HIGH && DFT2_Val == LOW && DFT_State == true) {
      DFT_State = false;
      digitalWrite(BUZZER, LOW);


    }
    if (DFT1_Val == LOW && DFT2_Val == HIGH && DFT_State == false)
    {
      DFT_Counter = DFT_Counter + 1;
      Serial.println(DFT_Counter);
      delay(1);
      digitalWrite(BUZZER, HIGH);
      DFT_State = true;
      // SFT_DISPLAY_PRINT();
    }
  }
}

  


void AIM_DISPLAY_PRINT() {
 // tft.fillScreen(BLACK);
  tft.setTextColor(BLACK);
  tft.setCursor(200, 60);
  tft.setTextSize(18);
  tft.println(Old_Score);

  tft.setTextColor(GREEN);
 // tft.setCursor(200, 80);
 // tft.setTextSize(1);
 // tft.println("AIM switch on");
  tft.setCursor(200, 60);
  tft.setTextColor(SKY);
//  tft.setTextSize(2);
  tft.println(Score);
}

void MAZE_DISPLAY_PRINT() {
  tft.fillScreen(BLACK);
  tft.setCursor(200, 80);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.println("MAZE switch on");
  tft.setCursor(200, 60);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println(Score);
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