
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;  // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 100
#define TS_MINY 180
#define TS_MAXX 950
#define TS_MAXY 860

// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define MINPRESSURE 10  //200
#define MAXPRESSURE 1000
//240

// Assign human-readable names to some common 16-bit color values:
#define	WHITE  0x0000 
#define	YELLOW 0x001F 
#define	SKY    0xF800
#define	PINK   0x07E0 
#define ORANGE 0x07FF 
#define GREEN  0xF81F  
#define BLUE   0xFFE0  
#define BLACK  0xFFFF 

uint16_t xpos, ypos;

void setup(void) {
  tft.reset();
  tft.begin(tft.readID());
  Serial.begin(9600);
  tft.setRotation(3);  tft.fillScreen(WHITE);
  tft.fillRect(190, 130, 100, 60, SKY);
   //  tft.drawRect(190, 130, 100, 60, BLACK);
}

void loop() 
{
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    xpos = map(p.y, TS_MINX, TS_MAXX, 0, 480);
    ypos = map(p.x, TS_MINY, TS_MAXY, 0, 320);
      Serial.print("(");      Serial.print(xpos);
      Serial.print(", ");      Serial.print(ypos);      Serial.println(")");
    if ((xpos >= 190) && (xpos <= 290) && (ypos >= 130) && (ypos <= 190)) {
      tft.drawRect(190, 130, 100, 60, BLACK);
        } 
     
    }else tft.drawRect(190, 130, 100, 60, SKY);
  }