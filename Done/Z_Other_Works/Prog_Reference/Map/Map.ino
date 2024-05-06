int Throttle_In = A0;
int Throttle_Out = A1;
int Throttle_Out_Val = 0;
int Throttle_In_Val = 0;

void setup() 
{
  pinMode(Throttle_In, INPUT);
  pinMode(Throttle_Out, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  Throttle_In_Val = analogRead(Throttle_In);
  Serial.print("Throttle_In_Val --> ");  Serial.print(Throttle_In_Val);
  Throttle_Out_Val = map(Throttle_In_Val,0,1023,0,500);
  Serial.print("    Throttle_Out_Val --> ");  Serial.println(Throttle_Out_Val);
  analogWrite(Throttle_Out, Throttle_Out_Val); 
}
