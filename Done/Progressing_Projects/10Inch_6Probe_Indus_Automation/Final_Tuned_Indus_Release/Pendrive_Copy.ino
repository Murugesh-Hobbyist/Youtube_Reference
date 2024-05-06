
void printInfo(const char info[]) {

  int infoLength = strlen(info);
  if (infoLength > 40) {
    infoLength = 40;
  }
  Serial.print(F("\n\n"));
  for (int a = 0; a < infoLength; a++) {
    Serial.print('*');
  }
  Serial.println();
  Serial.println(info);
  for (int a = 0; a < infoLength; a++) {
    Serial.print('*');
  }
  Serial.print(F("\n\n"));
}

//--------------------------------------------------Void_Pendrive-----------------------------------------------------------------------------

void Pendrive_Copy() {
  if (flashDrive.checkIntMessage()) {
    if (flashDrive.getDeviceStatus()) {
      Serial.println(F("Flash drive attached!"));
    } else {
      Serial.println(F("Flash drive detached!"));
    }
  }

  Fetch_Text();

    if ((receivedFloat == 66) && !flashDrive.driveReady()) {
      printInfo("Attach flash drive first!");
      dwinSerial.write(Pass_Page15, sizeof(Pass_Page15));
      delay(1500);
    dwinSerial.write(Pass_Page1, sizeof(Pass_Page1));
      receivedFloat = 99;
    }

  if ((receivedFloat == 66) && (flashDrive.driveReady())) {

        Serial.println("Pendrive Attached & Copying Data");
        dwinSerial.write(Pass_Page13, sizeof(Pass_Page13));
    readFile(SD, "/Machine_Log.txt");
        delay(100);
        int startIndex = 0;

    for (int i = 0; i < we.length(); i++) {

      if (we[i] == delimiter) {

        String substring = we.substring(startIndex, i);
        substring.toCharArray(Row_Buffer, substring.length() + 1);
        Serial.println(substring);

        printInfo("Append data to file: LOG.TXT");
        flashDrive.setFileName("LOG.TXT");

        if (flashDrive.openFile() == ANSW_USB_INT_SUCCESS) {
          flashDrive.moveCursor(CURSOREND);
        }

        for (int a = 0; a < 1; a++) {
          if (flashDrive.getFreeSectors()) {
            flashDrive.writeFile(Row_Buffer, strlen(Row_Buffer));
          } else {
            printInfo("Disk full");
          }
        }

        flashDrive.closeFile();  //at the end, close the file
        printInfo("Done!");
        startIndex = i + 1;
      }
    }

    String lastSubstring = we.substring(startIndex);
    Serial.println(lastSubstring);
    dwinSerial.write(Pass_Page14, sizeof(Pass_Page14));
    delay(3000);
    dwinSerial.write(Pass_Page1, sizeof(Pass_Page1));
    receivedFloat = 99;
    delay(1000);
  }

}




  /*
  if (Serial.available()) {
    tmpCommand = Serial.read();                                                  //read incoming bytes from the serial monitor
    if (((tmpCommand > 48) && (tmpCommand < 58)) && !flashDrive.driveReady()) {  // if the data is ASCII 1 - 9 and no flash drive are attached
      printInfo("Attach flash drive first!");
      tmpCommand = 10;  // change the command byte
    }
    switch (tmpCommand) {

      case 49:                                                             //1
        printInfo("COMMAND1: Create and write data to file : Machine_Log.txt");  // Create a file called Machine_Log.txt
        flashDrive.setFileName("Machine_Log.txt");                               //set the file name
        flashDrive.openFile();                                             //open the file

        for (int a = 0; a < 20; a++) {                           //write text from string(Row_Buffer) to flash drive 20 times
          flashDrive.writeFile(Row_Buffer, strlen(Row_Buffer));  //string, string length
        }
        flashDrive.closeFile();  //at the end, close the file
        printInfo("Done!");
        break;

        //*****************************************************************************************************************************************************
      case 50:  //2
        we.toCharArray(Row_Buffer, we.length());
        printInfo("COMMAND2: Append data to file: Machine_Log.txt");  // Append data to the end of the file.
        flashDrive.setFileName("Machine_Log.txt");                    //set the file name
        if (flashDrive.openFile() == ANSW_USB_INT_SUCCESS) {    //open the file
          flashDrive.moveCursor(CURSOREND);                     //if the file exist, move the "virtual" cursor at end of the file, with CURSORBEGIN we actually rewrite our old file
                                                                //flashDrive.moveCursor(flashDrive.getFileSize()); // is almost the same as CURSOREND, because we put our cursor at end of the file
        }
        for (int a = 0; a < 2; a++) {                              //write text from string(Row_Buffer) to flash drive 20 times
          if (flashDrive.getFreeSectors()) {                       //check the free space on the drive
            flashDrive.writeFile(Row_Buffer, strlen(Row_Buffer));  //string, string length
          } else {
            printInfo("Disk full");
          }
        }
        flashDrive.closeFile();  //at the end, close the file
        printInfo("Done!");
        break;

        //*****************************************************************************************************************************************************
      case 51:                                        //3
        printInfo("COMMAND3: Read File: Machine_Log.txt");  // Read the contents of this file on the USB disk, and display contents in the Serial Monitor
        flashDrive.setFileName("Machine_Log.txt");          //set the file name
        flashDrive.openFile();                        //open the file
        readMore = true;
        //read data from flash drive until we reach EOF
        while (readMore) {  // our temporary buffer where we read data from flash drive and the size of that buffer
          readMore = flashDrive.readFile(Read_Buffer, sizeof(Read_Buffer));
          Serial.print(Read_Buffer);  //print the contents of the temporary buffer
        }
        flashDrive.closeFile();  //at the end, close the file
        printInfo("Done!");
        break;

        //*****************************************************************************************************************************************************
      case 54:                                          //6
        printInfo("COMMAND6: Delete File: Machine_Log.txt");  // Delete the file named Machine_Log.txt
        flashDrive.setFileName("Machine_Log.txt");            //set the file name
        flashDrive.deleteFile();                        //delete file
        printInfo("Done!");
        break;

        //*****************************************************************************************************************************************************
      case 57:  //9
        switch (flashDrive.cd("/Prod_Data/", 1)) {
          case CH376_ERR_LONGFILENAME:  //0x01
            Serial.println(F("Directory name is too long"));
            break;

          case ANSW_USB_INT_SUCCESS:  //0x14
            Serial.println(F("Directory created successfully"));
            break;

          case ANSW_ERR_OPEN_DIR:  //0x41
            Serial.println(F("Directory opened successfully"));
            break;

          case ANSW_ERR_MISS_FILE:  //0x42
            Serial.println(F("Directory doesn't exist"));
            break;

          case ANSW_ERR_FOUND_NAME:  //0x43
            Serial.println(F("File exist with the given name"));
            break;

          default:

            break;
        }
        break;
        //*****************************************************************************************************************************************************
      case 104:  //h
        printInfo(helpString);
        break;
      default:
        break;
    }
  }*/
