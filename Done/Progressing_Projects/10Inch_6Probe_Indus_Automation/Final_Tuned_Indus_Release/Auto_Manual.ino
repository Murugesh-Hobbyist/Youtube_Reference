
//-------------------------------------------------------------Auto_Manual_Controls-----------------------------------------------------------------------------

void Auto_Manual() {

  //-------------Full execution----------------

  int sensorValue1 = digitalRead(Piston_Reed1);
  int sensorValue2 = digitalRead(Piston_Reed2);

  //           /*
  Serial.print("  Piston_Reed1 -> ");
  Serial.print(sensorValue1);
  Serial.print("  Piston_Reed2 -> ");
  Serial.println(sensorValue2);
  //         */

  if ((digitalRead(B1) == LOW) && (digitalRead(B2) == LOW) && (digitalRead(Piston_Reed1) == HIGH) && (digitalRead(Piston_Reed2) == LOW) && (digitalRead(Emergency_Button) == LOW)) {

    Serial.println("loop head -> ");

    //-----------------------------Piston-Home-----------------------------

    while ((digitalRead(Piston_Reed1) == HIGH) && (digitalRead(Piston_Reed2) == LOW) && (Piston_Home == true) && (digitalRead(Emergency_Button) == LOW)) {

      digitalWrite(Piston_Soli1, LOW);
      digitalWrite(Piston_Soli2, HIGH);
      Piston_Up2Down = true;
      Piston_Down2Up = false;
      Serial.println("up to down -> ");
    }

    while ((digitalRead(Piston_Reed1) == LOW) && (digitalRead(Piston_Reed2) == LOW) && (Piston_Up2Down == true) && (digitalRead(Emergency_Button) == LOW)) {
      Fetch_Text();
      Read_ADC();
      Piston_Bottom = true;
    }
  }

  //--------------------------------------Check-Piston-Bottom-and-Lock-----------------------------

  if ((digitalRead(Piston_Reed1) == LOW) && (digitalRead(Piston_Reed2) == HIGH) && (Piston_Bottom == true) && (digitalRead(Emergency_Button) == LOW)) {

    digitalWrite(Piston_Soli1, HIGH);
    digitalWrite(Piston_Soli2, HIGH);
    Piston_Bottom = true;
    Piston_Up2Down = false;
    Piston_Down2Up = false;

    for (int i = 0; i <= 10; i++) {
      Fetch_Text();
      Read_ADC();
      Serial.println(i);
    }

    Serial.println("Job Checked");
    //----------------------------------------------Auto-Mode---------------------------------------------

    while ((Piston_Bottom == true) && (Modex == "Auto") && (digitalRead(Emergency_Button) == LOW)) {

      Serial.println("llllllllllllllllllllllllllllllllllll");
      if (Stat_Str1 == "PASS" && Stat_Str2 == "PASS" && Stat_Str3 == "PASS" && Stat_Str4 == "PASS" && Stat_Str5 == "PASS" && Stat_Str6 == "PASS" && (digitalRead(Emergency_Button) == LOW)) {

    //OK_Count_Str.toCharArray(Ok_Count_Char, OK_Count_Str.length() + 1);
        /*
        OK_Count_Str = String(OK_Count);
    OK_Count_Str.toCharArray(Ok_Count_Char, OK_Count_Str.length() + 1);

 // dwinSerial.write(Ok_Count_Clr, sizeof(Ok_Count_Clr));
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(strlen(Ok_Count_Char) + 3);
  dwinSerial.write(0x82);
  dwinSerial.write(0x74);
  dwinSerial.write(0x26);
  for (int i = 0; i < strlen(Ok_Count_Char); i++) {
    char c = Ok_Count_Char[i];
    dwinSerial.write(c);
  }
  */
  
        OK_Count = OK_Count+1;
        sendFloatShiftCount(OK_Count);
        OK_Count_Str = String(OK_Count);
        

  delay(50);
        SD_Save();
delay(50);

        Serial.println("All Pass -> ");
        digitalWrite(Punch_Soli1, HIGH);
        digitalWrite(Punch_Soli2, LOW);
        delay(200);

        digitalWrite(Punch_Soli1, LOW);
        digitalWrite(Punch_Soli2, HIGH);
        delay(200);
        digitalWrite(Punch_Soli1, HIGH);
        digitalWrite(Punch_Soli2, HIGH);


        digitalWrite(Piston_Soli1, HIGH);
        digitalWrite(Piston_Soli2, LOW);
        Serial.println("passed down to up -> ");
        Piston_Home = false;
        Piston_Bottom = false;
        Piston_Up2Down = false;
        Piston_Down2Up = true;
        delay(1000);
      }

      else {
        Serial.println("Failed -> ");
        delay(2000);

        digitalWrite(Piston_Soli1, HIGH);
        digitalWrite(Piston_Soli2, LOW);
        Serial.println(" failed down to up -> ");

        Piston_Up2Down = false;
        Piston_Down2Up = true;
        Piston_Home = false;
        Piston_Bottom = false;
      }
    }

    //----------------------------------------------Manual-Mode---------------------------------

    while ((Piston_Bottom == true) && (Modex == "Manual") && (digitalRead(Emergency_Button) == LOW)) {

      Serial.println("oooooooooooooooooooooooooooooooooooo");
      Fetch_Text();
      Read_ADC();

      digitalRead(Reset_Button);
      Serial.println(digitalRead(Reset_Button));

      if (digitalRead(Reset_Button) == LOW && (digitalRead(Emergency_Button) == LOW)) {

        digitalWrite(Piston_Soli1, HIGH);
        digitalWrite(Piston_Soli2, LOW);
        Serial.println(" Manual down to up -> ");

        Piston_Up2Down = false;
        Piston_Down2Up = true;
        Piston_Home = false;
        Piston_Bottom = false;
      }
    }
  }

  //-----------------------------Punch-Home-----------------------------

  if ((digitalRead(Piston_Reed1) == HIGH) && (digitalRead(Piston_Reed2) == LOW) && (Piston_Down2Up == true) && (digitalRead(Emergency_Button) == LOW)) {
    Serial.println("pggggggggggggggggggggggggggggg-> ");
    digitalWrite(Piston_Soli1, HIGH);
    digitalWrite(Piston_Soli2, HIGH);
    Piston_Bottom = false;
    Piston_Home = true;
    Piston_Up2Down = false;
    Piston_Down2Up = false;
    Serial.println("resetting-> ");
  }
  if ((digitalRead(Emergency_Button) == HIGH)) {
    Emergency_Lock = true;
    digitalWrite(Piston_Soli1, HIGH);
    digitalWrite(Piston_Soli2, HIGH);
    digitalWrite(Piston_Soli1, HIGH);
    digitalWrite(Piston_Soli2, LOW);
    Serial.println(" Emergency down to up -> ");

    Piston_Up2Down = false;
    Piston_Down2Up = true;
    Piston_Home = false;
    Piston_Bottom = false;

    while (Emergency_Lock == true) {
      if ((digitalRead(Piston_Reed1) == HIGH) && (digitalRead(Piston_Reed2) == LOW) && (Piston_Down2Up == true)) {
        Serial.println("pggggggggggggggggggggggggggggg-> ");
        digitalWrite(Piston_Soli1, HIGH);
        digitalWrite(Piston_Soli2, HIGH);
        Piston_Bottom = false;
        Piston_Home = true;
        Piston_Up2Down = false;
        Piston_Down2Up = false;
        Emergency_Lock = false;
        Serial.println("resetting-> ");
      }
    }
  }
}
