#include <Servo.h> 
Servo servo_a;  //Gripper
Servo servo_b;  //Shoulder
Servo servo_c;  //Elbow
Servo servo_d;  //Base
int pot1;   //Gripper
int pot2;   //Shoulder
int pot3;   //Elbow
int pot4;   //Base
int servo1[10];
int servo2[10];
int servo3[10];
int servo4[10];
int angle1;  //Gripper
int angle2;  //Shoulder
int angle3;  //Elbow
int angle4;  //Base
int savebutton = 8;
int playbutton=12;
int resetbutton = 13;
int switchpoint =0;
int led=7;
boolean ledon=false;
boolean lastbutton=LOW;
boolean currentbutton=LOW;
int cycle = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(savebutton, INPUT);
  pinMode(playbutton, INPUT);
  pinMode(resetbutton, INPUT);
  pinMode(7,OUTPUT);
  
  servo_a.attach(9);//Base
  servo_b.attach(10);//Shoulder
  servo_c.attach(11);//Elbow
  servo_d.attach(5);//Gripper
 /* 
  Serial.println("Hi, I am MIMIC!");  
  delay(2000);
  Serial.println("You can Control, Record & Play back the motion you needed."); 
  delay(2000);
  Serial.println("");
  Serial.println("CAUTION - Please follow the instructions Below..."); 
  delay(3000);
  Serial.println("");
  Serial.println("Press Button-A to Record currect position of Ditto. (Must Record 10 Positions to Playback)"); 
  delay(5000);
  Serial.println("Press Button-B to Playback the recorded motion."); 
  delay(3000);
  Serial.println("Press & Hold Button-C to Reset the motion. (Must complete a play cycle)"); 
  delay(5000);
  Serial.println("Press Button-D for Emergency stop and Program reboot."); 
  delay(3000);
  Serial.println("");
  Serial.print("Connecting."); 
  delay(400);  
  Serial.print("."); 
  delay(400);  
  Serial.print("."); 
  delay(400);  
  Serial.print("."); 
  delay(400);  
  Serial.print("."); 
  delay(400);  
  Serial.println("."); 
  delay(400);
  Serial.println("Live Control Is Activated."); 
  delay(2000);
  */
}

boolean debounce (boolean last)
{
  boolean current = digitalRead(playbutton);
  if(last!=current)
  {
    delay(5);
    current= digitalRead(playbutton);
  }
  return current;
}
 
void(* resetFunc) (void) = 0;

void  loop()
{ 
  currentbutton=debounce(lastbutton);
  if(lastbutton==LOW&&currentbutton==HIGH)
  { 
    ledon=!ledon;
  }
  lastbutton=currentbutton;
  digitalWrite(led,ledon);


//Base
pot1=analogRead(A1);
angle1=map(pot1,0,1023,0,180);
servo_a.write(angle1);

//Shoulder
pot2=analogRead(A2);
angle2=map(pot2,0,1023,0,180);
servo_b.write(angle2);

//Elbow
pot3=analogRead(A3);
angle3=map(pot3,0,1023,0,180);
servo_c.write(angle3);

//Gripper
pot4=analogRead(A4);
angle4=map(pot4,0,1023,180,0);
servo_d.write(angle4);
       Serial.println(angle1);
       Serial.println(angle2);
       Serial.println(angle3);
       Serial.println(angle4);


  
if(digitalRead(savebutton) == HIGH) 
  {
  switchpoint++;  
  switch(switchpoint)
    {
      case 1:
       servo1[0] = angle1;
       servo2[0] = angle2;
       servo3[0] = angle3;
       servo4[0] = angle4;
       Serial.println("");
       Serial.println("Position 1 out of 10 is Saved");
       delay(1000);
       break;
       
      case 2:
       servo1[1] = angle1;
       servo2[1] = angle2;
       servo3[1] = angle3;
       servo4[1] = angle4;
       Serial.println("Position 2 out of 10 is Saved");
       delay(1000);
       break;
       
      case 3:
       servo1[2] = angle1;
       servo2[2] = angle2;
       servo3[2] = angle3;
       servo4[2] = angle4;
       Serial.println("Position 3 out of 10 is Saved");
       delay(1000);
       break;

      case 4:
       servo1[3] = angle1;
       servo2[3] = angle2;
       servo3[3] = angle3;
       servo4[3] = angle4;
       Serial.println("Position 4 out of 10 is Saved");
       delay(1000);
       break;
       
       case 5:
       servo1[4] = angle1;
       servo2[4] = angle2;
       servo3[4] = angle3;
       servo4[4] = angle4;
       Serial.println("Position 5 out of 10 is Saved");
       delay(1000);
       break;

       case 6:
       servo1[5] = angle1;
       servo2[5] = angle2;
       servo3[5] = angle3;
       servo4[5] = angle4;
       Serial.println("Position 6 out of 10 is Saved");
       delay(1000);
       break;

       case 7:
       servo1[6] = angle1;
       servo2[6] = angle2;
       servo3[6] = angle3;
       servo4[6] = angle4;
       Serial.println("Position 7 out of 10 is Saved");
       delay(1000);
       break;

       case 8:
       servo1[7] = angle1;
       servo2[7] = angle2;
       servo3[7] = angle3;
       servo4[7] = angle4;
       Serial.println("Position 8 out of 10 is Saved");
       delay(1000);
       break;

       case 9:
       servo1[8] = angle1;
       servo2[8] = angle2;
       servo3[8] = angle3;
       servo4[8] = angle4;
       Serial.println("Position 9 out of 10 is Saved");
       delay(1000);
       break;

       case 10:
       servo1[9] = angle1;
       servo2[9] = angle2;
       servo3[9] = angle3;
       servo4[9] = angle4;

       Serial.println("Position 10 out of 10 is Saved");
       Serial.println("");
       Serial.print("Preparing."); 
       delay(400);  
       Serial.print("."); 
       delay(400);  
       Serial.print("."); 
       delay(400); 
       Serial.print("."); 
       delay(400);
       Serial.println("."); 
       delay(400);
       Serial.println("Ready to play.");
       delay(1000);
       break;              
    }
 }


if(digitalRead(led) == HIGH) 
{ 
  Serial.println(""); 
  Serial.print("Play Cycle-");  
  cycle = cycle+1 ; 
  Serial.println(cycle);
  
  for(int i = 0; i < 10; i++)
     {
      Serial.print("Possition ");
      Serial.print(i+1);
      Serial.print(" ---> ");
      {
       servo_a.write(servo1[i]);
       Serial.print("Base->");
       Serial.print(servo1[i]);
       Serial.print("   ");

       servo_b.write(servo2[i]);
       Serial.print("Shoulder->");
       Serial.print(servo2[i]);
       Serial.print("   ");

       servo_c.write(servo3[i]);
       Serial.print("Elbow->");
       Serial.print(servo3[i]);
       Serial.print("   ");
       
       servo_d.write(servo4[i]);
       Serial.print("Gripper->");
       Serial.print(servo4[i]);
       Serial.print("   ");
      }delay(1000);
     }
}

if(digitalRead(resetbutton) == HIGH)
 {
  delay(100);
  Serial.println("");
  Serial.print("Processing...");  
  Serial.print("."); 
  delay(500);  
  Serial.print("."); 
  delay(500);  
  Serial.println("."); 
  delay(500);
  Serial.println("reset complete");
  Serial.println("");
  delay(1000);
  resetFunc();
 }
}
