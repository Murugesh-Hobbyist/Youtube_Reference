const int buzz = 5 ;       //Connect button to D1

void setup() 
{
pinMode(buzz, OUTPUT);            //Configure LED as output
}

void loop() 
{           //Read the button state
    digitalWrite(buzz, HIGH);  //Turn ON LED
    delay(1000);
    digitalWrite(buzz, LOW);  //Turn LOW LED
    delay(1000);
}
