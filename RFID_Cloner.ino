#include <MFRC522Extended.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <require_cpp11.h>

#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

LiquidCrystal lcd(9, 10, 5, 6, 7, 8);

File root;

void setup() {
  
  lcd.begin(16, 2);
  SD.begin(4);
  pinMode(A0, INPUT); //brute force button
  pinMode(A1, INPUT); //emit button
  pinMode(A2. INPUT); //read button
  pinMode(A3, INPUT); //up button
  pinMode(A4, INPUT); //down button
  pinMode(A5, INPUT); //delete button
  root = SD.open("/");
  root.rewindDirectory();
  counter = 0;

  lcd.print("Hello!");

  //read list of saved codes, store in array, print 2 top array entries to LCD. Chooses two array entries as current.

  while(true) {
    File currentFile = root.openNextFile();

    if (!currentFile) {
      break;
    }
    counter++;
  }
  
  root.rewindDirectory();
  String savedFiles = [counter];
  
  for(int i = 0; i < counter; i++) {
    currentFile = root.openNextFile();

    while(currentFile.available() > 0) {
      currentChar = currentFile.read();
      savedFiles[i] = savedFiles[i].concat(currentChar);
    }
  }

  int currentPos = 0;
  int nextPos = 1;

  lcd.print(savedFiles[currentPos]);
  lcd.setCursor(0,1);
  lcd.print(savedFiles[nextPos]);
}

void loop() {

  //read buttons, all buttons have an on/off state variable. Only one button can be on at once.

  boolean brutbtn = digitalRead(A0);
  boolean upbtn = digitalRead(A1);
  boolean downbtn = digitalRead(A2);
  boolean emitbtn = digitalRead(A3);
  boolean readbtn = digitalRead(A4);
  boolean deletebtn = digitalRead(A5);

  //brute force -- exhausts entire hexadecimal 8-digit keyspace starting from 00000000, can exit by pressing down

  if(brutbtn == 1) {
    
  }

  //up -- scrolls up list of saved codes. Chooses two of array entries as current. Current entries displayed on LCD. Only scrolls up if current entry greater than 0.
  //down

  if(upbtn == 1) {
    if(currentPos > 0) {
      currentPos--;
      nextPos--;
      lcd.print(savedFiles[currentPos]);
      lcd.setCursor(0,1);
      lcd.print(savedFiles[nextPos]);
    }
  }

  if(downbtn == 1) {
    if(nextPos < counter) {
      currentPos++;
      nextPos++;
      lcd.print(savedFiles[currentPos]);
      lcd.setCursor(0,1);
      lcd.print(savedFiles[nextPos]);
    }
  }

  //emit -- emits currently selected code, which is the 1st current code. Prints to screen "emitting {current}"

  //read -- reads signal, if signal received and good, saved into bottom of array.

  mfrc522.PICC_IsNewCardPresent()
  mfrc522.PICC_ReadCardSerial()

  Serial.print(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

  //delete -- deletes currently selected code. Asks for confirmation.
  if(deletebtn == 1) {
    int deletePos = currentPos;
    root.rewindDirectory();

    for(int i = 0; i <= deletePos; i++) {
      currentFile = root.openNextFile();
    }
    String currentName = currentFile.name();
    SD.remove(currentName);

    counter = 0;

    while(true) {
    File currentFile = root.openNextFile();

    if (!currentFile) {
      break;
    }
    counter++;
  }
  
  root.rewindDirectory();
  String savedFiles = [counter];
  
  for(int i = 0; i < counter; i++) {
    currentFile = root.openNextFile();

    while(currentFile.available() > 0) {
      currentChar = currentFile.read();
      savedFiles[i] = savedFiles[i].concat(currentChar);
    }
  }

  int currentPos = 0;
  int nextPos = 1;

  lcd.print(savedFiles[currentPos]);
  lcd.setCursor(0,1);
  lcd.print(savedFiles[nextPos]);
  }
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
