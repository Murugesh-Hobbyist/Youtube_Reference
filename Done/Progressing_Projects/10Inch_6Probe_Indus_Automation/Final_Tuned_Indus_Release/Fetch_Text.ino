
//-------------------------------------------------------------fetchText-----------------------------------------------------------------------------

void Fetch_Text() {

  if (dwinSerial.available() > 0) {
    Collect = dwinSerial.readString();
    receivedFloat = atof(Collect.c_str());
    dwinSerial.write(Tolerance_Write, sizeof(Tolerance_Write));
    if (receivedFloat == 0) {
      if (Start_Once >= 1) { check = receivedFloat; }
      if (Start_Once < 1) {
        sendFloatActual_ADC1(Setval_ADC1);
        sendFloatActual_ADC2(Setval_ADC2);
        sendFloatActual_ADC3(Setval_ADC3);
        sendFloatActual_ADC4(Setval_ADC4);
        sendFloatActual_ADC5(Setval_ADC5);
        sendFloatActual_ADC6(Setval_ADC6);
        Start_Once++;
      }
    }
    if (receivedFloat > 0 && receivedFloat < 10) {
      tolerance = receivedFloat;
      Save_Library.begin("Storage", false);
      Save_Library.putFloat("Tolerance_Save", tolerance);
      delay(10);
      Save_Library.end();
      Serial.print("tolerance Saved! -> ");
      Serial.println(tolerance);
    }

    if (receivedFloat > 10) {
    }
    Serial.print("Received float -> ");
    Serial.println(receivedFloat, 2);
  } else {
  }
}