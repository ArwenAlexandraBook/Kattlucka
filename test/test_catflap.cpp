#include <gtest/gtest.h>
#include <cstring>
#include "catflap.h"
#include "rfid_reader.h"
#include "led_control.h"

class TestRFIDReader : public RFIDReader {
public:
    void initialize() override {}
    int readData(char *buffer, int bufferSize) override {
        const char* mockData = "mock RFID data";
        int dataSize = strlen(mockData);
        if(dataSize > bufferSize - 1) {
            dataSize = bufferSize -1;
        }
        strncpy(buffer, mockData, dataSize);
        buffer[dataSize] = '\0';
        return dataSize;
    }
};

class TestLEDControl : public LEDControl {
public:
};

class CatFlapTest: public testing::Test 
{
protected:
    TestRFIDReader rfidReader;
    TestLEDControl ledControl;

    void SetUp() override
    {
        initializeCatFlap(&rfidReader, &ledControl);
        resetCatFlap();  
    }
};

TEST_F(CatFlapTest, TestifflapOpenswithaValidID)
{
    RegisterCat("valid_id");
    processCatChip("valid_id");
    ASSERT_TRUE(isCatFlapOpen());
}

TEST_F(CatFlapTest, TestifflapCloseswithInvalidID)
{
    processCatChip("invalid_id");
    ASSERT_FALSE(isCatFlapOpen());
}

TEST_F(CatFlapTest, TestifflapCloseswithNoID)
{
    processCatChip("");
    ASSERT_FALSE(isCatFlapOpen());
}

TEST_F(CatFlapTest, TestifflapOpenswithAnotherValidID)
{
    RegisterCat("another_valid_id");
    processCatChip("another_valid_id");
    ASSERT_TRUE(isCatFlapOpen());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}