int input1  = 5;
int input2  = 6;  

void setup()
{
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);
}


void loop()
{
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    delay(2000); 
    
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    delay(2000);
//    
  //  digitalWrite(input1, LOW);
    //digitalWrite(input2, HIGH);
    //delay(2000);
   
  //  digitalWrite(input1, HIGH);
    //digitalWrite(input2, HIGH);
    //delay(2000);   
}
