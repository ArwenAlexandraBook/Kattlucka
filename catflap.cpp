#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "catflap.h"
#include "rfid_reader.h"

std::vector<std::string> approvedCats;
time_t flapOpenTime = 0;

void initializeCatflap()
{
    initializeRFIDReader();
}

void openCatFlap()
{
    
        turnOnGreenLED();
        flapOpenTime = time(NULL);
}        
    

    void closeCatFlap()
    {

            turnOnRedLED();
            flapOpenTime = 0;
    }


void processCatChip(const std::string& catID)
{
    if (isApproved(catID))
    {
        openCatFlap();
    }
    else
    {
        closeCatFlap();
    }
}

void addApprovedCat(const std::string& catID)
{
    if (approvedCats.size() < MAX_APPROVED_CATS)
    {
        approvedCats.push_back(catID);
    }
}

    bool isApproved(const std::string& catID)
    {
        for (const auto& cat : approvedCats)
        {
            if (cat == catID) 
            {
            return true;
        }
    }
    return false;
}

void catFlapTask(void *pvParameters)
{
    try
    {
    while (true)
    {
        const std::string catID = readCatChip();
        processCatChip(catID);

        const std::string rfidData = readRFIDData();
        processRFIDData(rfidData);
    }
    }
    catch (const std::exception& e) {
        std::cerr <<"Ett fel uppstod: " <<e.what() << std::endl;
    }
}

int batteryLevel = 100;

void lowBatterysensor()
{
    if (batteryLevel < 10) 
    {
        turnOnLowBatteryLED();
    }
    else
    {
        turnOffLowBatteryLED();
    }
}

void checkAutoClose()
{
    if (flapOpenTime != 0)
    {
        time_t currentTime = time(NULL);
        int elapsedTime = difftime(currentTime, flapOpenTime);

        if (elapsedTime >= 20)
        {
            closeCatFlap();
        }
    }
}

void userAddCat()
{
    std::string newCatID;
   std::cout << "Enter the cat ID to add it: ";
    std::cin >> newCatID;

    if (newCatID.lenght() == MAX_CAT_ID_LENGHT) {
        addApprovedCat(newCatID);
     } else {
        std::cerr << "The cat ID is invald. Please enter a valid ID" << std::endl;

    }
}
