#ifndef RFID_READER_H
#define RFID_READER_H

class RFIDReader {
public:
    virtual void initialize() = 0;
    virtual int readData(char *data, int bufferSize) = 0;
};

class MFRC522RFIDReader : public RFIDReader {
public:
    MFRC522RFIDReader();
    void initialize() override;
    int readData(char *data, int bufferSize) override;
};

#endif // RFID_READER_H