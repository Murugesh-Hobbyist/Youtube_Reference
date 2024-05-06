
//-------------------------------------------------------------readADC-----------------------------------------------------------------------------

void Read_ADC() {

  Core0_ADC_1 = ADS1.readADC_SingleEnded(3);
  Core0_ADC_2 = ADS1.readADC_SingleEnded(2);
  Core0_ADC_3 = ADS2.readADC_SingleEnded(1);
  Core0_ADC_4 = ADS2.readADC_SingleEnded(0);
  Core0_ADC_5 = ADS2.readADC_SingleEnded(3);
  Core0_ADC_6 = ADS2.readADC_SingleEnded(2);

  //    Serial.print(" ADC-1 -> ");Serial.print(Core0_ADC_1);Serial.print(" ADC-2 -> ");Serial.print(Core0_ADC_2);Serial.print(" ADC-3 -> ");Serial.print(Core0_ADC_3);
  //    Serial.print(" ADC-4 -> ");Serial.print(Core0_ADC_4);Serial.print(" ADC-5 -> ");Serial.print(Core0_ADC_5);Serial.print(" ADC-6 -> ");Serial.println(Core0_ADC_6);

  //---------When receiving float----------------

  if (check == 0) {
    Serial.println("im in...............");
    if (millis() - ADCTimer > 50) {
      Convert1 = Core0_ADC_1;
      Convert2 = Core0_ADC_2;
      Convert3 = Core0_ADC_3;
      Convert4 = Core0_ADC_4;
      Convert5 = Core0_ADC_5;
      Convert6 = Core0_ADC_6;

      Final_ADC1 = map(Convert1, 9, 17629, 1110, 0);
      Final_ADC1 = (Final_ADC1 / 100);
      Setval_ADC1 = Final_ADC1;

      Final_ADC2 = map(Convert2, 10, 17629, 1108, 0);
      Final_ADC2 = (Final_ADC2 / 100);
      Setval_ADC2 = Final_ADC2;

      Final_ADC3 = map(Convert3, 15, 17623, 1104, 0);
      Final_ADC3 = (Final_ADC3 / 100);
      Setval_ADC3 = Final_ADC3;

      Final_ADC4 = map(Convert4, 8, 17629, 1109, 0);
      Final_ADC4 = (Final_ADC4 / 100);
      Setval_ADC4 = Final_ADC4;

      Final_ADC5 = map(Convert5, 8, 17629, 1105, 0);
      Final_ADC5 = (Final_ADC5 / 100);
      Setval_ADC5 = Final_ADC5;

      Final_ADC6 = map(Convert6, 12, 17629, 1102, 0);
      Final_ADC6 = (Final_ADC6 / 100);
      Setval_ADC6 = Final_ADC6;

      Save_Library.begin("Storage", false);
      Save_Library.putFloat("ADC1", Setval_ADC1);
      delay(10);
      Save_Library.putFloat("ADC2", Setval_ADC2);
      delay(10);
      Save_Library.putFloat("ADC3", Setval_ADC3);
      delay(10);
      Save_Library.putFloat("ADC4", Setval_ADC4);
      delay(10);
      Save_Library.putFloat("ADC5", Setval_ADC5);
      delay(10);
      Save_Library.putFloat("ADC6", Setval_ADC6);
      delay(10);
      delay(10);
      Save_Library.end();

      sendFloatActual_ADC1(Setval_ADC1);
      sendFloatActual_ADC2(Setval_ADC2);
      sendFloatActual_ADC3(Setval_ADC3);
      sendFloatActual_ADC4(Setval_ADC4);
      sendFloatActual_ADC5(Setval_ADC5);
      sendFloatActual_ADC6(Setval_ADC6);

      ADCTimer = millis();
      check = 1;
    }
  }

  //---------Setting Mode----------------

  while ((receivedFloat == 95) && (Modex_Change == true)) {
    while ((Modex == "Manual") && (Modex_Change == true)) {
      Modex = "Auto";
      dwinSerial.write(Dis_Info_Mode_Clr, sizeof(Dis_Info_Mode_Clr));
      dwinSerial.write(Dis_Info_Auto, sizeof(Dis_Info_Auto));

      Save_Library.begin("Storage", false);
      Save_Library.putString("Sav_Modex", "Auto");
      delay(10);
      Save_Library.end();

      Serial.println("Set to Auto");
      receivedFloat = 99;
      Modex_Change = false;
    }
    while ((Modex == "Auto") && (Modex_Change == true)) {
      Modex = "Manual";
      dwinSerial.write(Dis_Info_Mode_Clr, sizeof(Dis_Info_Mode_Clr));
      dwinSerial.write(Dis_Info_Manual, sizeof(Dis_Info_Manual));

      Save_Library.begin("Storage", false);
      Save_Library.putString("Sav_Modex", "Manual");
      delay(10);
      Save_Library.end();

      Serial.println("Set to Manual");
      Modex_Change = false;
      receivedFloat = 99;
    }
  }
  Modex_Change = true;


  //----Refresh black Map plottings in Probe page----------------

  if (receivedFloat == 65) {
    dwinSerial.write(Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
    dwinSerial.write(Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
    dwinSerial.write(Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
    dwinSerial.write(Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
    dwinSerial.write(Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
    dwinSerial.write(Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
  }

  //----Assign 20 plottings and their results in home page----------------

  while (receivedFloat == 41) {
    if (dwinSerial.available() > 0) {
      Collect = dwinSerial.readString();
      receivedFloat = atof(Collect.c_str());
    }

    if (receivedFloat == 21) {  //Pos-1
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num1, sizeof(Probe1_Num1));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos1_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos1_Num1_Green[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos1_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num1); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num1[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(1, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 22) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num2, sizeof(Probe1_Num2));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos2_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos2_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos2_Num1_Red[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num2); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num2[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(2, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 23) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num3, sizeof(Probe1_Num3));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos3_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos3_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos3_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num3); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num3[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(3, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 24) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num4, sizeof(Probe1_Num4));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos4_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos4_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos4_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num4); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num4[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(4, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 25) {  //Pos-2

      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num5, sizeof(Probe1_Num5));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos5_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos5_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos5_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num5); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num5[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(5, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 26) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num6, sizeof(Probe1_Num6));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos6_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos6_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos6_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num6); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num6[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(6, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 27) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num7, sizeof(Probe1_Num7));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos7_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos7_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos7_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num7); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num7[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(7, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 28) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num8, sizeof(Probe1_Num8));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos8_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos8_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos8_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num8); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num8[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(8, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 29) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num9, sizeof(Probe1_Num9));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos9_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos9_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos9_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num9); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num9[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(9, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 30) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num10, sizeof(Probe1_Num10));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos10_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos10_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos10_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num10); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num10[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(10, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 31) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num11, sizeof(Probe1_Num11));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos11_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos11_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos11_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num11); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num11[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(11, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 32) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num12, sizeof(Probe1_Num12));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos12_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos12_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos12_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num12); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num12[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(12, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 33) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num13, sizeof(Probe1_Num13));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos13_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos13_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos13_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num13); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num13[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(13, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 34) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num14, sizeof(Probe1_Num14));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos14_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos14_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos14_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num14); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num14[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(14, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 35) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num15, sizeof(Probe1_Num15));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos15_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos15_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos15_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num15); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num15[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(15, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 36) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num16, sizeof(Probe1_Num16));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos16_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos16_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos16_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num16); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num16[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(16, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 37) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num17, sizeof(Probe1_Num17));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos17_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos17_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos17_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num17); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num17[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(17, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 38) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num18, sizeof(Probe1_Num18));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos18_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos18_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos18_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num18); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num18[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(18, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 39) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num19, sizeof(Probe1_Num19));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos19_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos19_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos19_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num19); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num19[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(19, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }

    if (receivedFloat == 40) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe1_Num1_2_Off, sizeof(Probe1_Num1_2_Off));
      dwinSerial.write(Probe1_Num3_4_Off, sizeof(Probe1_Num3_4_Off));
      dwinSerial.write(Probe1_Num5_6_Off, sizeof(Probe1_Num5_6_Off));
      dwinSerial.write(Probe1_Num7_8_Off, sizeof(Probe1_Num7_8_Off));
      dwinSerial.write(Probe1_Num9_10_Off, sizeof(Probe1_Num9_10_Off));
      dwinSerial.write(Probe1_Num11_12_Off, sizeof(Probe1_Num11_12_Off));
      dwinSerial.write(Probe1_Num13_14_Off, sizeof(Probe1_Num13_14_Off));
      dwinSerial.write(Probe1_Num15_16_Off, sizeof(Probe1_Num15_16_Off));
      dwinSerial.write(Probe1_Num17_18_Off, sizeof(Probe1_Num17_18_Off));
      dwinSerial.write(Probe1_Num19_20_Off, sizeof(Probe1_Num19_20_Off));
      dwinSerial.write(Probe1_Num20, sizeof(Probe1_Num20));

      dwinSerial.write(Selected_Pos1_Off, sizeof(Selected_Pos1_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num1_Off); Array_Copier++) {
        Selected_Pos1_Off[Array_Copier] = Pos20_Num1_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num1_Green); Array_Copier++) {
        Selected_Pos1_Green[Array_Copier] = Pos20_Num1_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num1_Red); Array_Copier++) {
        Selected_Pos1_Red[Array_Copier] = Pos20_Num1_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe1_Num20); Array_Copier++) {
        Selected_Probe1_Num[Array_Copier] = Probe1_Num20[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos1_Off", Selected_Pos1_Off, sizeof(Selected_Pos1_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Green", Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos1_Red", Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob1_Num", Selected_Probe1_Num, sizeof(Selected_Probe1_Num));
      delay(10);

      itoa(1, User_Map1, 10);
      itoa(20, True_Map1, 10);

      Save_Library.putBytes("Sav_User_Map1", User_Map1, sizeof(User_Map1));
      delay(10);
      Save_Library.putBytes("Sav_True_Map1", True_Map1, sizeof(True_Map1));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos1_Off, Selected_Pos1_Green, Selected_Pos1_Red, Selected_Probe1_Num are Saved!");
    }
  }

  while (receivedFloat == 42) {
    if (dwinSerial.available() > 0) {
      Collect = dwinSerial.readString();
      receivedFloat = atof(Collect.c_str());
    }

    if (receivedFloat == 21) {  //Pos-1
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num1, sizeof(Probe2_Num1));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos1_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos1_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos1_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num1); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num1[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(1, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 22) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num2, sizeof(Probe2_Num2));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos2_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos2_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos2_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num2); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num2[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(2, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 23) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num3, sizeof(Probe2_Num3));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos3_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos3_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos3_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num3); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num3[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(3, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 24) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num4, sizeof(Probe2_Num4));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos4_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos4_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos4_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num4); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num4[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(4, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 25) {  //Pos-2

      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num5, sizeof(Probe2_Num5));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos5_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos5_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos5_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num5); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num5[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(5, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 26) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num6, sizeof(Probe2_Num6));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos6_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos6_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos6_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num6); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num6[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(6, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 27) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num7, sizeof(Probe2_Num7));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos7_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos7_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos7_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num7); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num7[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(7, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 28) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num8, sizeof(Probe2_Num8));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos8_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos8_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos8_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num8); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num8[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(8, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 29) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num9, sizeof(Probe2_Num9));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos9_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos9_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos9_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num9); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num9[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(9, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 30) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num10, sizeof(Probe2_Num10));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos10_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos10_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos10_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num10); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num10[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(10, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 31) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num11, sizeof(Probe2_Num11));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos11_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos11_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos11_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num11); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num11[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(11, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 32) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num12, sizeof(Probe2_Num12));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos12_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos12_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos12_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num12); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num12[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(12, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 33) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num13, sizeof(Probe2_Num13));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos13_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos13_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos13_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num13); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num13[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(13, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 34) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num14, sizeof(Probe2_Num14));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos14_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos14_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos14_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num14); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num14[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(14, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 35) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num15, sizeof(Probe2_Num15));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos15_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos15_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos15_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num15); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num15[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(15, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 36) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num16, sizeof(Probe2_Num16));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos16_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos16_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos16_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num16); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num16[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(16, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 37) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num17, sizeof(Probe2_Num17));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos17_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos17_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos17_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num17); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num17[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(17, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 38) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num18, sizeof(Probe2_Num18));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos18_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos18_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos18_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num18); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num18[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(18, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 39) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num19, sizeof(Probe2_Num19));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos19_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos19_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos19_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num19); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num19[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(19, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }

    if (receivedFloat == 40) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe2_Num1_2_Off, sizeof(Probe2_Num1_2_Off));
      dwinSerial.write(Probe2_Num3_4_Off, sizeof(Probe2_Num3_4_Off));
      dwinSerial.write(Probe2_Num5_6_Off, sizeof(Probe2_Num5_6_Off));
      dwinSerial.write(Probe2_Num7_8_Off, sizeof(Probe2_Num7_8_Off));
      dwinSerial.write(Probe2_Num9_10_Off, sizeof(Probe2_Num9_10_Off));
      dwinSerial.write(Probe2_Num11_12_Off, sizeof(Probe2_Num11_12_Off));
      dwinSerial.write(Probe2_Num13_14_Off, sizeof(Probe2_Num13_14_Off));
      dwinSerial.write(Probe2_Num15_16_Off, sizeof(Probe2_Num15_16_Off));
      dwinSerial.write(Probe2_Num17_18_Off, sizeof(Probe2_Num17_18_Off));
      dwinSerial.write(Probe2_Num19_20_Off, sizeof(Probe2_Num19_20_Off));
      dwinSerial.write(Probe2_Num20, sizeof(Probe2_Num20));

      dwinSerial.write(Selected_Pos2_Off, sizeof(Selected_Pos2_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num2_Off); Array_Copier++) {
        Selected_Pos2_Off[Array_Copier] = Pos20_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num2_Green); Array_Copier++) {
        Selected_Pos2_Green[Array_Copier] = Pos20_Num2_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num2_Red); Array_Copier++) {
        Selected_Pos2_Red[Array_Copier] = Pos20_Num2_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe2_Num20); Array_Copier++) {
        Selected_Probe2_Num[Array_Copier] = Probe2_Num20[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos2_Off", Selected_Pos2_Off, sizeof(Selected_Pos2_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Green", Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos2_Red", Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob2_Num", Selected_Probe2_Num, sizeof(Selected_Probe2_Num));
      delay(10);

      itoa(2, User_Map2, 10);
      itoa(20, True_Map2, 10);

      Save_Library.putBytes("Sav_User_Map2", User_Map2, sizeof(User_Map2));
      delay(10);
      Save_Library.putBytes("Sav_True_Map2", True_Map2, sizeof(True_Map2));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos2_Off, Selected_Pos2_Green, Selected_Pos2_Red, Selected_Probe2_Num  are Saved!");
    }
  }

  while (receivedFloat == 43) {
    if (dwinSerial.available() > 0) {
      Collect = dwinSerial.readString();
      receivedFloat = atof(Collect.c_str());
    }

    if (receivedFloat == 21) {  //Pos-1
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num1, sizeof(Probe3_Num1));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos1_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos1_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos1_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num1); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num1[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(1, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 22) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num2, sizeof(Probe3_Num2));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos2_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos2_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos2_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num2); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num2[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(2, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 23) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num3, sizeof(Probe3_Num3));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos3_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos3_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos3_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num3); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num3[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(3, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 24) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num4, sizeof(Probe3_Num4));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos4_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos4_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos4_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num4); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num4[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(4, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 25) {  //Pos-2

      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num5, sizeof(Probe3_Num5));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos5_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos5_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos5_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num5); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num5[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(5, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 26) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num6, sizeof(Probe3_Num6));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos6_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos6_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos6_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num6); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num6[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(6, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 27) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num7, sizeof(Probe3_Num7));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos7_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos7_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos7_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num7); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num7[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(7, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 28) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num8, sizeof(Probe3_Num8));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos8_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos8_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos8_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num8); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num8[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(8, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 29) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num9, sizeof(Probe3_Num9));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos9_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos9_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos9_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num9); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num9[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(9, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 30) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num10, sizeof(Probe3_Num10));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos10_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos10_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos10_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num10); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num10[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(10, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 31) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num11, sizeof(Probe3_Num11));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos11_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos11_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos11_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num11); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num11[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(11, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 32) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num12, sizeof(Probe3_Num12));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos12_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos12_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos12_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num12); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num12[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(12, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 33) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num13, sizeof(Probe3_Num13));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos13_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos13_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos13_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num13); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num13[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(13, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 34) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num14, sizeof(Probe3_Num14));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos14_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos14_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos14_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num14); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num14[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(14, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 35) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num15, sizeof(Probe3_Num15));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos15_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos15_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos15_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num15); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num15[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(15, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 36) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num16, sizeof(Probe3_Num16));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos16_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos16_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos16_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num16); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num16[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(16, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 37) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num17, sizeof(Probe3_Num17));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos17_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos17_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos17_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num17); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num17[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(17, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 38) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num18, sizeof(Probe3_Num18));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos18_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos18_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos18_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num18); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num18[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(18, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 39) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num19, sizeof(Probe3_Num19));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos19_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos19_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos19_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num19); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num19[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(19, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }

    if (receivedFloat == 40) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe3_Num1_2_Off, sizeof(Probe3_Num1_2_Off));
      dwinSerial.write(Probe3_Num3_4_Off, sizeof(Probe3_Num3_4_Off));
      dwinSerial.write(Probe3_Num5_6_Off, sizeof(Probe3_Num5_6_Off));
      dwinSerial.write(Probe3_Num7_8_Off, sizeof(Probe3_Num7_8_Off));
      dwinSerial.write(Probe3_Num9_10_Off, sizeof(Probe3_Num9_10_Off));
      dwinSerial.write(Probe3_Num11_12_Off, sizeof(Probe3_Num11_12_Off));
      dwinSerial.write(Probe3_Num13_14_Off, sizeof(Probe3_Num13_14_Off));
      dwinSerial.write(Probe3_Num15_16_Off, sizeof(Probe3_Num15_16_Off));
      dwinSerial.write(Probe3_Num17_18_Off, sizeof(Probe3_Num17_18_Off));
      dwinSerial.write(Probe3_Num19_20_Off, sizeof(Probe3_Num19_20_Off));
      dwinSerial.write(Probe3_Num20, sizeof(Probe3_Num20));

      dwinSerial.write(Selected_Pos3_Off, sizeof(Selected_Pos3_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num3_Off); Array_Copier++) {
        Selected_Pos3_Off[Array_Copier] = Pos20_Num3_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num3_Green); Array_Copier++) {
        Selected_Pos3_Green[Array_Copier] = Pos20_Num3_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num3_Red); Array_Copier++) {
        Selected_Pos3_Red[Array_Copier] = Pos20_Num3_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe3_Num20); Array_Copier++) {
        Selected_Probe3_Num[Array_Copier] = Probe3_Num20[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos3_Off", Selected_Pos3_Off, sizeof(Selected_Pos3_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Green", Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos3_Red", Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob3_Num", Selected_Probe3_Num, sizeof(Selected_Probe3_Num));
      delay(10);

      itoa(3, User_Map3, 10);
      itoa(20, True_Map3, 10);

      Save_Library.putBytes("Sav_User_Map3", User_Map3, sizeof(User_Map3));
      delay(10);
      Save_Library.putBytes("Sav_True_Map3", True_Map3, sizeof(True_Map3));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos3_Off, Selected_Pos3_Green, Selected_Pos3_Red, Selected_Probe3_Num are Saved!");
    }
  }

  while (receivedFloat == 44) {
    if (dwinSerial.available() > 0) {
      Collect = dwinSerial.readString();
      receivedFloat = atof(Collect.c_str());
    }

    if (receivedFloat == 21) {  //Pos-1
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num1, sizeof(Probe4_Num1));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos1_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos1_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos1_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num1); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num1[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(1, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 22) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num2, sizeof(Probe4_Num2));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos2_Num2_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos2_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos2_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num2); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num2[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(2, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 23) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num3, sizeof(Probe4_Num3));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos3_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos3_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos3_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num3); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num3[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(3, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 24) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num4, sizeof(Probe4_Num4));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos4_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos4_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos4_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num4); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num4[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(4, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 25) {  //Pos-2

      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num5, sizeof(Probe4_Num5));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos5_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos5_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos5_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num5); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num5[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(5, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 26) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num6, sizeof(Probe4_Num6));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos6_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos6_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos6_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num6); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num6[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(6, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 27) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num7, sizeof(Probe4_Num7));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos7_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos7_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos7_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num7); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num7[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(7, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 28) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num8, sizeof(Probe4_Num8));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos8_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos8_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos8_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num8); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num8[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(8, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 29) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num9, sizeof(Probe4_Num9));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos9_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos9_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos9_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num9); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num9[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(9, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 30) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num10, sizeof(Probe4_Num10));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos10_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos10_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos10_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num10); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num10[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(10, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 31) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num11, sizeof(Probe4_Num11));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos11_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos11_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos11_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num11); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num11[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(11, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 32) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num12, sizeof(Probe4_Num12));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos12_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos12_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos12_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num12); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num12[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(12, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 33) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num13, sizeof(Probe4_Num13));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos13_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos13_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos13_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num13); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num13[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(13, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 34) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num14, sizeof(Probe4_Num14));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos14_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos14_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos14_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num14); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num14[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(14, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 35) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num15, sizeof(Probe4_Num15));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos15_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos15_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos15_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num15); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num15[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(15, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 36) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num16, sizeof(Probe4_Num16));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos16_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos16_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos16_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num16); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num16[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(16, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 37) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num17, sizeof(Probe4_Num17));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos17_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos17_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos17_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num17); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num17[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(17, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 38) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num18, sizeof(Probe4_Num18));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos18_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos18_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos18_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num18); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num18[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(18, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 39) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num19, sizeof(Probe4_Num19));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos19_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos19_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos19_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num19); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num19[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(19, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }

    if (receivedFloat == 40) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe4_Num1_2_Off, sizeof(Probe4_Num1_2_Off));
      dwinSerial.write(Probe4_Num3_4_Off, sizeof(Probe4_Num3_4_Off));
      dwinSerial.write(Probe4_Num5_6_Off, sizeof(Probe4_Num5_6_Off));
      dwinSerial.write(Probe4_Num7_8_Off, sizeof(Probe4_Num7_8_Off));
      dwinSerial.write(Probe4_Num9_10_Off, sizeof(Probe4_Num9_10_Off));
      dwinSerial.write(Probe4_Num11_12_Off, sizeof(Probe4_Num11_12_Off));
      dwinSerial.write(Probe4_Num13_14_Off, sizeof(Probe4_Num13_14_Off));
      dwinSerial.write(Probe4_Num15_16_Off, sizeof(Probe4_Num15_16_Off));
      dwinSerial.write(Probe4_Num17_18_Off, sizeof(Probe4_Num17_18_Off));
      dwinSerial.write(Probe4_Num19_20_Off, sizeof(Probe4_Num19_20_Off));
      dwinSerial.write(Probe4_Num20, sizeof(Probe4_Num20));

      dwinSerial.write(Selected_Pos4_Off, sizeof(Selected_Pos4_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num4_Off); Array_Copier++) {
        Selected_Pos4_Off[Array_Copier] = Pos20_Num4_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num4_Green); Array_Copier++) {
        Selected_Pos4_Green[Array_Copier] = Pos20_Num4_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num4_Red); Array_Copier++) {
        Selected_Pos4_Red[Array_Copier] = Pos20_Num4_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe4_Num20); Array_Copier++) {
        Selected_Probe4_Num[Array_Copier] = Probe4_Num20[Array_Copier];
      }

      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos4_Off", Selected_Pos4_Off, sizeof(Selected_Pos4_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Green", Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos4_Red", Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob4_Num", Selected_Probe4_Num, sizeof(Selected_Probe4_Num));
      delay(10);

      itoa(4, User_Map4, 10);
      itoa(20, True_Map4, 10);

      Save_Library.putBytes("Sav_User_Map4", User_Map4, sizeof(User_Map4));
      delay(10);
      Save_Library.putBytes("Sav_True_Map4", True_Map4, sizeof(True_Map4));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos4_Off, Selected_Pos4_Green, Selected_Pos4_Red, Selected_Probe4_Num are Saved!");
    }
  }

  while (receivedFloat == 45) {
    if (dwinSerial.available() > 0) {
      Collect = dwinSerial.readString();
      receivedFloat = atof(Collect.c_str());
    }

    if (receivedFloat == 21) {  //Pos-1
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num1, sizeof(Probe5_Num1));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos1_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos1_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos1_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num1); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num1[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(1, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 22) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num2, sizeof(Probe5_Num2));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos2_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos2_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos2_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num2); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num2[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(2, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 23) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num3, sizeof(Probe5_Num3));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos3_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos3_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos3_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num3); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num3[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(31, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 24) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num4, sizeof(Probe5_Num4));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos4_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos4_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos4_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num4); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num4[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(4, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 25) {  //Pos-2

      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num5, sizeof(Probe5_Num5));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos5_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos5_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos5_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num5); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num5[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(5, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 26) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num6, sizeof(Probe5_Num6));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos6_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos6_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos6_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num6); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num6[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(6, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 27) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num7, sizeof(Probe5_Num7));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos7_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos7_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos7_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num7); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num7[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(7, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 28) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num8, sizeof(Probe5_Num8));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos8_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos8_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos8_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num8); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num8[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(8, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 29) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num9, sizeof(Probe5_Num9));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos9_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos9_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos9_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num9); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num9[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(9, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 30) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num10, sizeof(Probe5_Num10));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos10_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos10_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos10_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num10); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num10[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(10, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 31) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num11, sizeof(Probe5_Num11));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos11_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos11_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos11_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num11); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num11[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(11, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 32) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num12, sizeof(Probe5_Num12));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos12_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos12_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos12_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num12); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num12[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(12, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 33) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num13, sizeof(Probe5_Num13));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos13_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos13_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos13_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num13); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num13[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(13, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 34) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num14, sizeof(Probe5_Num14));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos14_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos14_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos14_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num14); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num14[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(14, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 35) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num15, sizeof(Probe5_Num15));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos15_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos15_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos15_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num15); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num15[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(15, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 36) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num16, sizeof(Probe5_Num16));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos16_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos16_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos16_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num16); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num16[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(16, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 37) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num17, sizeof(Probe5_Num17));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos17_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos17_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos17_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num17); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num17[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(17, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 38) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num18, sizeof(Probe5_Num18));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos18_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos18_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos18_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num18); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num18[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(18, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 39) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num19, sizeof(Probe5_Num19));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos19_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos19_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos19_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num19); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num19[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(19, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }

    if (receivedFloat == 40) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe5_Num1_2_Off, sizeof(Probe5_Num1_2_Off));
      dwinSerial.write(Probe5_Num3_4_Off, sizeof(Probe5_Num3_4_Off));
      dwinSerial.write(Probe5_Num5_6_Off, sizeof(Probe5_Num5_6_Off));
      dwinSerial.write(Probe5_Num7_8_Off, sizeof(Probe5_Num7_8_Off));
      dwinSerial.write(Probe5_Num9_10_Off, sizeof(Probe5_Num9_10_Off));
      dwinSerial.write(Probe5_Num11_12_Off, sizeof(Probe5_Num11_12_Off));
      dwinSerial.write(Probe5_Num13_14_Off, sizeof(Probe5_Num13_14_Off));
      dwinSerial.write(Probe5_Num15_16_Off, sizeof(Probe5_Num15_16_Off));
      dwinSerial.write(Probe5_Num17_18_Off, sizeof(Probe5_Num17_18_Off));
      dwinSerial.write(Probe5_Num19_20_Off, sizeof(Probe5_Num19_20_Off));
      dwinSerial.write(Probe5_Num20, sizeof(Probe5_Num20));

      dwinSerial.write(Selected_Pos5_Off, sizeof(Selected_Pos5_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num5_Off); Array_Copier++) {
        Selected_Pos5_Off[Array_Copier] = Pos20_Num5_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num5_Green); Array_Copier++) {
        Selected_Pos5_Green[Array_Copier] = Pos20_Num5_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num5_Red); Array_Copier++) {
        Selected_Pos5_Red[Array_Copier] = Pos20_Num5_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe5_Num20); Array_Copier++) {
        Selected_Probe5_Num[Array_Copier] = Probe5_Num20[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos5_Off", Selected_Pos5_Off, sizeof(Selected_Pos5_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Green", Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos5_Red", Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob5_Num", Selected_Probe5_Num, sizeof(Selected_Probe5_Num));
      delay(10);

      itoa(5, User_Map5, 10);
      itoa(20, True_Map5, 10);

      Save_Library.putBytes("Sav_User_Map5", User_Map5, sizeof(User_Map5));
      delay(10);
      Save_Library.putBytes("Sav_True_Map5", True_Map5, sizeof(True_Map5));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos5_Off, Selected_Pos5_Green, Selected_Pos5_Red, Selected_Probe5_Num  are Saved!");
    }
  }

  while (receivedFloat == 46) {
    if (dwinSerial.available() > 0) {
      Collect = dwinSerial.readString();
      receivedFloat = atof(Collect.c_str());
    }

    if (receivedFloat == 21) {  //Pos-1
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num1, sizeof(Probe6_Num1));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos1_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos1_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos1_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos1_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num1); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num1[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(1, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 22) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num2, sizeof(Probe6_Num2));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos2_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos2_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos2_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos2_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num2); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num2[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(2, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 23) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num3, sizeof(Probe6_Num3));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos3_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos3_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos3_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos3_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num3); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num3[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(3, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 24) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num4, sizeof(Probe6_Num4));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos4_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos4_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos4_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos4_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num4); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num4[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(4, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 25) {  //Pos-2

      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num5, sizeof(Probe6_Num5));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos5_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos5_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos5_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos5_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num5); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num5[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(5, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 26) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num6, sizeof(Probe6_Num6));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos6_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos6_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos6_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos6_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num6); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num6[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(6, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 27) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num7, sizeof(Probe6_Num7));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos7_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos7_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos7_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos7_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num7); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num7[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(7, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 28) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num8, sizeof(Probe6_Num8));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos8_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos8_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos8_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos8_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num8); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num8[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(8, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 29) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num9, sizeof(Probe6_Num9));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos9_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos9_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos9_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos9_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num9); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num9[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(9, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 30) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num10, sizeof(Probe6_Num10));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos10_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos10_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos10_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos10_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num10); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num10[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(10, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 31) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num11, sizeof(Probe6_Num11));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos11_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos11_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos11_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos11_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num11); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num11[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(11, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 32) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num12, sizeof(Probe6_Num12));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos12_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos12_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos12_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos12_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num12); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num12[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(12, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 33) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num13, sizeof(Probe6_Num13));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos13_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos13_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos13_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos13_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num13); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num13[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(13, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 34) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num14, sizeof(Probe6_Num14));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos14_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos14_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos14_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos14_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num14); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num14[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(14, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 35) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num15, sizeof(Probe6_Num15));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos15_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos15_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos15_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos15_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num15); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num15[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(15, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 36) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num16, sizeof(Probe6_Num16));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos16_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos16_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos16_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos16_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num16); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num16[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(16, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 37) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num17, sizeof(Probe6_Num17));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos17_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos17_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos17_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos17_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num17); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num17[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(17, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 38) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num18, sizeof(Probe6_Num18));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos18_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos18_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos18_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos18_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num18); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num18[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(18, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 39) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num19, sizeof(Probe6_Num19));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos19_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos19_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos19_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos19_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num19); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num19[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(19, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }

    if (receivedFloat == 40) {  //Pos-2
      Serial.println(receivedFloat);
      dwinSerial.write(Probe6_Num1_2_Off, sizeof(Probe6_Num1_2_Off));
      dwinSerial.write(Probe6_Num3_4_Off, sizeof(Probe6_Num3_4_Off));
      dwinSerial.write(Probe6_Num5_6_Off, sizeof(Probe6_Num5_6_Off));
      dwinSerial.write(Probe6_Num7_8_Off, sizeof(Probe6_Num7_8_Off));
      dwinSerial.write(Probe6_Num9_10_Off, sizeof(Probe6_Num9_10_Off));
      dwinSerial.write(Probe6_Num11_12_Off, sizeof(Probe6_Num11_12_Off));
      dwinSerial.write(Probe6_Num13_14_Off, sizeof(Probe6_Num13_14_Off));
      dwinSerial.write(Probe6_Num15_16_Off, sizeof(Probe6_Num15_16_Off));
      dwinSerial.write(Probe6_Num17_18_Off, sizeof(Probe6_Num17_18_Off));
      dwinSerial.write(Probe6_Num19_20_Off, sizeof(Probe6_Num19_20_Off));
      dwinSerial.write(Probe6_Num20, sizeof(Probe6_Num20));

      dwinSerial.write(Selected_Pos6_Off, sizeof(Selected_Pos6_Off));

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num6_Off); Array_Copier++) {
        Selected_Pos6_Off[Array_Copier] = Pos20_Num6_Off[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num6_Green); Array_Copier++) {
        Selected_Pos6_Green[Array_Copier] = Pos20_Num6_Green[Array_Copier];
      }

      for (Array_Copier = 0; Array_Copier < sizeof(Pos20_Num6_Red); Array_Copier++) {
        Selected_Pos6_Red[Array_Copier] = Pos20_Num6_Red[Array_Copier];
      }
      for (Array_Copier = 0; Array_Copier < sizeof(Probe6_Num20); Array_Copier++) {
        Selected_Probe6_Num[Array_Copier] = Probe6_Num20[Array_Copier];
      }
      Save_Library.begin("Storage", false);
      Save_Library.putBytes("Sel_Pos6_Off", Selected_Pos6_Off, sizeof(Selected_Pos6_Off));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Green", Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
      delay(10);
      Save_Library.putBytes("Sel_Pos6_Red", Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
      delay(10);
      Save_Library.putBytes("Sel_Prob6_Num", Selected_Probe6_Num, sizeof(Selected_Probe6_Num));
      delay(10);

      itoa(6, User_Map6, 10);
      itoa(20, True_Map6, 10);

      Save_Library.putBytes("Sav_User_Map6", User_Map6, sizeof(User_Map6));
      delay(10);
      Save_Library.putBytes("Sav_True_Map6", True_Map6, sizeof(True_Map6));
      delay(10);

      Save_Library.end();
      Serial.print(" The Selected_Pos6_Off, Selected_Pos6_Green, Selected_Pos6_Red, Selected_Probe6_Num  are Saved!");
    }
  }




  if (millis() - ADCTimer > 50) {

    Convert1 = Core0_ADC_1;
    Convert2 = Core0_ADC_2;
    Convert3 = Core0_ADC_3;
    Convert4 = Core0_ADC_4;
    Convert5 = Core0_ADC_5;
    Convert6 = Core0_ADC_6;

    Final_ADC1 = map(Convert1, 9, 17629, 1110, 0);
    Final_ADC1 = (Final_ADC1 / 100) - Setval_ADC1;
    Final_ADC2 = map(Convert2, 10, 17629, 1108, 0);
    Final_ADC2 = (Final_ADC2 / 100) - Setval_ADC2;
    Final_ADC3 = map(Convert3, 15, 17623, 1104, 0);
    Final_ADC3 = (Final_ADC3 / 100) - Setval_ADC3;
    Final_ADC4 = map(Convert4, 8, 17629, 1109, 0);
    Final_ADC4 = (Final_ADC4 / 100) - Setval_ADC4;
    Final_ADC5 = map(Convert5, 8, 17629, 1105, 0);
    Final_ADC5 = (Final_ADC5 / 100) - Setval_ADC5;
    Final_ADC6 = map(Convert6, 12, 17629, 1102, 0);
    Final_ADC6 = (Final_ADC6 / 100) - Setval_ADC6;

    if (tolerance > 0 && tolerance < 10) {

      //-----------------------------Display_Signal_ADC1-----------------------------

      if (tolerance > abs(Final_ADC1) && tolerance != abs(Final_ADC1)) {
        dwinSerial.write(ADC1_PASS, sizeof(ADC1_PASS));
        dwinSerial.write(Selected_Pos1_Green, sizeof(Selected_Pos1_Green));
        Stat_Str1 = "PASS";
      }
      if (tolerance < abs(Final_ADC1)) {
        dwinSerial.write(ADC1_Fail, sizeof(ADC1_Fail));
        dwinSerial.write(Selected_Pos1_Red, sizeof(Selected_Pos1_Red));
        Stat_Str1 = "FAIL";
      }

      //-----------------------------Display_Signal_ADC2-----------------------------


      if (tolerance > abs(Final_ADC2) && tolerance != abs(Final_ADC2)) {
        dwinSerial.write(ADC2_PASS, sizeof(ADC2_PASS));
        dwinSerial.write(Selected_Pos2_Green, sizeof(Selected_Pos2_Green));
        Stat_Str2 = "PASS";
      }
      if (tolerance < abs(Final_ADC2)) {
        dwinSerial.write(ADC2_Fail, sizeof(ADC2_Fail));
        dwinSerial.write(Selected_Pos2_Red, sizeof(Selected_Pos2_Red));
        Stat_Str2 = "FAIL";
      }

      //-----------------------------Display_Signal_ADC3-----------------------------

      if (tolerance > abs(Final_ADC3) && tolerance != abs(Final_ADC3)) {
        dwinSerial.write(ADC3_PASS, sizeof(ADC3_PASS));
        dwinSerial.write(Selected_Pos3_Green, sizeof(Selected_Pos3_Green));
        Stat_Str3 = "PASS";
      }
      if (tolerance < abs(Final_ADC3)) {
        dwinSerial.write(ADC3_Fail, sizeof(ADC3_Fail));
        dwinSerial.write(Selected_Pos3_Red, sizeof(Selected_Pos3_Red));
        Stat_Str3 = "FAIL";
      }

      //-----------------------------Display_Signal_ADC4-----------------------------

      if (tolerance > abs(Final_ADC4) && tolerance != abs(Final_ADC4)) {
        dwinSerial.write(ADC4_PASS, sizeof(ADC4_PASS));
        dwinSerial.write(Selected_Pos4_Green, sizeof(Selected_Pos4_Green));
        Stat_Str4 = "PASS";
      }
      if (tolerance < abs(Final_ADC4)) {
        dwinSerial.write(ADC4_Fail, sizeof(ADC4_Fail));
        dwinSerial.write(Selected_Pos4_Red, sizeof(Selected_Pos4_Red));
        Stat_Str4 = "FAIL";
      }

      //-----------------------------Display_Signal_ADC5-----------------------------

      if (tolerance > abs(Final_ADC5) && tolerance != abs(Final_ADC5)) {
        dwinSerial.write(ADC5_PASS, sizeof(ADC5_PASS));
        dwinSerial.write(Selected_Pos5_Green, sizeof(Selected_Pos5_Green));
        Stat_Str5 = "PASS";
      }
      if (tolerance < abs(Final_ADC5)) {
        dwinSerial.write(ADC5_Fail, sizeof(ADC5_Fail));
        dwinSerial.write(Selected_Pos5_Red, sizeof(Selected_Pos5_Red));
        Stat_Str5 = "FAIL";
      }

      //-----------------------------Display_Signal_ADC6-----------------------------

      if (tolerance > abs(Final_ADC6) && tolerance != abs(Final_ADC6)) {
        dwinSerial.write(ADC6_PASS, sizeof(ADC6_PASS));
        dwinSerial.write(Selected_Pos6_Green, sizeof(Selected_Pos6_Green));
        Stat_Str6 = "PASS";
      }
      if (tolerance < abs(Final_ADC6)) {
        dwinSerial.write(ADC6_Fail, sizeof(ADC6_Fail));
        dwinSerial.write(Selected_Pos6_Red, sizeof(Selected_Pos6_Red));
        Stat_Str6 = "FAIL";
      }
    }
    sendFloatTolerance(tolerance);
    sendFloatADC1(Final_ADC1);
    sendFloatADC2(Final_ADC2);
    sendFloatADC3(Final_ADC3);
    sendFloatADC4(Final_ADC4);
    sendFloatADC5(Final_ADC5);
    sendFloatADC6(Final_ADC6);

    //-----------------------------SD/Pendrive-Storage-----------------------------

    dtostrf(Setval_ADC1, 2, 2, Act1);
    dtostrf(Setval_ADC2, 2, 2, Act2);
    dtostrf(Setval_ADC3, 2, 2, Act3);
    dtostrf(Setval_ADC4, 2, 2, Act4);
    dtostrf(Setval_ADC5, 2, 2, Act5);
    dtostrf(Setval_ADC6, 2, 2, Act6);

    dtostrf(tolerance, 2, 2, Toler);

    dtostrf(Final_ADC1, 2, 2, Devi1);
    dtostrf(Final_ADC2, 2, 2, Devi2);
    dtostrf(Final_ADC3, 2, 2, Devi3);
    dtostrf(Final_ADC4, 2, 2, Devi4);
    dtostrf(Final_ADC5, 2, 2, Devi5);
    dtostrf(Final_ADC6, 2, 2, Devi6);

    ADCTimer = millis();
  }

  //-----------------------------RTC-Date-Sender-----------------------------

  DateTime now = rtc.now();
  sprintf(Disp_Date_Char, "%02u/%02u/%04u", now.day(), now.month(), now.year());
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(strlen(Disp_Date_Char) + 3);
  dwinSerial.write(0x82);
  dwinSerial.write(0x10);
  dwinSerial.write(0x55);
  for (int i = 0; i < strlen(Disp_Date_Char); i++) {
    char c = Disp_Date_Char[i];
    dwinSerial.write(c);
  }

  //-----------------------------RTC-Time-Sender-----------------------------

  sprintf(Disp_Time_Char, "%02u:%02u:%02u", now.hour(), now.minute(), now.second());
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(strlen(Disp_Time_Char) + 3);
  dwinSerial.write(0x82);
  dwinSerial.write(0x10);
  dwinSerial.write(0x65);
  for (int i = 0; i < strlen(Disp_Time_Char); i++) {
    char c = Disp_Time_Char[i];
    dwinSerial.write(c);
  }
}