#include "FlySkyIBus.h"

void setup() 
{
  Serial.begin(115200);
  IBus.begin(Serial);

}

void loop() 
{
  IBus.loop();
  Serial.print(IBus.readChannel(0), HEX);
  Serial.print("\t");
  Serial.print(IBus.readChannel(1), HEX);
  Serial.print("\t");
  Serial.print(IBus.readChannel(2), HEX);
  Serial.print("\t");
  Serial.print(IBus.readChannel(3), HEX);
  Serial.print("\t");
  Serial.print(IBus.readChannel(4), HEX);
  Serial.print("\t");
  Serial.print(IBus.readChannel(5), HEX);
  Serial.print("\t");
  Serial.print(IBus.readChannel(6), HEX);
  Serial.print("\t");
  Serial.print(IBus.readChannel(7), HEX);
  Serial.print("\t");
  Serial.print(IBus.readChannel(8), HEX);
  Serial.print("\t");
  Serial.println(IBus.readChannel(9), HEX);
}
