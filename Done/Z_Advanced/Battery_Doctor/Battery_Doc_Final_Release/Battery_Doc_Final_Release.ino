#include <SPI.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "COOPBL5pt7b.h"
#include "SHOWG5pt7b.h"
#include "MTCORSVA5pt7b.h"

#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);    

#define OLED_RESET LED_BUILTIN //D4
Adafruit_SSD1306 display(OLED_RESET); //D4
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#include <FirebaseArduino.h>
#define FIREBASE_HOST "batterydoc-3074c-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "QZh6pMDYle9jG3YkLeZxVcrvuW5QoARLRPCmSVZ9"
#define WIFI_SSID "Battery_Doc" // Change the name of your WIFI
#define WIFI_PASSWORD "12345678" // Change the password of your WIFI
//-------------------------------->GPIO_PINS
int Buzzer = D0;
//D1->OLED->SCK or SCL
//D2->OLED->SDA
//D3->Temperature Sensor
int Internet_Status = D4;
int Charge_Status = D5;
int Charge_Control = D6;
int VoltageCurr = D7;
int Battery_Control = D8;
//-------------------------------->Variables
int Read_Charge_Status;
float Read_Voltage;
float Read_Current;
const int OLED_Variables_Pos = 0;
const int OLED_Arrows_Pos = 50;
const int OLED_Values_Pos = 75;
String Status_String;

unsigned int total; // holds <= 64 analogReads
byte numReadings =64;
float offset = 575; // calibrate zero current
float span = 0.05; // calibrate max current | ~0.07315 is for 30A sensor
float currentin; // holds final current
float current_2Decimal;
float V_Max = 12.50;
int Battery_Level;

void setup()
{ pinMode(Internet_Status,OUTPUT);
pinMode(Battery_Control,OUTPUT);
pinMode(Charge_Control,OUTPUT);
pinMode(Charge_Status,INPUT);
pinMode(VoltageCurr,OUTPUT);

 pinMode(Charge_Status,INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setFont(&COOPBL5pt7b);
  dht.begin();

    Serial.begin(115200);
    pinMode(Charge_Status, INPUT);
    pinMode(VoltageCurr, OUTPUT);
    pinMode(Buzzer, OUTPUT); digitalWrite(Buzzer, LOW);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {Serial.print("."); delay(500);}
 
  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); 
  //Firebase.begin(FIREBASE_HOST);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int Read_Voltage_Interval() {
    digitalWrite(VoltageCurr, HIGH);    
    delay(200);
    return analogRead(0);
}

int Read_Current_Interval() {
    digitalWrite(VoltageCurr, LOW);
    delay(200);
        total = 0;
      for (int i = 0; i < numReadings; i++) total += analogRead(A0);
    //  for (int i = 0; i < numReadings; i++) total += Read_Current_Interval();
    currentin = (total / numReadings - offset) * span;
    return currentin;
}

