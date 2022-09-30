#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("HELLO");
  lcd.setCursor(5, 1);      
  lcd.print("WORLD");
}

void loop() 
{}
