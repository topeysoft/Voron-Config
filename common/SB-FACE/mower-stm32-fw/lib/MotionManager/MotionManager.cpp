#include "MotionManager.h"
#define DebugSerial Serial4
MotionManagerClass motionManager;
Servo _leftServo;  // create servo object to control a servo
Servo _rightServo; // create servo object to control a servo
Every printMovementNow(1000);
void MotionManagerClass::setup(int leftPin, int rightPin)
{
    _leftServo.attach(leftPin);
    _rightServo.attach(rightPin);
    // _leftServo.writeMicroseconds(_maxPwm);
    // _rightServo.writeMicroseconds(_maxPwm);
}
void MotionManagerClass::stop()
{
    _leftServo.writeMicroseconds(0);
    _rightServo.writeMicroseconds(0);
}

void MotionManagerClass::work() {}
// void MotionManagerClass::move(int x, int y, int z) {}
void MotionManagerClass::move(int leftPercent, int rightPercent)
{
    int left = _getSpeedPwm(leftPercent);
    int right = _getSpeedPwm(rightPercent);
    if (printMovementNow())
    {
        DebugSerial.print("Motion::Move --- left: ");
        DebugSerial.print(left);
        DebugSerial.print(" right: ");
        DebugSerial.println(right);
    }

    _leftServo.writeMicroseconds(left);
    _rightServo.writeMicroseconds(right);
}
// void turnLeft();
// void turnRight();
// void stop();
// void setCallback(MotionManagerCallback callback);
// void setSpeed(int16_t speed);
