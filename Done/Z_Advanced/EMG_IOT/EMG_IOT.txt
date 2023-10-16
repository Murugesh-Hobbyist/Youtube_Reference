
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define WIFI_SSID "Speed"
#define WIFI_PASSWORD "12344321"
#define API_KEY "AIzaSyCdIJt8L4ZKnw2LH_TBDvEeNZFytn9tjfQ"
#define DATABASE_URL "emg-iotx-default-rtdb.firebaseio.com"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int EMG_Signal_Pin = 13;
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
int Stop_Alarm=12;
int From_APP;
String Blood_Pressure;
// int floatValue ;

void setup() 
{ 
 pinMode(Buzzer, OUTPUT);
 pinMode(EMG_Signal_Pin, INPUT);

 Serial.begin(9600);
 
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
//  rtc.set(0, 43, 19, 3, 2, 5, 23);
//  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
}

{
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

}

void loop() 
{
   EMG_Signal = analogRead(EMG_Signal_Pin);
   EMG_Signal = map(EMG_Signal, 0, 100, 0, 1023);
  //  Serial.println(EMG_Signal);

    Heart_Rate=random(65,80);
    //Serial.println(Heart_Rate);

      int tempC = dht_sensor.readTemperature();
  //lcd.clear();
       if (Heart_Rate < 71)
      {  Blood_Pressure = "L";
         digitalWrite(Buzzer, LOW);
         lcd.setCursor(3, 0);
         lcd.print(Heart_Rate);
         lcd.setCursor(14, 0);  
         lcd.print(Blood_Pressure);
      }
       if ((Heart_Rate > 70) && (Heart_Rate < 76))
      {  Blood_Pressure = "M";
         digitalWrite(Buzzer, LOW);
         lcd.setCursor(3, 0);
         lcd.print(Heart_Rate);
         lcd.setCursor(14, 0);
         lcd.print(Blood_Pressure);  
      }

      if (Heart_Rate > 75 )
      {  Blood_Pressure = "H";
         digitalWrite(Buzzer, HIGH);
         lcd.setCursor(3, 0);
         lcd.print(Heart_Rate);
         lcd.setCursor(14, 0);
         lcd.print(Blood_Pressure);
      }
    
    lcd.setCursor(12, 1);
    lcd.print(tempC);  
    lcd.setCursor(14, 1);   
    lcd.print( (char)223); // displaying degree symbol (°).
    lcd.setCursor(15, 1);   
    lcd.print("C"); // displaying degree symbol (°).
    /*
{
  rtc.refresh();
  Serial.print(rtc.hour());
  Serial.print(':');
  Serial.print(rtc.minute());
  Serial.print(':');
  Serial.println(rtc.second());

}*/
    Firebase.RTDB.setInt(&fbdo, "EMG_Signal", EMG_Signal);
    Firebase.RTDB.setInt(&fbdo, "Heart_Rate", Heart_Rate);
    Firebase.RTDB.setString(&fbdo, "Blood_Pressure", Blood_Pressure);
    Firebase.RTDB.setInt(&fbdo, "Temperature", tempC);
    //Firebase.RTDB.setInt(&fbdo, "T_Hr", rtc.hour());
    //Firebase.RTDB.setInt(&fbdo, "T_Min", rtc.minute());
    //Firebase.RTDB.setInt(&fbdo, "T_Sec", rtc.second());
// set, setInt, setFloat, setDouble, setString, setJSON, setArray, setBlob, and setFile, setBool
// get, getInt, getFloat, getDouble, getBool, getString, getJSON, getArray, getBlob, getFile.
String floatValue;

 if (Firebase.RTDB.getString(&fbdo, "/Alarm")) 
 {
    floatValue = fbdo.stringData();
    Serial.println(floatValue);
 }
      int num = floatValue.toInt();
             if (num == 1)
           { 
            digitalWrite(Buzzer, HIGH);
            delay(5000);  
            Firebase.RTDB.setInt(&fbdo, "/Alarm", 0);
            Serial.println("TRUE");
           }

//object’s functions: fbdo.intData, fbdo.floatData, fbdo.doubleData, fbdo.boolData, fbdo.stringData, fbdo.jsonString, 
//fbdo.jsonObject, fbdo.jsonObjectPtr, fbdo.jsonArray, fbdo.jsonArrayPtr, fbdo.jsonData (for keeping parse/get result), 
//and fbdo.blobData.

if (digitalRead(Stop_Alarm) == HIGH)
{
            digitalWrite(Buzzer, LOW);
            Firebase.RTDB.setInt(&fbdo, "/Alarm", 0);
}

}