void loop() 
{
  if (WiFi.status() != WL_CONNECTED){ 
    //Serial.println("WiFi Not Connected");
    digitalWrite(Internet_Status, HIGH); //Turn off WiFi LED
  }
  else{ 
    //Serial.println("WiFi Connected");
    digitalWrite(Internet_Status, LOW); //Turn on WiFi LED
//------------------------------------DISPLAY VARIABLES & ARROWS----------------------------------------
}display.clearDisplay();    
{
                   display.setCursor(OLED_Variables_Pos,6);
                  display.print("Charger"); 
                   display.setCursor(OLED_Variables_Pos,14);  
                  display.print("Level"); 
                   display.setCursor(OLED_Variables_Pos,22);  
                  display.print("Voltage"); 
                   display.setCursor(OLED_Variables_Pos,30);  
                  display.print("Temp"); 
}
{
                   display.setCursor(45,6);
                  display.print("--"); 
                   display.setCursor(OLED_Arrows_Pos,14);  
                  display.print("-->"); 
                   display.setCursor(OLED_Arrows_Pos,22);  
                  display.print("-->"); 
                   display.setCursor(OLED_Arrows_Pos,30);  
                  display.print("-->"); 
}
//------------------------------------------Charge Status-----------------------------------------------------------
    if (digitalRead(Charge_Status) == HIGH)
       {Status_String="Connected";
        Firebase.setString ("Charge Status",Status_String);};
    if (digitalRead(Charge_Status) == LOW)
       {Status_String="Dis-Connected";
        Firebase.setString ("Charge Status",Status_String);};
     delay(100);
//-------------------------------------------------------------------------------------------------------
//------------------------------------------Charge Status-------------------------------------------------------------
                  display.setCursor(55,6);
                  display.print(Status_String); 
                  display.display();
                  delay(10);

//-------------------------------------------------------------------------------------------------------

   //Voltage Read
//-------------------------------------------------------------------------------------------------------
    Read_Voltage = Read_Voltage_Interval();
    delay(200);
    Read_Voltage = Read_Voltage/77.5423729;
    float Voltage_1Decimcal = (roundf(Read_Voltage*10))/10;
    float Voltage_2Decimcal = (roundf(Read_Voltage*100))/100;
    Firebase.setFloat ("Voltage",Voltage_1Decimcal);
    delay(200);
    
//-------------------------------------------------------------------------------------------------------
//------------------------------------------Battery Level-------------------------------------------------------------
                   display.setCursor(OLED_Values_Pos,22);
                  display.print(Voltage_1Decimcal,1); 
                   display.setCursor(OLED_Values_Pos+28,22);
                  display.print("V"); 
                   display.display();                   delay(10);

//-------------------------------------------------------------------------------------------------------   

  //Battery Level
//-------------------------------------------------------------------------------------------------------   
if (Voltage_1Decimcal >= 10.50)
    { Battery_Level = 100-((V_Max - Voltage_2Decimcal)/.0235);
      Firebase.setFloat ("Battery Level",Battery_Level);};
      
if (Voltage_1Decimcal < 10.50)
    { Battery_Level = 0;
      Firebase.setFloat ("Battery Level",Battery_Level);};
//-------------------------------------------------------------------------------------------------------   
//------------------------------------------Battery Level-------------------------------------------------------------
                   display.setCursor(OLED_Values_Pos,14);
                  display.print(Battery_Level); 
                   display.setCursor(OLED_Values_Pos+18,14);
                  display.print("%"); 
                   display.display();                   delay(10);

//-------------------------------------------------------------------------------------------------------
   //Temperature Read
//-------------------------------------------------------------------------------------------------------
    float Read_Temperature = dht.readTemperature();
    Firebase.setFloat ("Temperature",Read_Temperature);
    delay(100);
//-------------------------------------------------------------------------------------------------------
//------------------------------------------Temperature Read-------------------------------------------------------------
 
                    display.setCursor(OLED_Values_Pos,30);
                  display.print(Read_Temperature,1); 
                    display.setCursor(OLED_Values_Pos+28,30);
                  display.print("*C"); 
                   display.display();
                   delay(10);
//-------------------------------------------------------------------------------------------------------

  //Battery Level Functions
//-------------------------------------------------------------------------------------------------------   
   if (Voltage_1Decimcal >= 12.5)
    { digitalWrite(Buzzer, HIGH); 
     digitalWrite(Charge_Control, LOW);
    Firebase.setString ("Battery Condition","Fully_Charged");
    delay (5000);};
   if (Voltage_1Decimcal == 10.5)
    { digitalWrite(Buzzer, HIGH);
    Firebase.setString ("Battery Condition","LOW_Battery");
    delay (5000);};
   if (12.5 > Voltage_1Decimcal > 10.5)
    { digitalWrite(Buzzer, LOW); 
    Firebase.setString ("Battery Condition","Ok");
    digitalWrite(Battery_Control, LOW);    //MOTOR ON
    delay (5000);};
   if (Voltage_1Decimcal < 10.5)
    { digitalWrite(Buzzer, HIGH);     
    digitalWrite(Battery_Control, HIGH);    //MOTOR OFF
    Firebase.setString ("Battery Condition","Too_Low→Disconnected");
    delay (5000);
    digitalWrite(Battery_Control, HIGH);    //MOTOR OFF
    };
    if ((Voltage_1Decimcal < 12.5) && (digitalRead(Charge_Status) == HIGH))
    {digitalWrite(Charge_Control, HIGH);}
    else{digitalWrite(Charge_Control, LOW);};
//-------------------------------------------------------------------------------------------------------   


  //Temperature Functions
//-------------------------------------------------------------------------------------------------------   
   if (Read_Temperature >= 36)
    {digitalWrite(Buzzer, HIGH);
    Firebase.setString ("Battery Condition","High_Temperature");
    delay (5000);
    digitalWrite(Battery_Control, HIGH);    //MOTOR OFF
    digitalWrite(Charge_Control, LOW); // CHARGER OFF
    digitalWrite(Buzzer, LOW);
    };
    if (Read_Temperature < 36)
    {digitalWrite(Buzzer, LOW);
    digitalWrite(Battery_Control, LOW);   
    Firebase.setString ("Battery Condition","Ok");
    };delay (20);

//-------------------------------------------------------------------------------------------------------

   //Current Read
//-------------------------------------------------------------------------------------------------------

  Read_Current = Read_Current_Interval();
   Serial.print(Read_Current);Serial.print("----");
  currentin = currentin +1.4;
  Serial.print("----");Serial.print(currentin);
  if (currentin < 0 ) {currentin = 0; Firebase.setFloat ("Current",currentin);};
  if (currentin > 0)
    {
      currentin = 5 * currentin;
     Serial.print("----");Serial.print(currentin);
      current_2Decimal = (roundf(currentin*100))/100;
     Serial.print("----");Serial.println(current_2Decimal);
      Firebase.setFloat ("Current",current_2Decimal);
    }; delay(200);
    
   //Current Functions
//-------------------------------------------------------------------------------------------------------
   if (current_2Decimal >= 2)
    { //Serial.println("-lkjhij--fedf-");
    digitalWrite(Buzzer, HIGH); 
    Firebase.setString ("Battery Condition","Heavy_Load...Disconnecting");
    delay (5000);
    digitalWrite(Battery_Control, HIGH); //motor off
    };
    if (current_2Decimal < 2)
    {digitalWrite(Buzzer, LOW);
     Firebase.setString ("Battery Condition","Ok");
    // digitalWrite(Battery_Control, LOW);//motor on
     };
//-------------------------------------------------------------------------------------------------------
}
