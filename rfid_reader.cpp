
#include "rfid_reader.h"
#include <SPI.h>
#include "catflap.h"

#define SS_PIN 5
#define RST_PIN 0 

MFRC522 rfid(SS_PIN,RST_PIN);

MFR522::MIFARE_Key key; 


byte catID[4] = {0}; // Variabbel som lagrar CatID som användaren matar in 

void setup () {
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
}

void initalizeRFIDReader () {
    SPI.begin()
    rfid.PCD_Init()

    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF; 
    }
}
void loop () {
    readCatID();
}

if (!rfid.PICC_IsNewCardPresent())
return;

if (!rfid.PICC_ReadCarSerial())
return;

Serial.print(F("Taggtyp:"));
MFRC522::PICC_TYPE piccType = rfid.PICC_GetType(rfid.uid.sak);
Serial.println(rfid.PICC_GetTypeName(piccType));'
'
if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && 
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Din tagg är inte av typen MIFARE Classic."));
    return;
      }

    Serial.println(F("En ny tagg har uppträckts.")); 

    for (byte i = 0; <4; i++) {
        catID[i] = rfid.uid.uidByte[i];
    }

    Serial println(F("CatID:"));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();

    rfid_PiCC_HaltA();

    rfid.PCD_StopCrypto1();
    }

    void readCatID() {
        Serial.println(F("Ange CatID:")); 
        while (Serial.available() < 4) {
            delay(100);

for (byte i = 0; i < 4; i++) {
    catID[i] = Serial.read();
}
        }
void printHex(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? "0" : " ")
        Serial.print(buffer[i], HEX);
    }
}
    }


