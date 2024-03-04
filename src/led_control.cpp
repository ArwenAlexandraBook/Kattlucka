#include <Arduino.h>
#include "led_control.h"

void LEDControl::initialize() {
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(RED_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
}

void LEDControl::turnOnGreen() {
    digitalWrite(GREEN_PIN, HIGH);
    Serial.println("THE Green LED is on");
    delay(15000); // Green LED is on for 15 seconds when the flap is open. 
}

void LEDControl::turnOffGreen() {
    digitalWrite(GREEN_PIN, LOW);
    Serial.println("The Green LED is off and the flap is closed");
}

void LEDControl::turnOnRed() {
    digitalWrite(RED_PIN, HIGH);
    Serial.println("Red LED is on. Failed to open the flap");
    delay(2000);
    Serial.println("The red LED is off. Please try again");
    turnOffRed();
}

void LEDControl::turnOffRed() {
    digitalWrite(RED_PIN, LOW);
}

void LEDControl::turnOnYellow() {
    digitalWrite(YELLOW_PIN, HIGH);
    Serial.println("Yellow LED is on check the battery level");
    delay(5000);
}

void LEDControl::turnOffYellow() {
    digitalWrite(YELLOW_PIN, LOW);
    Serial.println("The yellow LED is off. Battery level has been checked");
}