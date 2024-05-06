
//-------------------------------------------------------------Set_Time-----------------------------------------------------------------------------

void Set_Time() {

  Fetch_Text();

  if (receivedFloat == 75) {

    DateTime now = rtc.now();
    Time_Lock = true;
    dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));

    while (Time_Lock == true) {
      DateTime now = rtc.now();
      int Yearx = now.year();
      int Monthx = now.month();
      int Dayx = now.day();
      //int Dayx = 6;

      //-----------------------------Hour-Displayer-----------------------------

      if (dwinSerial.available() > 0 && Hourb == true) {
        Collect = dwinSerial.readString();
        Time_receivedFloat = atof(Collect.c_str());

        if (Time_receivedFloat >= 0 && Time_receivedFloat < 24) {
          Hourx = Time_receivedFloat;
          Hourb = false;
          Minb = true;
          Secb = false;
          Syncb = false;
          Serial.print("Hour -> ");
          Serial.println(Hourx);

          sprintf(Disp_Hour_Char, "%02i", Hourx);
          dwinSerial.write(0x5A);
          dwinSerial.write(0xA5);
          dwinSerial.write(strlen(Disp_Hour_Char) + 3);
          dwinSerial.write(0x82);
          dwinSerial.write(0x16);
          dwinSerial.write(0x00);

          for (int i = 0; i < strlen(Disp_Hour_Char); i++) {
            char c = Disp_Hour_Char[i];
            dwinSerial.write(c);
          }

          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Min, sizeof(Dis_Info_Min));
          dwinSerial.write(Dis_Info_Min, sizeof(Dis_Info_Min));
        }
Serial.println(Time_receivedFloat);
        if ((Time_receivedFloat == 76) || (Time_receivedFloat == 78)) {
          Hourb = true;
          Minb = false;
          Secb = false;
          Syncb = false;
          Serial.print("Time Data Erased");
          dwinSerial.write(Dis_Hour, sizeof(Dis_Hour));
          dwinSerial.write(Dis_Min, sizeof(Dis_Min));
          dwinSerial.write(Dis_Sec, sizeof(Dis_Sec));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));
          dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));

          if (Time_receivedFloat == 78) {
            Serial.print("Back_Out_Loop");
            Time_Lock = false;
            receivedFloat = 99;
          }
        }
      }

      //-----------------------------Minutes-Displayer-----------------------------

      if (dwinSerial.available() > 0 && Minb == true) {
        Collect = dwinSerial.readString();
        Time_receivedFloat = atof(Collect.c_str());
        if (Time_receivedFloat >= 0 && Time_receivedFloat < 61) {

          Minx = Time_receivedFloat;
          Hourb = false;
          Minb = false;
          Secb = true;
          Syncb = false;
          Serial.print("Min -> ");
          Serial.println(Minx);

          sprintf(Disp_Min_Char, "%02i", Minx);
          dwinSerial.write(0x5A);
          dwinSerial.write(0xA5);
          dwinSerial.write(strlen(Disp_Min_Char) + 3);
          dwinSerial.write(0x82);
          dwinSerial.write(0x16);
          dwinSerial.write(0x05);
          
          for (int i = 0; i < strlen(Disp_Min_Char); i++) {
            char c = Disp_Min_Char[i];
            dwinSerial.write(c);
          }
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Sec, sizeof(Dis_Info_Sec));
          dwinSerial.write(Dis_Info_Sec, sizeof(Dis_Info_Sec));
        }

        if ((Time_receivedFloat == 76) || (Time_receivedFloat == 78)) {
          Hourb = true;
          Minb = false;
          Secb = false;
          Syncb = false;
          Serial.print("Time Data Erased");
          dwinSerial.write(Dis_Hour, sizeof(Dis_Hour));
          dwinSerial.write(Dis_Min, sizeof(Dis_Min));
          dwinSerial.write(Dis_Sec, sizeof(Dis_Sec));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));
          dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));
          if (Time_receivedFloat == 78) {
            Serial.print("Back_Out_Loop");
            Time_Lock = false;
            receivedFloat = 99;
          }
        }
      }

      //-----------------------------Seconds-Displayer-----------------------------

      if (dwinSerial.available() > 0 && Secb == true) {
        Collect = dwinSerial.readString();
        Time_receivedFloat = atof(Collect.c_str());

        if (Time_receivedFloat >= 0 && Time_receivedFloat < 61) {
          Secx = Time_receivedFloat;
          Hourb = false;
          Minb = false;
          Secb = false;
          Syncb = true;
          Serial.print("Sec -> ");
          Serial.println(Secx);

          sprintf(Disp_Sec_Char, "%02i", Secx);
          dwinSerial.write(0x5A);
          dwinSerial.write(0xA5);
          dwinSerial.write(strlen(Disp_Sec_Char) + 3);
          dwinSerial.write(0x82);
          dwinSerial.write(0x16);
          dwinSerial.write(0x10);

          for (int i = 0; i < strlen(Disp_Sec_Char); i++) {
            char c = Disp_Sec_Char[i];
            dwinSerial.write(c);
          }
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Sync, sizeof(Dis_Info_Sync));
          dwinSerial.write(Dis_Info_Sync, sizeof(Dis_Info_Sync));
        }

        if ((Time_receivedFloat == 76) || (Time_receivedFloat == 78)) {
          Hourb = true;
          Minb = false;
          Secb = false;
          Syncb = false;
          Serial.print("Time Data Erased");
          dwinSerial.write(Dis_Hour, sizeof(Dis_Hour));
          dwinSerial.write(Dis_Min, sizeof(Dis_Min));
          dwinSerial.write(Dis_Sec, sizeof(Dis_Sec));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));
          dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));

          if (Time_receivedFloat == 78) {
            Serial.print("Back_Out_Loop");
            Time_Lock = false;
            receivedFloat = 99;
          }
        }
      }

      //-----------------------------Sync-Displayer-----------------------------

      if (dwinSerial.available() > 0 && Syncb == true) {
        Collect = dwinSerial.readString();
        Time_receivedFloat = atof(Collect.c_str());

        if ((Time_receivedFloat == 76) || (Time_receivedFloat == 78)) {
          Hourb = true;
          Minb = false;
          Secb = false;
          Syncb = false;
          Serial.print("Time Data Erased");
          dwinSerial.write(Dis_Hour, sizeof(Dis_Hour));
          dwinSerial.write(Dis_Min, sizeof(Dis_Min));
          dwinSerial.write(Dis_Sec, sizeof(Dis_Sec));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));
          dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));

          if (Time_receivedFloat == 78) {
            Serial.print("Back_Out_Loop");
            Time_Lock = false;
            receivedFloat = 99;
          }
        }

        if (Time_receivedFloat == 77) {
          Hourb = true;
          Minb = false;
          Secb = false;
          Syncb = false;
          rtc.adjust(DateTime(Yearx, Monthx, Dayx, Hourx, Minx, Secx));
          Serial.print("Synced");
          //Hourx = ""; Minx = ""; Secx = "";
          dwinSerial.write(Dis_Hour, sizeof(Dis_Hour));
          dwinSerial.write(Dis_Min, sizeof(Dis_Min));
          dwinSerial.write(Dis_Sec, sizeof(Dis_Sec));
          dwinSerial.write(Home_Page1, sizeof(Home_Page1));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Clr, sizeof(Dis_Info_Clr));
          dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));
          dwinSerial.write(Dis_Info_Hour, sizeof(Dis_Info_Hour));
          receivedFloat = 99;
          Time_Lock = false;
        }
      }
    }

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(10);
  }
}
