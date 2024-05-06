
//-------------------------------------------------------------Toleranc_Password_Entry-----------------------------------------------------------------------------

void Tolerance_Pass()
{
  Fetch_Text();
  if (receivedFloat == 63) {
    Pasword_Lock = true;
    while (Pasword_Lock == true) {

      if (dwinSerial.available() > 0) {
        Collect = dwinSerial.readString();
        receivedFloat = atof(Collect.c_str());
      }
      if ((receivedFloat == 62) || (receivedFloat == 60)) {
        Pasword_Lock = false;
      }
      if (receivedFloat == 81) {
        Pass_Entry += 1;
        if (Pass_Entry.length() == 1) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass1s, sizeof(Pass1s));
        }
        if (Pass_Entry.length() == 2) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass2s, sizeof(Pass2s));
        }
        if (Pass_Entry.length() == 3) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass3s, sizeof(Pass3s));
        }
        if (Pass_Entry.length() == 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass4s, sizeof(Pass4s));
        }
        if (Pass_Entry.length() > 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
        }
        receivedFloat = 99;
        Serial.println(Pass_Entry);
      }

      if (receivedFloat == 82) {
        Pass_Entry += 2;
        if (Pass_Entry.length() == 1) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass1s, sizeof(Pass1s));
        }
        if (Pass_Entry.length() == 2) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass2s, sizeof(Pass2s));
        }
        if (Pass_Entry.length() == 3) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass3s, sizeof(Pass3s));
        }
        if (Pass_Entry.length() == 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass4s, sizeof(Pass4s));
        }
        if (Pass_Entry.length() > 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
        }
        receivedFloat = 99;
        Serial.println(Pass_Entry);
      }

      if (receivedFloat == 83) {
        Pass_Entry += 3;
        if (Pass_Entry.length() == 1) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass1s, sizeof(Pass1s));
        }
        if (Pass_Entry.length() == 2) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass2s, sizeof(Pass2s));
        }
        if (Pass_Entry.length() == 3) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass3s, sizeof(Pass3s));
        }
        if (Pass_Entry.length() == 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass4s, sizeof(Pass4s));
        }
        if (Pass_Entry.length() > 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
        }
        receivedFloat = 99;
        Serial.println(Pass_Entry);
      }

      if (receivedFloat == 84) {
        Pass_Entry += 4;
        if (Pass_Entry.length() == 1) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass1s, sizeof(Pass1s));
        }
        if (Pass_Entry.length() == 2) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass2s, sizeof(Pass2s));
        }
        if (Pass_Entry.length() == 3) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass3s, sizeof(Pass3s));
        }
        if (Pass_Entry.length() == 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass4s, sizeof(Pass4s));
        }
        if (Pass_Entry.length() > 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
        }
        receivedFloat = 99;
        Serial.println(Pass_Entry);
      }

      if (receivedFloat == 85) {
        Pass_Entry += 5;
        if (Pass_Entry.length() == 1) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass1s, sizeof(Pass1s));
        }
        if (Pass_Entry.length() == 2) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass2s, sizeof(Pass2s));
        }
        if (Pass_Entry.length() == 3) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass3s, sizeof(Pass3s));
        }
        if (Pass_Entry.length() == 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass4s, sizeof(Pass4s));
        }
        if (Pass_Entry.length() > 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
        }
        receivedFloat = 99;
        Serial.println(Pass_Entry);
      }

      if (receivedFloat == 86) {
        Pass_Entry += 6;
        if (Pass_Entry.length() == 1) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass1s, sizeof(Pass1s));
        }
        if (Pass_Entry.length() == 2) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass2s, sizeof(Pass2s));
        }
        if (Pass_Entry.length() == 3) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass3s, sizeof(Pass3s));
        }
        if (Pass_Entry.length() == 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass4s, sizeof(Pass4s));
        }
        if (Pass_Entry.length() > 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
        }
        receivedFloat = 99;
        Serial.println(Pass_Entry);
      }

      if (receivedFloat == 87) {
        Pass_Entry += 7;
        if (Pass_Entry.length() == 1) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass1s, sizeof(Pass1s));
        }
        if (Pass_Entry.length() == 2) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass2s, sizeof(Pass2s));
        }
        if (Pass_Entry.length() == 3) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass3s, sizeof(Pass3s));
        }
        if (Pass_Entry.length() == 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass4s, sizeof(Pass4s));
        }
        if (Pass_Entry.length() > 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
        }
        receivedFloat = 99;
        Serial.println(Pass_Entry);
      }

      if (receivedFloat == 88) {
        Pass_Entry += 8;
        if (Pass_Entry.length() == 1) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass1s, sizeof(Pass1s));
        }
        if (Pass_Entry.length() == 2) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass2s, sizeof(Pass2s));
        }
        if (Pass_Entry.length() == 3) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass3s, sizeof(Pass3s));
        }
        if (Pass_Entry.length() == 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass4s, sizeof(Pass4s));
        }
        if (Pass_Entry.length() > 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
        }
        receivedFloat = 99;
        Serial.println(Pass_Entry);
      }

      if (receivedFloat == 89) {
        Pass_Entry += 9;
        if (Pass_Entry.length() == 1) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass1s, sizeof(Pass1s));
        }
        if (Pass_Entry.length() == 2) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass2s, sizeof(Pass2s));
        }
        if (Pass_Entry.length() == 3) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass3s, sizeof(Pass3s));
        }
        if (Pass_Entry.length() == 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass4s, sizeof(Pass4s));
        }
        if (Pass_Entry.length() > 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
        }
        receivedFloat = 99;
        Serial.println(Pass_Entry);
      }

      if (receivedFloat == 80) {
        Pass_Entry += 0;
        if (Pass_Entry.length() == 1) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass1s, sizeof(Pass1s));
        }
        if (Pass_Entry.length() == 2) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass2s, sizeof(Pass2s));
        }
        if (Pass_Entry.length() == 3) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass3s, sizeof(Pass3s));
        }
        if (Pass_Entry.length() == 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass4s, sizeof(Pass4s));
        }
        if (Pass_Entry.length() > 4) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
        }
        receivedFloat = 99;
        Serial.println(Pass_Entry);
      }

      if (receivedFloat == 91) {
        dwinSerial.write(PassClr, sizeof(PassClr));
        Pass_Entry = "";
        receivedFloat = 99;
        Serial.println("Entry Cleared");
      }

      if (receivedFloat == 92) {
        if (Pass_Entry != Pass_Fixed) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          Pass_Entry = "";
          receivedFloat = 99;
          Serial.println("Password Wrong try again ");
        }
        if (Pass_Entry == Pass_Fixed) {
          dwinSerial.write(PassClr, sizeof(PassClr));
          dwinSerial.write(Pass_Page5, sizeof(Pass_Page5));
          Pass_Entry = "";
          receivedFloat = 99;
          Pasword_Lock = false;
          Serial.println("Password Correct and reset variable done ");
        }
      }
    }
  }
}
