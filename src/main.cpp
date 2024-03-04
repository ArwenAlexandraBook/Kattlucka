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
            Serial.println("Failed to connect to wifi, retrying");
            startTime = millis();
        }
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Wifi is connected");

    // Konfigurerar tiden från NTP 
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    initializeCatFlap(rfidReader, ledControl); // Pass the pointers to initializeCatFlap
}

int getCurrentHour()
{
    if (testHour != -1)
    {
        return testHour;
    }

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to get the current time");
        return -1;
    }
    return timeinfo.tm_hour;
}

void loop()
{
    catFlapTask(NULL);  // Call catFlapTask instead of the previous code

    int currentHour = getCurrentHour();
    if ((currentHour >= LOCK_START_HOUR && currentHour < LOCK_END_HOUR))
    {
        closeCatFlap();
    }
    delay(200);
}