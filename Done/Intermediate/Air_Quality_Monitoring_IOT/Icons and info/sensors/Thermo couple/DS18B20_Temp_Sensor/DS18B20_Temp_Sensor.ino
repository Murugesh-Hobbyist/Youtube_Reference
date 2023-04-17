#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8  // pin changable to any digital
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature Temperature_Sensor(&oneWire);
int Temperature_Val;

void setup(void) // same as void setup()
{
  Temperature_Sensor.begin();
  Serial.begin(9600);
}

void loop(void)
{ 
  Temperature_Sensor.requestTemperatures();
  Temperature_Val = Temperature_Sensor.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(Temperature_Val);
  Serial.println(" C");
  delay(50);
}
