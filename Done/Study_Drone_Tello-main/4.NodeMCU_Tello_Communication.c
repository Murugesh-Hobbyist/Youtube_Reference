#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid      = "TELLO-5EA8AA";
const char* password  = "";

IPAddress TelloIp(192, 168, 10, 1);
const int TelloPort = 8889;      // local port to listen on

WiFiUDP Udp;
const int localUdpPort = 9002;  // local port to listen on
const char  cmdCommandPacekt[] = "command"; // command
const char  cmdTakeoffPacekt[] = "takeoff"; // takeoff
const char  cmdLandPacekt[] = "land";       // land

void setup()
{
  Serial.begin(115200);
  
//----------------------Connecting to Tello------------------

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  { 
    delay(500);
    Serial.print(".");
  } 
  Serial.println(" connected");
  
//----------------------Enter SDK Mode-----------------------

  Udp.beginPacket(TelloIp, TelloPort);
  Udp.write(cmdCommandPacekt);
  Udp.endPacket();  
  delay(100);
  Udp.begin(localUdpPort);
  Serial.printf ("Now listening at IP %s, UDP port %d\n", 
                  WiFi.localIP().toString().c_str(), localUdpPort);
//-----------------------------------------------------------
}

void loop()
{
      {
          Serial.println("TELLO_Takeoff");
          Udp.beginPacket(TelloIp, TelloPort);
          Udp.write(cmdTakeoffPacekt);
          Udp.endPacket();
      }delay(8000);
      {
         Serial.println("TELLO_Landing");
         Udp.beginPacket(TelloIp, TelloPort);
         Udp.write(cmdLandPacekt);
         Udp.endPacket();
      }delay(500000);
}