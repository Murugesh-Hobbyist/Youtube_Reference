#include  <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "inject-38929-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "NtERcHXnmeoq5EwJK9ht3rSrW1pOE9bW6wuYlYzT"
#define WIFI_SSID "Smart"
#define WIFI_PASSWORD "12344321"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);
int sensorValue;

void setup()
{  
  Serial.begin(9600);
  nodemcu.begin(9600);
  while (!Serial) continue;
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
  }
  
  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  //Firebase.begin(FIREBASE_HOST);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() 
{
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");
  Serial.print("x");
  float x = data[""];
  Serial.println(x);
  
  Serial.print("Recieved Analog1:  ");
  int sensorValue1 = data["analog value1"];
  Serial.println(sensorValue1);    Firebase.setInt ("analog1",sensorValue1);
  
  Serial.print("Recieved Analog:  ");
  int sensorValue = data["analog value"];
  Serial.println(sensorValue);    Firebase.setInt ("analog",sensorValue);

  Serial.println("-----------------------------------------");
}
