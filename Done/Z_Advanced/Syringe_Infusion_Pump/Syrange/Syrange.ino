

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
//#define WIFI_SSID "Speed"
//#define WIFI_PASSWORD "12344321"

#define WIFI_SSID "sara"
#define WIFI_PASSWORD "1234567890"

#define API_KEY "AIzaSyD9gsnuyvtrMG2VtIk1M9zSous_03j2oSc"
#define DATABASE_URL "syringe-ip-default-rtdb.firebaseio.com"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <Arduino.h>
#include "A4988.h"

int Step = D3 ; //GPIO14---D5 of Nodemcu--Step of stepper motor driver
int Dire = D4 ; //GPIO2---D4 of Nodemcu--Direction of stepper motor driver

const int spr = 200; //Steps per revolution
int RPM = 10; //Motor Speed in revolutions per minute
int Microsteps = 1; //Stepsize (1 for full steps, 2 for half steps, 4 for quarter steps, etc)
A4988 stepper(spr, Dire, Step);

int Buzzer=D0;
String ml_String;
int ml;
int length;
int Pot_Feed;
int Estep;
int Set_Button = D5 ;
int Reset_Button = D7 ;
int Total_Liquid = 20;
int Remaining_Liquid=20;
int Liquid_Injected=0;
bool alreadyRun = false;

void setup() 
{ 
  pinMode(Set_Button, INPUT);
  pinMode(Buzzer, OUTPUT);
  Serial.begin(9600);
  
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  pinMode(Step, OUTPUT); //Step pin as output
  pinMode(Dire,  OUTPUT); //Direcction pin as output
  digitalWrite(Step, LOW); // Currently no stepper motor movement
  digitalWrite(Dire, LOW);
  stepper.begin(RPM, Microsteps);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  //Serial.println();
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("Connected to Firebase");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);



    /*/
 // if (alreadyRun == false)
 //   alreadyRun = true;
    Firebase.RTDB.setInt(&fbdo, "/Total_Liquid", Total_Liquid);
    delay(1000);
    Firebase.RTDB.setInt(&fbdo, "/Remaining_Liquid", Remaining_Liquid);
    delay(1000);   
    Firebase.RTDB.setInt(&fbdo, "/Liquid_Injected", Liquid_Injected);
    delay(1000);
    Firebase.RTDB.setInt(&fbdo, "/Input_ml", 0);
    delay(1000);
    Serial.println("Initialised Database Variables");
    delay(1000);
  */


}




void loop() 
{


  lcd.setCursor(2, 0);
  lcd.print("INFUSION PUMP");
  /*
  {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("INFUSION PUMP");
  lcd.setCursor(4, 1);      
  lcd.print("Injecting");
  delay(2000);  
  
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("INFUSION PUMP");
  lcd.setCursor(6, 1);      
  lcd.print("HALT");
  delay(2000);  
  
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("INFUSION PUMP");
  lcd.setCursor(4, 1);      
  lcd.print("INJECTING");
  delay(2000);  

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("FLOW_R");
  lcd.setCursor(8, 0);      
  lcd.print("50 ml/s");
  lcd.setCursor(0, 1);
  lcd.print("DELIVERED");
  lcd.setCursor(10, 1);      
  lcd.print("50 %");
  delay(2000);  

  }
*/

 // if(Serial.available())
 // ml = Serial.parseInt(); 
 // set, setInt, setFloat, setDouble, setString, setJSON, setArray, setBlob, and setFile, setBool
 // get, getInt, getFloat, getDouble, getBool, getString, getJSON, getArray, getBlob, getFile.

 if (Firebase.RTDB.getString(&fbdo, "/Input_ml"))
    { 
      ml_String = fbdo.stringData();
    }
      ml_String.remove(0, 2);      
        length = ml_String.length();
      ml_String.remove((length-2),length);
        ml = ml_String.toInt();
                                  //        Serial.println(ml);

  int Pot_Val = analogRead(A0);
  Pot_Val = map(Pot_Val, 0, 1023, 0, 20);
 Serial.println(Pot_Val);

if (digitalRead(Set_Button) == HIGH)
   {
    Firebase.RTDB.setInt(&fbdo, "/Input_ml", 0);
    ml = Pot_Val;
   }
     // 1ml -> estep?
     //Estep = ml * constant
    //run stepper for estep

if (ml != 0)
{ 
  Remaining_Liquid = Remaining_Liquid - ml;
  Liquid_Injected = ml;

  if(Remaining_Liquid < 0)
  {
    Serial.println("Insufficient Liquid");    
    Remaining_Liquid = Remaining_Liquid + ml;
    Liquid_Injected = 0;
  }
    Firebase.RTDB.setInt(&fbdo, "/Remaining_Liquid", Remaining_Liquid);    
    Firebase.RTDB.setInt(&fbdo, "/Liquid_Injected", Liquid_Injected);
    delay(2000);
}

if (digitalRead(Reset_Button) == HIGH)
   {
      Total_Liquid = 20;
      Remaining_Liquid=20;
      Liquid_Injected=0;
    Firebase.RTDB.setInt(&fbdo, "/Total_Liquid", Total_Liquid);
    Firebase.RTDB.setInt(&fbdo, "/Remaining_Liquid", Remaining_Liquid);    
    Firebase.RTDB.setInt(&fbdo, "/Liquid_Injected", Liquid_Injected);
    Firebase.RTDB.setInt(&fbdo, "/Input_ml", 0);
   }


     // stepper.move(ml);

//Serial.println(" Steps"); 

 // if (ml == 1)
/*
if (digitalRead(buttonPin1) == HIGH)
{ ml = Pot_Val; 

Serial.print(" Steps"); 

Serial.println(ml); 
}
//Serial.print("Moving "); 
//Serial.print(ml); zz
stepper.move(ml);
//Serial.println(" Steps"); 


//object’s functions: fbdo.intData, fbdo.floatData, fbdo.doubleData, fbdo.boolData, fbdo.stringData, fbdo.jsonString, 
//fbdo.jsonObject, fbdo.jsonObjectPtr, fbdo.jsonArray, fbdo.jsonArrayPtr, fbdo.jsonData (for keeping parse/get result), 
//and fbdo.blobData.

*/
}
