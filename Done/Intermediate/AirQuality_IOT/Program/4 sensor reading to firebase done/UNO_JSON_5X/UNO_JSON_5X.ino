#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial nodemcu(5, 6);//rx/tx

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8  // pin changable to any digital
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature Temperature_Sensor(&oneWire);
int Temperature_Val;

const int trigPin = 9; // analog
const int echoPin = 10; // analog
long duration;
float distance;
int Water_Level;
float Water_Max = 20;

#define SensorPin A1
unsigned long int avgValue;
float b;
int buf[10],temp;
float phValue;

int GasLevel_Good_Min = 0;
int GasLevel_Good_Max = 750;

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeMonoOblique9pt7b.h>
#define AQ_Sen A0
int GasLevel = 0;
String quality ="";


void setup()
{

  Serial.println("Program started");
  {  
   pinMode(8, INPUT);pinMode(7, OUTPUT);
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   Serial.begin(9600);
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
  nodemcu.begin(9600);
  delay(1000);
}

void loop() 
{

  {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  
  US_Sensor();
  Temp_Sensor();
  PH_Sensor();
  AQ_Sensor();
  //------------------------------Assign collected data to JSON Object
  //data["Distance: "] = distance;
  data["Water Level: "] = Water_Level;
  data["Temperature: "] = Temperature_Val;
  data["Air Quality: "] = quality;
  data["PH Value: "] = phValue;
  //------------------------------Send data to NodeMCU
  data.printTo(nodemcu);
  jsonBuffer.clear();
  delay(500);
  
  {
    if (phValue < 6.5 || phValue > 7.5) 
    {
      digitalWrite(7, HIGH);
      Serial.println("Motor ON");
    }
    if (phValue >= 6.5 && phValue<=7.5) 
    {
      digitalWrite(7, LOW);
      Serial.println("Motor OFF");
    }
    delay(50);
}
  
  
  }
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
  {
    if (distance >= 5 && distance <=20)
    { Water_Level = ((Water_Max - distance)/.15);
     Serial.print("Water Level: ");
     Serial.println(Water_Level);
    //Firebase.setFloat ("Water Level",Water_Level);
    }
      
    if (distance < 5)
    { Water_Level = 100;
     Serial.print("Water Level: ");
     Serial.println(Water_Level);
   //Firebase.setFloat ("Water Level",Water_Level);};
    }
    if (distance > 20)
    { Water_Level = 0;
     Serial.print("Water Level: ");
     Serial.println(Water_Level);
   //Firebase.setFloat ("Water Level",Water_Level);};
    }
  }
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
  if(GasLevel >= GasLevel_Good_Min || GasLevel <= GasLevel_Good_Max){quality = "GOOD!";}
  if (GasLevel < GasLevel_Good_Min ||  GasLevel > GasLevel_Good_Max){quality = "Poor!";}
 //if (GasLevel >880 && GasLevel<=920){quality = "Very_bad!";}
 // else{quality = "Toxic!";}
 Serial.print("GasLevel");
 Serial.println(GasLevel);
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
 // phValue=3.5*phValue;                      //convert the millivolt into pH value
  phValue=1+(3.5*phValue);  
  Serial.print("PH Value: ");  
 // phValue = (roundf(phValue*1000))/10;
  Serial.println(phValue); 
  
  //float phdeci2 = (roundf(phValue*10))/10;
 // Serial.println(phdeci2); 
  delay(50);


  
}
