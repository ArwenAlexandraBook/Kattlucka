#include <Arduino.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "catflap.h"
#include "rfid_reader.h"
#include "led_control.h"

char RegisteredCats[MAX_REGISTERED_CATS][MAX_CAT_ID_LENGTH];
int numRegisteredCats = 0;
time_t flapOpenTime = 0L;

extern int testHour;

RFIDReader* rfidReader;  // Changed to pointer type
LEDControl* ledControl;  // Changed to pointer type

void initializeCatFlap(RFIDReader* reader, LEDControl* leds) {
    rfidReader = reader;
    ledControl = leds;

    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    srand(time(NULL));

    rfidReader->initialize();
    ledControl->initialize();
}

void catFlapTask(void *pvParameters) {
    char catID[MAX_CAT_ID_LENGTH];
    int bufferSize = MAX_CAT_ID_LENGTH;
    int bytesRead = rfidReader->readData(catID, bufferSize);

    if (bytesRead > 0)
    {
        processCatChip(catID);
    }
    else
    {
        Serial.println("Failed to read RFID data");
    }

    lowBatterySensor();
    checkAutoClose();
    userAddCat();
}

void openCatFlap()
{
    Serial.println("Opening catflap");
    ledControl->turnOnGreen();
    flapOpenTime = time(NULL);
}

bool isCatFlapOpen()
{
    return flapOpenTime != 0L;
}

void closeCatFlap()
{
    Serial.println("Closing cat flap");
    ledControl->turnOffGreen();
    flapOpenTime = 0L;
}

bool isRegistered(const char *catID)
{
    for (int i = 0; i < numRegisteredCats; ++i)
    {
        if (strcmp(catID, RegisteredCats[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

void setTime(int hour)
{
    testHour = hour;
}

void processCatChip(const char *catID)
{
    if (isRegistered(catID))
    {
        openCatFlap();
    }
    else
    {
        closeCatFlap();
    }
}

int readBatteryLevel()
{
    return rand() % 101; // Modified this line
}

void lowBatterySensor()
{
    int batteryLevel = readBatteryLevel();
    if (batteryLevel < 10)
    {
        ledControl->turnOnYellow();
    }
    else
    {
        ledControl->turnOffYellow();
    }
}

void checkAutoClose()
{
    if (isCatFlapOpen ())
    {
        time_t currentTime = time(NULL);
        int elapsedTime = difftime(currentTime, flapOpenTime);

        if (elapsedTime >= 20)
        {
            closeCatFlap();
        }
    }
    else
    {
        Serial.println("The catflap closed like it should");
    }
}

void RegisterCat(const char *newCat)
{
    if (numRegisteredCats < MAX_REGISTERED_CATS)
    {
        strncpy(RegisteredCats[numRegisteredCats], newCat, MAX_CAT_ID_LENGTH);
        numRegisteredCats++;
    }
    else
    {
        Serial.println("The maximum amount of registered cats are reached");
    }
}

bool addCatMode = false;

void userAddCat()
{
    if (addCatMode)
    {
        char newCatID[MAX_CAT_ID_LENGTH];
        Serial.println("Add the cat's ID:");
        int newCatIDSize = rfidReader->readData(newCatID, sizeof(newCatID));

        if (newCatIDSize > 0)
        {
            newCatID[newCatIDSize] = '\0';
            RegisterCat(newCatID);
            addCatMode = false;
        }
        else
        {
            Serial.println("Sorry failed to read the new cat ID");
        }
    }
    else
    {
        Serial.println("Not in the add cat mode");
    }
}

void enterAddCatMode()
{
    addCatMode = true;
    Serial.println("In the add cat mode. Please scan the cat's RFiD tag to add it to the system");
}

void resetCatFlap()
{
    flapOpenTime = 0L;
}