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





float temp;
float hum;
float temp1;
float temp2;




void setup() {
  Serial.begin(9600);

  nodemcu.begin(9600);
  delay(1000);

  Serial.println("Program started");
}

void loop() {

  StaticJsonDocument<1000> doc;

  //Obtain Temp and Hum data
  dht11_func();   doc["humidity "] = hum;
  dht11_func1();  doc["temperature "] = temp;
  dht11_func2();  doc["humi "] = temp1;
  dht11_func3();  doc["tempe "] = temp2;


  //Assign collected data to JSON Object
  //Send data to NodeMCU
  serializeJson(doc, nodemcu);
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
