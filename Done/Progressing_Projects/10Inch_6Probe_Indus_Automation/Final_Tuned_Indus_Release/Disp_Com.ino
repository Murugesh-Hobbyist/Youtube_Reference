

//----------------------------------------------------------FloatToHex-----------------------------------------------------------------------------

void FloatToHex(float f, byte* hex) {
  byte* f_byte = reinterpret_cast<byte*>(&f);
  memcpy(hex, f_byte, 4);
}

//------------------------------------------------------sendFloatTolerance-----------------------------------------------------------------------------

void sendFloatTolerance(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x10);
  dwinSerial.write((byte)0x50);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}

//---------------------------------------------------------sendFloatADC1-----------------------------------------------------------------------------

void sendFloatADC1(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x00);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
                                 //  Serial.println((byte)0x00);Serial.println(hex[3]);Serial.println(hex[2]);Serial.println(hex[1]);Serial.println(hex[0]);Serial.println("-----------------------");
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}

//---------------------------------------------------------sendFloatADC2-----------------------------------------------------------------------------

void sendFloatADC2(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x05);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}


//---------------------------------------------------------sendFloatADC3-----------------------------------------------------------------------------

void sendFloatADC3(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x10);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}


//---------------------------------------------------------sendFloatADC4-----------------------------------------------------------------------------

void sendFloatADC4(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x15);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}


//---------------------------------------------------------sendFloatADC5-----------------------------------------------------------------------------

void sendFloatADC5(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x20);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}


//---------------------------------------------------------sendFloatADC6-----------------------------------------------------------------------------

void sendFloatADC6(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x25);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}


//---------------------------------------------------------sendFloatActual_ADC1-----------------------------------------------------------------------------

void sendFloatActual_ADC1(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x50);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}

//---------------------------------------------------------sendFloatActual_ADC2-----------------------------------------------------------------------------

void sendFloatActual_ADC2(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x55);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}


//---------------------------------------------------------sendFloatActual_ADC3-----------------------------------------------------------------------------

void sendFloatActual_ADC3(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x60);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}


//---------------------------------------------------------sendFloatActual_ADC4-----------------------------------------------------------------------------

void sendFloatActual_ADC4(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x65);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}

//---------------------------------------------------------sendFloatActual_ADC5-----------------------------------------------------------------------------

void sendFloatActual_ADC5(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x70);  // Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}


//---------------------------------------------------------sendFloatActual_ADC6-----------------------------------------------------------------------------

void sendFloatActual_ADC6(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x11);
  dwinSerial.write((byte)0x75);  //  Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}

//---------------------------------------------------------sendFloatShiftCount-----------------------------------------------------------------------------

void sendFloatShiftCount(float floatValue) {
  dwinSerial.write(0x5A);
  dwinSerial.write(0xA5);
  dwinSerial.write(0x07);
  dwinSerial.write(0x82);
  dwinSerial.write(0x64);
  dwinSerial.write((byte)0x82);  //  Write address
  byte hex[4] = { 0 };           // create a hex array for the 4 bytes
  FloatToHex(floatValue, hex);   // convert the float to hex array
  dwinSerial.write(hex[3]);      // The order is flipped (endiannes)
  dwinSerial.write(hex[2]);
  dwinSerial.write(hex[1]);
  dwinSerial.write(hex[0]);
}