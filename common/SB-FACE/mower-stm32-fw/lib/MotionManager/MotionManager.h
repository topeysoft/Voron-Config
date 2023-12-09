#ifndef ELYIR_MOWER_MOTION_MANAGER_H
#define ELYIR_MOWER_MOTION_MANAGER_H

#include <Arduino.h>
#include <Every.h>
// #include "Tracing.h"
#include <Servo.h>

class MotionManagerClass;
extern MotionManagerClass motionManager;

// enum MotionModes
// {
//     MOTION_MODE_SPORT,
//     MOTION_MODE_STANDARD,
//     MOTION_MODE_CONTROL
// };
typedef void (*MotionManagerCallback)();

class MotionManagerClass
{
private:
    // int _speed;         // Speed in %, -ve = reverse, +ve = forward
    int _minPwm = 1000; // Minimum PWM value
    int _maxPwm = 2000; // Maximum PWM value
    int _getSpeedPwm(int speed)
    {
        int _speedPwm = map(speed, -100, 100, _minPwm, _maxPwm);
        return _speedPwm;
    }

public:
    void setup(int leftPin, int rightPin);
    void work();
    void move(int left, int right);
    void stop();
    void setCallback(MotionManagerCallback callback);
};

#endif // ELYIR_MOWER_MOTION_MANAGER_H