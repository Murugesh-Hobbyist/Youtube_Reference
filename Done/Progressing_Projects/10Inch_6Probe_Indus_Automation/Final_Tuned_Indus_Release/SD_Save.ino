

/*
    listDir(SD, "/", 0);
    createDir(SD, "/mydir");
    listDir(SD, "/", 0);
    removeDir(SD, "/mydir");
    listDir(SD, "/", 2);
    writeFile(SD, "/Machine_Log.txt", "Hello ");
    appendFile(SD, "/Machine_Log.txt", "World!\n");
    readFile(SD, "/Machine_Log.txt");
    deleteFile(SD, "/foo.txt");
    renameFile(SD, "/Machine_Log.txt", "/foo.txt");
    readFile(SD, "/foo.txt");
    testFileIO(SD, "/test.txt");
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
    */


//--------------------------------------------------Void_SD_Save-----------------------------------------------------------------------------

void SD_Save() {

    DateTime now = rtc.now();
    sprintf(Disp_Date_Char, "%02u/%02u/%04u", now.day(), now.month(), now.year());
    appendFile(SD, "/Machine_Log.txt", Disp_Date_Char);
    appendFile(SD, "/Machine_Log.txt", " ");
    sprintf(Disp_Time_Char, "%02u:%02u:%02u", now.hour(), now.minute(), now.second());
    appendFile(SD, "/Machine_Log.txt", Disp_Time_Char);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", User_Map1);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", True_Map1);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", User_Map2);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", True_Map2);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", User_Map3);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", True_Map3);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", User_Map4);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", True_Map4);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", User_Map5);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", True_Map5);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", User_Map6);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", True_Map6);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Act1);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Act2);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Act3);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Act4);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Act5);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Act6);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Toler);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Devi1);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Devi2);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Devi3);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Devi4);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Devi5);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", Devi6);
    appendFile(SD, "/Machine_Log.txt", " ");
    Stat_Str1.toCharArray(Stat1_Char, Stat_Str1.length() + 1);
    appendFile(SD, "/Machine_Log.txt", Stat1_Char);
    appendFile(SD, "/Machine_Log.txt", " ");
    Stat_Str2.toCharArray(Stat2_Char, Stat_Str2.length() + 1);
    appendFile(SD, "/Machine_Log.txt", Stat2_Char);
    appendFile(SD, "/Machine_Log.txt", " ");
    Stat_Str3.toCharArray(Stat3_Char, Stat_Str3.length() + 1);
    appendFile(SD, "/Machine_Log.txt", Stat3_Char);
    appendFile(SD, "/Machine_Log.txt", " ");
    Stat_Str4.toCharArray(Stat4_Char, Stat_Str4.length() + 1);
    appendFile(SD, "/Machine_Log.txt", Stat4_Char);
    appendFile(SD, "/Machine_Log.txt", " ");
    Stat_Str5.toCharArray(Stat5_Char, Stat_Str5.length() + 1);
    appendFile(SD, "/Machine_Log.txt", Stat5_Char);
    appendFile(SD, "/Machine_Log.txt", " ");
    Stat_Str6.toCharArray(Stat6_Char, Stat_Str6.length() + 1);
    appendFile(SD, "/Machine_Log.txt", Stat6_Char);
    appendFile(SD, "/Machine_Log.txt", " ");
    //appendFile(SD, "/Machine_Log.txt", OK_Count);
    //appendFile(SD, "/Machine_Log.txt", " ");
    OK_Count_Str.toCharArray(Ok_Count_Char, OK_Count_Str.length() + 1);
    appendFile(SD, "/Machine_Log.txt", Ok_Count_Char);
    appendFile(SD, "/Machine_Log.txt", " ");
    appendFile(SD, "/Machine_Log.txt", "; \n");
    readFile(SD, "/Machine_Log.txt");
    Serial.println(we);
    delay(1000);
    
}


//--------------------------------------------------------------listDir---------------------------------------------------------------

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}


//--------------------------------------------------------------createDir---------------------------------------------------------------


void createDir(fs::FS &fs, const char *path) {
  Serial.printf("Creating Dir: %s\n", path);
  if (fs.mkdir(path)) {
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

//--------------------------------------------------------------removeDir---------------------------------------------------------------

void removeDir(fs::FS &fs, const char *path) {
  Serial.printf("Removing Dir: %s\n", path);
  if (fs.rmdir(path)) {
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}


//--------------------------------------------------------------readFile---------------------------------------------------------------


void readFile(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  we = "";
  while (file.available()) {
    //Serial.write(file.read());
    q = file.read();
    we.concat(q);
  }
  file.close();
}

//--------------------------------------------------------------writeFile---------------------------------------------------------------

void writeFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

//--------------------------------------------------------------appendFile---------------------------------------------------------------

void appendFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

//--------------------------------------------------------------deleteFile---------------------------------------------------------------

void deleteFile(fs::FS &fs, const char *path) {
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}
