#include <Arduino.h>
#include <ctime>
#include <thread>
#include "catflap.h"
#include "rfid_reader.h"

void intializeCatFlap();

int getCurrentHour() {
    
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) {
        Serial.println("Misslyckades att hämta tid");
        return 0;
    }
    return timeinfo.tm_hour;
 }

void app_main()
{
    initializeCatFlap();


while (1) 
{
    const char* CatID = readCatChip();
    processCatChip(CatID);

    int currentHour = getCurrentHour();
    if (flapOpen &&(currentHour < LOCK_START_HOUR || currentHour > LOCK_END_HOUR)) 
    {
        closeCatFlap();
    }
    
    lowBatterysensor();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
}