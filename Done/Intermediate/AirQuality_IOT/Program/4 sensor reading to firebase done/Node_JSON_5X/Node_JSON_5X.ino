#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);

float distance;
float Water_Level;
int Temperature_Val;
float phValue;
//String quality =""; //ambiguous overload for 'operator='
String Global_quality = "";
//String Motor_Button="";

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "inject-38929-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "NtERcHXnmeoq5EwJK9ht3rSrW1pOE9bW6wuYlYzT"
//#define WIFI_SSID "Nithi"
//#define WIFI_PASSWORD "12345678"
#define WIFI_SSID "Water_QM"
#define WIFI_PASSWORD "12345678"

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte A[] = {
  B00100,
  B01010,
  B10001,
  B10001,
  B10101,
  B11111,
  B10001,
  B10001
};

byte T[] ={
  B11111,
  B11111,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B01110
};
byte DC[] ={
  B11000,
  B11000,
  B00000,
  B00111,
  B01000,
  B01000,
  B01000,
  B00111
};
byte PH[] ={
  B00101,
  B00111,
  B00111,
  B00101,
  B11000,
  B10100,
  B11000,
  B10000
};
byte L[] ={
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11111,
  B01111
};

void setup()
{
  pinMode(D3, OUTPUT);
  Serial.begin(9600);
  nodemcu.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  //Firebase.begin(FIREBASE_HOST);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  while (!Serial) continue;

  {
    lcd.begin(16, 2);
    lcd.init();
    // lcd.backlight();
  }
  {
    lcd.createChar(0, PH);
    lcd.createChar(1, T);
    lcd.createChar(2, DC);
    lcd.createChar(3, A);
    lcd.createChar(4, L);
    
    lcd.setCursor(0, 0);
    lcd.write(0);
    lcd.setCursor(9, 0);
    lcd.write(1);
    lcd.setCursor(15, 0);
    lcd.write(2);
    lcd.setCursor(0, 1);
    lcd.write(3);
    lcd.setCursor(9, 1);
    lcd.write(4);
  
  }delay (20);
  
}

void loop()
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }
  /*
    Serial.println("JSON Object Recieved");
    Serial.print("Recieved Distance: ");
    distance = data["Distance: "];
    Firebase.setFloat ("Recieved Distance",distance);
    Serial.println(distance);
  */
  Serial.println("JSON Object Recieved");
  
  Serial.print("Recieved PH Value: ");
  phValue = data["PH Value: "];
   phValue = (roundf(phValue*100))/100;
  Firebase.setFloat ("Recieved PH Value", phValue);
  Serial.println(phValue);
  lcd.setCursor(2, 0);
  lcd.print(phValue);
    lcd.setCursor(0, 0);
    lcd.write(0);
     Motor();






     

  Serial.print("Recieved Temperature: ");
  Temperature_Val = data["Temperature: "];
  Firebase.setFloat ("Recieved Temperature", Temperature_Val);
  Serial.println(Temperature_Val);
  lcd.setCursor(11, 0);
  lcd.print(Temperature_Val);
    lcd.setCursor(9, 0);
    lcd.write(1);
    lcd.setCursor(15, 0);
    lcd.write(2);
    
  Serial.print("Recieved Air Quality: ");
  String quality = data["Air Quality: "];
  Firebase.setString ("Recieved Air Quality", quality);
  Serial.println(quality);
  Global_quality = quality;
  lcd.setCursor(2, 1);
  lcd.print(Global_quality);
    lcd.setCursor(0, 1);
    lcd.write(3);

  
  Serial.print("Water Level: ");
  Water_Level = data["Water Level: "];
  Firebase.setFloat ("Recieved Water Level", Water_Level);
  Serial.println(Water_Level);
  lcd.setCursor(11, 1);
  lcd.print(Water_Level);
    lcd.setCursor(9, 1);
    lcd.write(4);



   //  Display();

 
    Serial.println("Reset..");
    ESP.restart();
    delay(100);
}


void Motor()
{
    if (phValue < 6.5 || phValue > 7.5) 
    {
      digitalWrite(D3, HIGH);
      Serial.println("Motor ON");
    }
    if (phValue >= 6.5 && phValue<=7.5) 
    {
      digitalWrite(D3, LOW);
      Serial.println("Motor OFF");
    }
    delay(50);
}
