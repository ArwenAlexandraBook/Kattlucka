#ifndef ESP32_H
#define ESP32_H

void ESPinit(void); // Initierar ESP32
void waitFor (char* response); // Väntar på svar från ESP32
void addData(char* name, int data);
void pushData(void); //Skickar datafrån ESP32
void ping(void) // Testar anslutningen till ESP32

#endif /*ESP32_H*/