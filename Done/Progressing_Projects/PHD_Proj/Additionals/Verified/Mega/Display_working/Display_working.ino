
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

unsigned long testText();

void setup(void) 

{
    Serial.begin(9600);
    uint16_t ID = tft.readID(); 
    tft.begin(ID);
}

void loop(void) 

{
    tft.fillScreen(BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE);  tft.setTextSize(1);    tft.println("Hello World!");
    tft.setTextColor(YELLOW); tft.setTextSize(2);    tft.println(123.45);
    tft.setTextColor(RED);    tft.setTextSize(3);    tft.println(0xDEADBEEF, HEX);
    tft.setTextColor(GREEN);  tft.setTextSize(5);    tft.println("Groop");
    tft.setTextSize(2);    tft.println("I implore thee,");
    tft.setTextSize(1);    tft.println("my foonting turlingdromes.");
}

