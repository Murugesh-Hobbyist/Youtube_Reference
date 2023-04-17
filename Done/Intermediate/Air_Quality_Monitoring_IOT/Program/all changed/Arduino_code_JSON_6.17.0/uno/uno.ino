#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial nodemcu(5, 6);

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4  // pin changable to any digital
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature Temperature_Sensor(&oneWire);
int Temperature_Val;

const int trigPin = 9; // analog
const int echoPin = 10; // analog
long duration;
int distance;

#define SensorPin A0
unsigned long int avgValue;
float b;
int buf[10],temp;
float phValue;
 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeMonoOblique9pt7b.h>
#define AQ_Sen A1
int GasLevel = 0;
String quality ="";






void setup()
{

  Serial.println("Program started");
  {  
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   Serial.begin(9600); // Starts the serial communication
  }
    {
     Temperature_Sensor.begin();
    }
      {
       pinMode(A0,INPUT); 
       Serial.println("Ready"); 
      }

        {
         pinMode(AQ_Sensor,INPUT);
        }
  Serial.begin(9600);
  nodemcu.begin(9600);
  delay(1000);
}

void loop() 
{

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  US_Sensor();
  Temp_Sensor();
  PH_Sensor();
  AQ_Sensor();
  //------------------------------Assign collected data to JSON Object
  data["Distance: "] = distance;
  data["Temperature: "] = Temperature_Val;
  data["Air Quality: "] = quality;
  data["PH Value: "] = phValue;
  //------------------------------Send data to NodeMCU

  data.printTo(nodemcu);
  jsonBuffer.clear();
  delay(500);
}

void US_Sensor()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(50);
}


void Temp_Sensor()
{ 
  Temperature_Sensor.requestTemperatures();
  Temperature_Val = Temperature_Sensor.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(Temperature_Val);
  Serial.println(" C");
  delay(50);
}

void AQ_Sensor()
{
  GasLevel = analogRead(AQ_Sensor);
  if(GasLevel<=820){quality = "  GOOD!";}
  else if (GasLevel >820 && GasLevel<=880){quality = "  Poor!";}
  else if (GasLevel >880 && GasLevel<=920){quality = "Very bad!";}
  else{quality = " Toxic";}
 // Serial.print("GasLevel");
 // Serial.println(GasLevel);
  Serial.print("Air Quality: ");
  Serial.println(quality);
  delay(50);
}



void PH_Sensor()
{
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  { for(int j=i+1;j<10;j++)
    { if(buf[i]>buf[j])
      { temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++) //take the average value of 6 center sample
    avgValue+=buf[i];
  phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  Serial.print("PH Value: ");  
  Serial.println(phValue,2); 
  delay(50);
}
