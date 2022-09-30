int Pot = A0;
int Relay = D5;
int Pot_Val = 0;
int Relay_Delay = 0;
int Off_Delay = 5000* Relay_Delay;

void setup() 
{
  pinMode(Pot, INPUT);
  pinMode(Relay, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  Pot_Val = analogRead(Pot);
  Relay_Delay = map(Pot_Val,0,500,0,500);
//  Serial.print("Pot_Val  -----> ");  Serial.println(Pot_Val);
  Serial.print("Relay_Delay --> ");  Serial.println(Relay_Delay);
  Serial.println("-----------------------------------------------------------------"); 
  digitalWrite(Relay, HIGH); 
  delay(3000);                     
  digitalWrite(Relay, LOW); 
  delay(Relay_Delay);   
}              





  
