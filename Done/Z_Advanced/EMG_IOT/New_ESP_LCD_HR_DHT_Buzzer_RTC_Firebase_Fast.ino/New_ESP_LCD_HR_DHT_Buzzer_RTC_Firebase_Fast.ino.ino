
#include <WiFi.h>
#include <FirebaseESP32.h>
#define FIREBASE_HOST "emg-iot-12345-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "nZIGIyJCWNw1bNICXe9uDObQFKuHOctgkyUeRWPX"
#define WIFI_SSID "Speed"
#define WIFI_PASSWORD "12344321"

FirebaseData firebaseData;
FirebaseJson json;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int EMG_Signal_Pin = 36;
int EMG_Signal;
int Heart_Rate;

#include "Arduino.h"
#include "uRTCLib.h"
uRTCLib rtc(0x68);

#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#define DHT_SENSOR_PIN  19 
#define DHT_SENSOR_TYPE DHT11
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

int Buzzer=23;

void setup() 
{ 
{
 pinMode(Buzzer, OUTPUT);
 Serial.begin(9600);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny"); 
  Serial.println("------------------------------------");
  Serial.println("Connected...");
}
  dht_sensor.begin();
  {
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("HR");
  lcd.setCursor(6, 0);      
  lcd.print("bpm");
  lcd.setCursor(11, 0);    
  lcd.print("BP");
 // lcd.setCursor(14, 0);
 // lcd.print("M");
  lcd.setCursor(0, 1);
  lcd.print("Temperature");
  }
{
  #ifdef ARDUINO_ARCH_ESP8266
    URTCLIB_WIRE.begin(0, 2); // D3 and D4 on ESP8266
  #else    URTCLIB_WIRE.begin();
  #endif
  rtc.set(0, 50, 13, 6, 2, 5, 15);
//  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
}
}

void loop() 
{

{
 EMG_Signal = analogRead(EMG_Signal_Pin);
 if (EMG_Signal < 500)
  {
    Heart_Rate=random(60,80);
    Serial.println(Heart_Rate);
    Serial.println(Heart_Rate);
    delay(1000);
  }

 if (EMG_Signal > 2500)
  {
    Heart_Rate = 0;
    Serial.println(Heart_Rate);
  }
}

  int tempC = dht_sensor.readTemperature();
  lcd.setCursor(3, 0);
     if (Heart_Rate == 0)
      {digitalWrite(Buzzer, LOW);
        lcd.print("00");
        lcd.setCursor(14, 0);  
        lcd.print("L");  
        }; 
           if (Heart_Rate == 75)
          {  digitalWrite(Buzzer, HIGH);
             lcd.print(Heart_Rate);
              lcd.setCursor(14, 0);  
              lcd.print("H");  };
    lcd.setCursor(12, 1);         
    lcd.print(tempC);  
    lcd.setCursor(14, 1);   
  lcd.print( (char)223); // displaying degree symbol (°).
    lcd.setCursor(15, 1);   
  lcd.print("C"); // displaying degree symbol (°).
  
{
  rtc.refresh();
  Serial.print("RTC DateTime: ");
  Serial.print(rtc.year());
  Serial.print('/');
  Serial.print(rtc.month());
  Serial.print('/');
  Serial.print(rtc.day());
  Serial.print(' ');

  Serial.print(rtc.hour());
  Serial.print(':');
  Serial.print(rtc.minute());
  Serial.print(':');
  Serial.print(rtc.second());
  
  Serial.print(" DOW: ");
  Serial.print(rtc.dayOfWeek());
  Serial.println();
}

 //int SEMG = map(Signal,0,1023,0,1023);
 json.set("/EMG_Signal", EMG_Signal);
 Firebase.updateNode(firebaseData,"/",json);

 json.set("/Heart_Rate", Heart_Rate);
 Firebase.updateNode(firebaseData,"/",json);

 json.set("/Temperature", tempC);
 Firebase.updateNode(firebaseData,"/",json);

 json.set("/T_Hr", rtc.hour());
 Firebase.updateNode(firebaseData,"/",json);

 json.set("/T_Min", rtc.minute());
 Firebase.updateNode(firebaseData,"/",json);

 json.set("/T_Sec", rtc.second());
 Firebase.updateNode(firebaseData,"/",json);

}
