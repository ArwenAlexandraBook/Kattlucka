#include <Arduino.h>
#include <time.h>
#include "esp32wifi.h"
#include "catflap.h"
#include "rfid_reader.h"  
#include "led_control.h"

// NTP-server och tidszoninställningar
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 0;

// Kattluckan är låst mellan 22-06:00
const int LOCK_START_HOUR = 22;
const int LOCK_END_HOUR = 6;

int testHour = -1;


void setup()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        if (millis() - startTime > 1000)
        {
            Serial.println("Misslyckades med att koppla upp till WIFI");
            startTime = millis();
        }
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Ansluten till WIFI");

    // Konfigurerar tiden från NTP 
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    initializeCatFlap(rfidReader, ledControl); 
}
// Funktion för att få den aktuella tiden
int getCurrentHour()
{
    if (testHour != -1)
    {
        return testHour;
    }

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Misslyckades med att kolla tiden");
        return -1;
    }
    return timeinfo.tm_hour;
}
// Så kattluckan förblir stängd mellan 06-22:00 då den ska vara låst. 
void loop()
{
    catFlapTask(NULL);  

    int currentHour = getCurrentHour();
    if ((currentHour >= LOCK_START_HOUR && currentHour < LOCK_END_HOUR))
    {
        closeCatFlap();
    }
    delay(200);
}
