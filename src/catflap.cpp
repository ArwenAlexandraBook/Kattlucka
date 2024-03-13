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

RFIDReader* rfidReader;  
LEDControl* ledControl;  

void initializeCatFlap(RFIDReader* reader, LEDControl* leds) {
    rfidReader = reader;
    ledControl = leds;

    Serial.begin(9600);
    while (!Serial) {
        ; 
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
        Serial.println("Misslyckades att läsa RFID data");
    }

    lowBatterySensor();
    checkAutoClose();
    userAddCat();
}

void openCatFlap()
{
    Serial.println("Öppnar kattluckan");
    ledControl->turnOnGreen();
    flapOpenTime = time(NULL);
}

bool isCatFlapOpen()
{
    return flapOpenTime != 0L;
}

void closeCatFlap()
{
    Serial.println("Stänger kattluckan");
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
    return rand() % 101; 
}

void lowBatterySensor()  // Funktion för att se över batterinivån värdet ovan är för testningssyfte.
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
        Serial.println("Kattluckan är stängd");
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
            Serial.println("Misslyckades med att lägga till nytt ID");
        }
    }
    else
    {
        Serial.println("Inte i add cat mode");
    }
}

void enterAddCatMode()
{
    addCatMode = true;
    Serial.println("I add cat mode. Snälla scanna kattens RFID-tag för att lägga till den");
}

void resetCatFlap()
{
    flapOpenTime = 0L;
}
