#ifndef RFID_READER_H
#define RFID_READER_H 


#define RFID_DATA_LENGHT 50
void initRFID();
const char* readRFIDData();
bool isRFIDDataValid(const char* data);

#endif 