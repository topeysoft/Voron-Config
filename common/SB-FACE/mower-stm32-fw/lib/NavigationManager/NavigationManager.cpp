

#include "NavigationManager.h"

NavigationManagerClass navigationManager;

void NavigationManagerClass::turnRight()
{

    _goal.orientation.yaw = normalizeAngle(_pose.orientation.yaw - 90);
    _goalRequested = true;
}
void NavigationManagerClass::turnLeft()
{

    _goal.orientation.yaw = normalizeAngle(_pose.orientation.yaw + 90);
    _goalRequested = true;
}
void NavigationManagerClass::turnAround()
{
    _goal.orientation.yaw = normalizeAngle(_pose.orientation.yaw + 180);
    _goalRequested = true;
}
void NavigationManagerClass::_move()
{
    if (_moveHandler)
    {
        // float l = (msg.linear.lat - msg.angular.z) / 2;
        // float r = (msg.linear.lat + msg.angular.z) / 2;
        int left = (distanceFromGoal() - 0) / 2;
        int right = (distanceFromGoal() + 0) / 2;
        _moveHandler(left, right);
    }
}
void NavigationManagerClass::_turn()
{
    if (_moveHandler)
    {
        // float l = (msg.linear.lat - msg.angular.z) / 2;
        // float r = (msg.linear.lat + msg.angular.z) / 2;
        int angle = map(angleFromGoal(), 0, 360, -180, 180);
        int factor = constrain((angle / 180) * 100, _minTurningSpeed, _maxTurningSpeed);

        int left, right;
        if (factor > 0)
        {
            left = ((0 + factor));
            right = ((0 - factor));
        }
        else
        {
            left = ((0 - factor));
            right = ((0 + factor));
        }
        _moveHandler(left, right);
    }
}
void NavigationManagerClass::move(int distance)
{
    _addDistanceToPose(distance);
    _goalRequested = true;
}
void NavigationManagerClass::moveForward()
{
    move(1); // Move forward 1 meter
}
void NavigationManagerClass::moveBackward()
{
    move(-1); // Move backward 1 meter
}

void NavigationManagerClass::_addDistanceToPose(double distance)
{
    // Taken from https://stackoverflow.com/questions/7477003/calculating-new-longitude-latitude-from-old-n-meters
    double earth = 6378.137;                      // radius of the earth in kilometer
    double m = (1 / ((PI / 180) * earth)) / 1000; // 1 meter in degree

    _pose.position.lat = _pose.position.lat + (distance * m);
    _pose.position.lon = _pose.position.lon + (distance * m) / cos(_pose.position.lat * (PI / 180));
}