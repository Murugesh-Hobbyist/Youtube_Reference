
String command;
void setup()
{
 Serial.begin(9600);
 pinMode(8, OUTPUT);
 //pinMode(7, OUTPUT);
}

void loop() 
{
  if (Serial.available())
  {
   delay(10);
   command = Serial.readString(); 
  
   if (command.length() > 0) {Serial.println(command);
     if (command == "Light_On")  {digitalWrite (8, HIGH);}
     if (command == "Light_Off") {digitalWrite (8, LOW);}
 //  if (command == "Fan_On")    {digitalWrite (7, HIGH);}
 //  if (command == "Fan_Off")   {digitalWrite (7, LOW);}
     command="";}
  }
}
