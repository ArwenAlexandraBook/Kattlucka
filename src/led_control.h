#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#define GREEN_PIN 2
#define RED_PIN 3
#define YELLOW_PIN 8

class LEDControl {
public:
    void initialize();
    void turnOnGreen();
    void turnOffGreen();
    void turnOnRed();
    void turnOffRed();
    void turnOnYellow();
    void turnOffYellow();
};

#endif