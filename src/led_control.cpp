#include <Arduino.h>
#include "led_control.h"

void LEDControl::initialize() {
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(RED_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
}

void LEDControl::turnOnGreen() {
    digitalWrite(GREEN_PIN, HIGH);
    Serial.println("Grön LED lyser");
    greenStartTime = millis();
}

void LEDControl::checkGreen() {
    if (millis() - greenStartTime >= 15000) {
        turnOffGreen();
    }
}

void LEDControl::turnOffGreen() {
    digitalWrite(GREEN_PIN, LOW);
    Serial.println("Grön LED är släckt och luckan är stängd");
}

void LEDControl::turnOnRed() {
    digitalWrite(RED_PIN, HIGH);
    Serial.println("Röd LED, lyser luckan är stängd);
    redStartTime = millis();
}

void LEDControl::checkRed() {
    if (millis() - redStartTime >= 2000) {
        Serial.println("Röd LED har släckts var god och prova igen");
        turnOffRed();
    }
}
