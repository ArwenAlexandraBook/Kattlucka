#include <Arduino.h>
#include "rfid_reader.h"
#include "MFRC522.h"
#include "SPI.h"

MFRC522RFIDReader::MFRC522RFIDReader(MFRC522& mfrc522) : mfrc522(mfrc522) {}

void MFRC522RFIDReader::initialize() {
    SPI.begin();
    mfrc522.PCD_Init();
    // Serial.begin(115200);
}

int MFRC522RFIDReader::readData(char *data, int bufferSize) {
    if (data == NULL || bufferSize <= 0) {
        Serial.println("Ogiltlig buffer");
        return 0;
    }
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
    {
        int dataSize = mfrc522.uid.size;  // Hämtar storleken på RFID-data
        if(dataSize > bufferSize - 1) {
            dataSize = bufferSize -1;
        }
        for (byte i = 0; i < dataSize; i++)
        {
            data[i] = mfrc522.uid.uidByte[i];
        }
        data [dataSize] = '\0';

        // Skriver ut RFID-data för testing
        Serial.print("RFID data: ");
        for (byte i = 0; i < dataSize; i++)
        {
            Serial.print(data[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        mfrc522.PICC_HaltA();

        return dataSize;
    }
    return 0;
}
