/*
 Name:		JarmonMeisseli.ino
 Created:	9/14/2016 9:31:32 AM
 Author:	pusan
*/

#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

long currentTag = 0;


void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }
    long t = 0;
    t += mfrc522.uid.uidByte[0];
    t += mfrc522.uid.uidByte[1];
    t += mfrc522.uid.uidByte[2];
    t += mfrc522.uid.uidByte[3];
    if (currentTag == 0) {
      Leimaa(t);
      delay(500);
    } else {
      if (currentTag == t) {
        PoistaNykyinenLeimaus();    
        delay(500);  
      } else {
        PoistaNykyinenLeimaus();
        Leimaa(t);
        delay(500);
      }
    }
}

void Leimaa(long t) {
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  currentTag = t;
}

void PoistaNykyinenLeimaus() {
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  currentTag = 0;
}


