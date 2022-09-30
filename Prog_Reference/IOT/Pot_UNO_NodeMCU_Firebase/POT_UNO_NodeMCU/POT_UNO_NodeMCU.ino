#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);
int sensorValue ;
int sensorValue1 ;

void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600);
  delay(1000);

  Serial.println("Program started");
}

void loop() 
{
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  dht11_func();
  data["analog value"] = sensorValue;
  data.printTo(nodemcu);
  data["analog value1"] = sensorValue1;
  data.printTo(nodemcu);
  jsonBuffer.clear();
  delay(2000);
}

void dht11_func() 
{
  sensorValue = analogRead(A0);
  Serial.print("analog value");
  Serial.println(sensorValue);
  sensorValue1 = analogRead(A1);
  Serial.print("analog value1");
  Serial.println(sensorValue1);

}
