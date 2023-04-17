//Arduino side code
//DHT11 Lib
#include <DHT.h>

//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);

//Initialisation of DHT11 Sensor
#define DHTPIN 4
DHT dht(DHTPIN, DHT11);
float temp;
float hum;
float temp1;
float temp2;


void setup() {
  Serial.begin(9600);

  dht.begin();
  nodemcu.begin(9600);
  delay(1000);

  Serial.println("Program started");
}

void loop() {

  StaticJsonDocument<1000> doc;

  //Obtain Temp and Hum data
  dht11_func();   doc["humidity "] = hum;
  dht11_func1();
  doc["temperature "] = temp;
  dht11_func2();  doc["humi "] = temp1;
  dht11_func3();  doc["tempe "] = temp2;


  //Assign collected data to JSON Object
 



  //Send data to NodeMCU
  serializeJson(doc, nodemcu);
  delay(500);
}

void dht11_func() {
  hum =  analogRead(A0);
  Serial.print("Humidity: ");
  Serial.println(hum);
}
void dht11_func1() {
  temp = digitalRead(5);
  Serial.print("Temperature: ");
  Serial.println(temp);
}
void dht11_func2() {  
  temp1 = digitalRead(3);
  Serial.print("Temp: ");
  Serial.println(temp1);
}
void dht11_func3() {
  temp2 = digitalRead(6);
  Serial.print("Temper: ");
  Serial.println(temp2);
}
