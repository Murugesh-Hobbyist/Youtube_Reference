//ThatsEngineering
//Sending Data from Arduino to NodeMCU Via Serial Communication
//Arduino code

//DHT11 Lib
#include <DHT.h>

//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4  // pin changable to any digital
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature Temperature_Sensor(&oneWire);
int Temperature_Val;



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

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  dht11_func();   data["humidity "] = hum;
  dht11_func1();  data["temperature "] = temp;
  dht11_func2();  data["humi "] = temp1;
  dht11_func3();  data["tempe "] = temp2;

  data.printTo(nodemcu);
  jsonBuffer.clear();

  delay(500);
}

void dht11_func() {

  Temperature_Sensor.requestTemperatures();
  Temperature_Val = Temperature_Sensor.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(Temperature_Val);
    hum =  Temperature_Val;
  Serial.println(" C"); 
  delay(500);
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
