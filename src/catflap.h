#ifndef CATFLAP_H
#define CATFLAP_H

#include "rfid_reader.h"
#include "led_control.h"

#define MAX_REGISTERED_CATS 10
#define MAX_CAT_ID_LENGTH 20

extern RFIDReader* rfidReader;
extern LEDControl* ledControl;

void initializeCatFlap(RFIDReader* reader, LEDControl* leds);
void openCatFlap();
bool isCatFlapOpen();
void closeCatFlap();
bool isRegistered(const char *catID);
void setTime(int hour);
void processCatChip(const char *catID);
void catFlapTask(void *pvParameters);
int readBatteryLevel();
void lowBatterySensor();
void checkAutoClose();
void RegisterCat(const char *newCat);
void userAddCat();
void enterAddCatMode();
void resetCatFlap();

#endif // CATFLAP_H