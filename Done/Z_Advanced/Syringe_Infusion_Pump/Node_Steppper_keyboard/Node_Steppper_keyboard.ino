#include <Arduino.h>
#include "A4988.h"

//int Step = 12; //GPIO14---D5 of Nodemcu--Step of stepper motor driver
//int Dire  = 14; //GPIO2---D4 of Nodemcu--Direction of stepper motor driver
int Step = 12 ; //GPIO14---D5 of esp32--Step of stepper motor driver
int Dire = 14 ; //GPIO2---D4 of esp32--Direction of stepper motor driver

//int Step = 5 ; //GPIO14---D5 of uno--Step of stepper motor driver
//int Dire = 6 ; //GPIO2---D4 of uno--Direction of stepper motor driver

const int spr = 6400; //Steps per revolution
int RPM = 100; //Motor Speed in revolutions per minute
int Microsteps = 1; //Stepsize (1 for full steps, 2 for half steps, 4 for quarter steps, etc)
String Command;

A4988 stepper(spr, Dire, Step);

void setup() 
{
  Serial.begin(9600);
  pinMode(Step, OUTPUT); //Step pin as output
  pinMode(Dire,  OUTPUT); //Direcction pin as output
  digitalWrite(Step, LOW); // Currently no stepper motor movement
  digitalWrite(Dire, LOW);
  stepper.begin(RPM, Microsteps);
}

void loop() 
{
  if(Serial.available())
  { Command = Serial.readStringUntil('\n');  }

    Serial.print("steps moves -> "); 
    Serial.println(Command); 
       int  step = Command.toInt();
    stepper.move(step);
    Command = "0";
}
