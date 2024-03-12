/*
 * -----------------------------------------------------------------------------------------
 *             MFRC522      ESP32
 *             Reader/PCD   
 * Signal      Pin          Pin           
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST         GPIO22            
 * SPI SS      SDA(SS)     GPIO21            
 * SPI MOSI    MOSI        GPIO23            
 * SPI MISO    MISO        GPIO19            
 * SPI SCK     SCK         GPIO18
 * GND         GND         GND            
 * -----------------------------------------------------------------------------------------
 */

#ifndef RFID_READER_H
#define RFID_READER_H

#include "MFRC522.h"

class MFRC522RFIDReader {
public:
    MFRC522RFIDReader(MFRC522& mfrc522);
    void initialize();
    int readData(char *data, int bufferSize);

private:
    MFRC522& mfrc522;
};

#endif // RFID_READER_H
