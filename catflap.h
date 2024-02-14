#ifndef CATFLAP_H
#define CATFLAP_H

#include <string.h>
#include <ctime>

#define MAX_APPROVED_CATS 5
#define MAX_CAT_ID_LENGTH 10

extern const int LOCK_START_HOUR;
extern const int LOCK_END_HOUR;


#define GREEN_PIN 2
#define RED_PIN 3
#define YELLOW_PIN 4
#define LOW_BATTERY_PIN 8


    void initializeCatFlap(); 

    void openCatFlap();

    void closeCatFlap();

    void processCatFlap();

    void processCatChip(const std::string& catID);

    void addApprovedCat(const std::string& catID);

    void isApproved(const std::string& catID);

    void lowBatterySensor();
    
    void userAddCat(); // En funktion som ger användaten möjlighet att lägga till en katt.

    #endif

