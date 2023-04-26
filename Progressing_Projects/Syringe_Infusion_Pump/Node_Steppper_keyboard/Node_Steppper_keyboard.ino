#include <Arduino.h>
#include "A4988.h"

int Step = 12; //GPIO14---D5 of Nodemcu--Step of stepper motor driver
int Dire  = 13; //GPIO2---D4 of Nodemcu--Direction of stepper motor driver

const int spr = 200; //Steps per revolution
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
  if(Serial.available()){
  Command = Serial.readStringUntil('\n');
  }

if (Command == "500" )
{
Serial.println("500 steps clock"); stepper.move(500);
};
if (Command=="-500")
{Serial.println("500 steps anti-clock");stepper.move(-500);};
Command = "";
}
