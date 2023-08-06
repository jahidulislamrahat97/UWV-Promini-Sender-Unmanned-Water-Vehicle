#include "UWV.h"

#include "Config.h"

UWV::UWV()
{
    this->joystickXPin = JOYSTICK_X_SPEED_PIN;
    this->joystickYPin = JOYSTICK_Y_RUDDER_PIN;
    this->armSwitchPin = ARM_SWITCH_PIN;
    this->modeSwitchPin = MODE_SWITCH_PIN;
    this->maxUwvSpeed = MAX_UWV_SPEED;
    this->minUwvSpeed = MIN_UWV_SPEED;
    this->maxRudderAngleLeft = MAX_RUDDER_ANGLE_LEFT;
    this->maxRudderAngleRight = MAX_RUDDER_ANGLE_RIGHT;
}

void UWV::init()
{
    pinMode(joystickXPin, INPUT);
    pinMode(joystickYPin, INPUT);
    pinMode(armSwitchPin, INPUT);
    pinMode(modeSwitchPin, INPUT);
}

int UWV::readSpeed()
{
    int xValue = map(analogRead(joystickXPin), 509, 0, minUwvSpeed, maxUwvSpeed);

    if (DEBUG)
    {
        Serial.print("speed: ");
        Serial.println(xValue);
    }
    return xValue;
}

int UWV::readRudder()
{
    int yValue = map(analogRead(joystickYPin), 0, 1024, maxRudderAngleRight, maxRudderAngleLeft);

    if (DEBUG)
    {
        Serial.print("ruddder: ");
        Serial.println(yValue);
    }
    return yValue;
}

int UWV::readArmState()
{
    int reading = digitalRead(armSwitchPin);
    Serial.print("reading: ");
    Serial.println(reading);

    if (reading != lastButtonState)
    {
        // reset the debouncing timer
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (reading != buttonState)
        {
            buttonState = reading;
            if (buttonState == HIGH)
            {
                ledState = !ledState;
            }
        }
    }

    Serial.println(ledState);
    lastButtonState = reading;
}