#ifndef UWV_H
#define UWV_H



class UWV
{
    private:
        int joystickXPin;
        int joystickYPin;
        int armSwitchPin;
        int modeSwitchPin;
        int minUwvSpeed;
        int maxUwvSpeed;
        int maxRudderAngleLeft;
        int maxRudderAngleRight;
        unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
        unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
        int ledState = 1;                    // the current state of the output pin
        int buttonState;                     // the current reading from the input pin
        int lastButtonState = 0;             // the previous reading from the input pin

    public:
        bool armState = false;        
        UWV();
        void init();
        int readSpeed();
        int readRudder();
        int readArmState();
        int readModeState();


};



#endif