#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//https://roboindia.com/tutorials/i2c-address-scanner-nodemcu/ --- wire connection
void setup() 
{
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("SATHISH");
  lcd.setCursor(5, 1);      
  lcd.print("SARA");
}

void loop() 
{}
