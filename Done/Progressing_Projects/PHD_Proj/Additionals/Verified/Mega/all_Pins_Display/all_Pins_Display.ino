
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

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
#define MAZE_SWITCH 45
#define AIM_SWITCH 47

#define DFT1 49
#define DFT2 51
#define SFT 53
#define PROBE A15

bool Timer = false;
int count = 0;

void setup(void) 
{
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

  pinMode(DFT1, INPUT_PULLUP);
  pinMode(DFT2, INPUT_PULLUP);
  pinMode(SFT, INPUT_PULLUP);
  pinMode(PROBE, INPUT);

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
    int DFT1_Val = digitalRead(49);
    int DFT2_Val = digitalRead(51);
    int SFT_Val = digitalRead(53);
    int PROBE_Val = analogRead(PROBE);

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
  
  while ((AIM_SWITCH_Val == HIGH) && (MAZE_SWITCH_Val == LOW) && (SFT_SWITCH_Val == LOW) && (DFT_SWITCH_Val == LOW)) 
                {  Serial.print(SFT_Val);Serial.print("  ");   }
}
