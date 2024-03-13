#ifndef LED_CONTROL_H
#define LED_CONTROL_H

// GPIO pins för LED-lamporna
#define GREEN_PIN 12 
#define RED_PIN 32
#define YELLOW_PIN 33

class LEDControl {
public:
    void initialize();
    void turnOnGreen();
    void checkGreen(); 
    void turnOffGreen();
    void turnOnRed();
    void checkRed(); 
    void turnOffRed();
    void turnOnYellow();
    void checkYellow(); 
    void turnOffYellow();

private:
    unsigned long greenStartTime; 
    unsigned long redStartTime;
    unsigned long yellowStartTime; 
};

#endif
