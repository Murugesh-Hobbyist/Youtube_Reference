#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);

int distance;
int Temperature_Val;
float phValue;
//String quality =""; //ambiguous overload for 'operator='

void setup() 
{
  Serial.begin(9600);
  nodemcu.begin(9600);
  while (!Serial) continue;
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
  
  Serial.println("JSON Object Recieved");
  Serial.print("Recieved Distance: ");
   distance = data["Distance: "];
  Serial.println(distance);
  
  Serial.print("Recieved Temperature: ");
  Temperature_Val = data["Temperature: "];
  Serial.println(Temperature_Val);

  Serial.print("Recieved Air Quality: ");
  String quality = data["Air Quality: "];
  Serial.println(quality);

  Serial.print("Recieved PH Value: ");
  phValue = data["PH Value: "];
  Serial.println(phValue);
  
  Serial.println("-----------------------------------------");
}
