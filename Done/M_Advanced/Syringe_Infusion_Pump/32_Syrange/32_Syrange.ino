

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


#define WIFI_SSID "Sri"
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

int Step = 25 ; //GPIO14---D5 of Nodemcu--Step of stepper motor driver
int Dire = 26 ; //GPIO2---D4 of Nodemcu--Direction of stepper motor driver

int spr = 200; //Steps per revolution
int RPM = 10; //Motor Speed in revolutions per minute
int Microsteps = 1; //Stepsize (1 for full steps, 2 for half steps, 4 for quarter steps, etc)
A4988 stepper(spr, Dire, Step);

int Buzzer=13;
String ml_String;
int ml;
int length;
int Pot_Feed;
int Estep;
int Set_Button = 27;
int Reset_Button = 14;
int Reload_Button = 12;
int Limit_Switch = 32;
int Total_Liquid = 20;
int Remaining_Liquid=20;
int Liquid_Injected=0;
bool alreadyRun = false;

void setup() 
{ 
  pinMode(Set_Button, INPUT);
  pinMode(Reset_Button, INPUT);
  pinMode(Reload_Button, INPUT);
  pinMode(Limit_Switch, INPUT);
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
    Firebase.RTDB.setInt(&fbdo, "/Refill", 0);
    delay(1000);
    Firebase.RTDB.setString(&fbdo, "/Status", "All Set");
    delay(1000);
    Serial.println("Initialised Database Variables");
    delay(1000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("INFUSION PUMP");
  delay(2000);  
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Liquid I/P >");
  lcd.setCursor(12, 0);
  lcd.print("0");
  lcd.setCursor(14, 0);
  lcd.print("ml");

  lcd.setCursor(0, 1);      
  lcd.print("Remaining  >");
  lcd.setCursor(12, 1);      
  lcd.print("20");
  lcd.setCursor(14, 1);      
  lcd.print("ml");
}




void loop() 
{


 // lcd.setCursor(2, 0);
 // lcd.print("INFUSION PUMP");

  
 // if(Serial.available())
 // ml = Serial.parseInt(); 
 // set, setInt, setFloat, setDouble, setString, setJSON, setArray, setBlob, and setFile, setBool
 // get, getInt, getFloat, getDouble, getBool, getString, getJSON, getArray, getBlob, getFile.

if (digitalRead(Reload_Button) == HIGH)
   {
   //  Firebase.RTDB.setString(&fbdo, "/Status", "Refilling");
     while(digitalRead(Limit_Switch) == LOW)
      {  
        spr = 1000; //Steps per revolution
        stepper.move(-30);
      }  
   //  Firebase.RTDB.setInt(&fbdo, "/Refill", 0);
   }
/*
if ((Firebase.RTDB.getInt(&fbdo, "/Refill")) == 1)
   {
     while(digitalRead(Limit_Switch) == LOW)
      {  
        spr = 1000; //Steps per revolution
        stepper.move(-30);
      }  
     Firebase.RTDB.setInt(&fbdo, "/Refill", 0);
     Firebase.RTDB.setString(&fbdo, "/Status", "Refilling");
   }
*/



 if (Firebase.RTDB.getString(&fbdo, "/Input_ml"))
    { 
      ml_String = fbdo.stringData();
    }
      ml_String.remove(0, 2);      
        length = ml_String.length();
      ml_String.remove((length-2),length);
        ml = ml_String.toInt();
                                  //        Serial.println(ml);

  int Pot_Val = analogRead(33);
  Pot_Val = map(Pot_Val, 0, 4095, 0, 20);
 Serial.println(Pot_Val);

if (digitalRead(Set_Button) == HIGH)
   {
    Firebase.RTDB.setInt(&fbdo, "/Input_ml", 0);
    ml = Pot_Val;
   }


if (ml != 0)
{
  Remaining_Liquid = Remaining_Liquid - ml;
  Liquid_Injected = ml;

  if(Remaining_Liquid < 5)  {Serial.println("Liquid_Low"); 
  digitalWrite(Buzzer, HIGH); delay (5000); digitalWrite(Buzzer, LOW);
      Firebase.RTDB.setString(&fbdo, "/Status", "Liquid_Low");
  }

  if(Remaining_Liquid < 0)
  {
    Serial.println("Insufficient_Liquid");    
    Firebase.RTDB.setString(&fbdo, "/Status", "Insufficient_Liquid");
    Remaining_Liquid = Remaining_Liquid + ml;
    Liquid_Injected = 0;
    ml=0;
    Firebase.RTDB.setInt(&fbdo, "/Input_ml", 0);
    digitalWrite(Buzzer, HIGH); delay (5000); digitalWrite(Buzzer, LOW);
  }
    Firebase.RTDB.setInt(&fbdo, "/Remaining_Liquid", Remaining_Liquid);
    Firebase.RTDB.setInt(&fbdo, "/Liquid_Injected", Liquid_Injected);
   // delay(2000);
   
     // 25 steps/mm   --->     // 3.1mm / ml
     

  Estep = ml * 25 * 3.1 ;
  stepper.move(Estep);
  ml=0;
  Firebase.RTDB.setInt(&fbdo, "/Input_ml", 0);
}



if (digitalRead(Reset_Button) == HIGH)
   {
      Total_Liquid = 20;
      Remaining_Liquid=20;
      Liquid_Injected=0;
    Firebase.RTDB.setInt(&fbdo, "/Total_Liquid", 20);
    Firebase.RTDB.setInt(&fbdo, "/Remaining_Liquid", 20);    
    Firebase.RTDB.setInt(&fbdo, "/Liquid_Injected", 0);
    Firebase.RTDB.setInt(&fbdo, "/Input_ml", 0);
    Firebase.RTDB.setString(&fbdo, "/Status", "All Set");

  lcd.setCursor(12, 0);
  lcd.print(0);
  lcd.setCursor(12, 1);      
  lcd.print(20);
   }
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Liquid I/P >");
  lcd.setCursor(14, 0);
  lcd.print("ml");
  lcd.setCursor(0, 1);      
  lcd.print("Remaining  >");
  lcd.setCursor(14, 1);      
  lcd.print("ml");
  lcd.setCursor(12, 0);
  lcd.print(Pot_Val);
  lcd.setCursor(12, 1);      
  lcd.print(Remaining_Liquid);
    

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
