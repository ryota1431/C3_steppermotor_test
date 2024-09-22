#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <Arduino.h>

class StepperMotor {
private:
    int dirPin;
    int stepPin;
    int stepsPerRevolution;
    int currentSpeed;
    bool isClockwise;
    unsigned long lastStepTime;
    int stepInterval;

public:
    StepperMotor(int dir, int step, int stepsPerRev = 200);
    void setSpeedFromJoystick(int joystickValue);
    void update();
};

#endif