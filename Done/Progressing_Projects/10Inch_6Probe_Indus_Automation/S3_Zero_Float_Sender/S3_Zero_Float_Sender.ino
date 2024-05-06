
#define txPin 6//----------nc
#define rxPin 5
HardwareSerial &dwinSerial = Serial1;

#define Sender_Txd_pin 7
#define Sender_Rxd_pin 8//----------nc
HardwareSerial &Sender = Serial2;

unsigned char incomingData[100];
char receivedFloatArray[50];
float receivedFloat;

void setup() {
  disableCore0WDT(); 
  Serial.begin(115200);  Sender.setTimeout(10); 
  dwinSerial.begin(115200, SERIAL_8N1,rxPin, txPin);
  Sender.begin(115200, SERIAL_8N1, Sender_Rxd_pin, Sender_Txd_pin);
}

void loop() {

  if (dwinSerial.available() > 0 ) {
    int i = 0;
    while (dwinSerial.available() > 0)  // empty the buffer into our array
    {
      char incomingByte = dwinSerial.read();
      incomingData[i] = incomingByte;
      i++;
    }
    incomingData[i+1] = (byte)0xFF;
    if (incomingData[3] == (byte)0x83)  // VP read instruction is in the returned char array
    {
      int k = 7;
      int j = 0;
      while (incomingData[k] != 0xFF) {
        receivedFloatArray[j] = incomingData[k];
        k++;
        j++;
      }
      receivedFloat = atof(receivedFloatArray);
      Sender.println(receivedFloat);
    Serial.print(" Sent Float -> ");   Serial.println(receivedFloat); 
    memset(incomingData, 0, sizeof(incomingData));
    memset(receivedFloatArray, 0, sizeof(receivedFloatArray));
    }
    else{}
    }
}








