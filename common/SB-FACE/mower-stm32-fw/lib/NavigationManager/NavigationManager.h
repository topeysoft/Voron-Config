#ifndef ELYIR_MOWER_NAVIGATION_MANAGER_H
#define ELYIR_MOWER_NAVIGATION_MANAGER_H

#include <Arduino.h>
#include <Every.h>
#include "Utils.h"
#include "Properties.h"

class NavigationManagerClass;
extern NavigationManagerClass navigationManager;

typedef void (*NavigationManagerMoveHandler)(int left, int right);
typedef void (*NavigationManagerGoalReachedCallback)(Pose pose);
typedef void (*NavigationManagerPoseUpdateCallback)(Pose pose, Pose goal);

class NavigationManagerClass
{
private:
    // Pose _pose;
    Pose _goal;
    bool _goalRequested = false;
    NavigationManagerMoveHandler _moveHandler;
    NavigationManagerGoalReachedCallback _goalReachedCallback;
    NavigationManagerPoseUpdateCallback _poseUpdateCallback;
    bool _goalReachedNotified = false;
    int _goalPositionTolerance = 10;
    int _goalOrientationTolerance = 1;
    unsigned long _lastNotifed = 0;
    const unsigned long _notifyInterval = 1000;
    float _turnSpeedDelta = 0.5;
    float _minTurningSpeed = 30;
    float _maxTurningSpeed = 70;
    bool _manualControl = false;
    void _notifyPoseUpdate()
    {
        if (millis() - _lastNotifed > _notifyInterval)
        {
            if (_poseUpdateCallback)
            {
                _poseUpdateCallback(_pose, _goal);
            }
            _lastNotifed = millis();
        }
    }
    void _move();
    void _turn();
    void _addDistanceToPose(double distance);

public:
    void setup(){};
    void work()
    {
        if (_manualControl)
        {
            return;
        }
        if (!_goalRequested)
        {
            return;
        }
        _notifyPoseUpdate();

        if (!isGoalOrientationReached())
        {
            // _notifyPoseUpdate();
            _turn();
        }
        else if (!isGoalPositionReached())
        {
            // _notifyPoseUpdate();
            _move();
        }
        else
        {
            if (!_goalReachedNotified)
            {
                _goalReachedNotified = true;
                if (_goalReachedCallback)
                {
                    _goalReachedCallback(_pose);
                }
            }
            _pose = _goal;
            _goalRequested = false;
            // _notifyPoseUpdate();
            stop();
        }
    }
    void setGoal(Pose goal)
    {
        _goal = goal;
        _goal.orientation.yaw = normalizeAngle(_goal.orientation.yaw);
        _goalReachedNotified = false;
        _goalRequested = true;
    }
    Pose getGoal()
    {
        return _goal;
    }
    Pose getPose()
    {
        return _pose;
    }
    double angleFromGoal()
    {
        int diff = _goal.orientation.yaw - _pose.orientation.yaw;
        // diff = map(diff, 0, 360, -180, 180);
        // return _goal.orientation.yaw - _pose.orientation.yaw;
        // return atan2(_goal.orientation.pitch - _pose.orientation.pitch, _goal.orientation.yaw - _pose.orientation.yaw) * 180 / M_PI;
        return diff;
    }
    double distanceFromGoal()
    {
        return sqrt(pow(_goal.position.lon - _pose.position.lon, 2) + pow(_goal.position.lat - _pose.position.lat, 2));
    }
    bool isGoalPositionReached()
    {
        return distanceFromGoal() < _goalPositionTolerance;
        // return abs(_pose.position.lat - _goal.position.lat) <= _goalPositionTolerance && abs(_pose.position.lon - _goal.position.lon) <= _goalPositionTolerance;
        // && abs(_pose.position.alt - _goal.position.alt) < _goalPositionTolerance;
    }
    bool isGoalOrientationReached()
    {
        return abs(angleFromGoal()) <= _goalOrientationTolerance;
        // return abs(_pose.orientation.yaw - _goal.orientation.yaw) <= _goalOrientationTolerance;
        // return abs(_pose.orientation.roll - _goal.orientation.roll) <= _goalOrientationTolerance && abs(_pose.orientation.pitch - _goal.orientation.pitch) < _goalOrientationTolerance && abs(_pose.orientation.yaw - _goal.orientation.yaw) <= _goalOrientationTolerance;
    }
    bool isGoalReached()
    {
        return isGoalPositionReached() && isGoalOrientationReached();
    }
    void setMoveHandler(NavigationManagerMoveHandler handler)
    {
        _moveHandler = handler;
    }

    void stop()
    {
        if (_moveHandler)
        {
            _moveHandler(0, 0);
        }
    }
    void setGoalReachedCallback(NavigationManagerGoalReachedCallback callback)
    {
        _goalReachedCallback = callback;
    }
    void setPoseUpdateCallback(NavigationManagerPoseUpdateCallback callback)
    {
        _poseUpdateCallback = callback;
    }
    void resetGoal()
    {
        _goal = _pose;
    }
    void abort()
    {
        stop();
        resetGoal();
        _goalRequested = false;
    }
    void turnAround();
    void turnLeft();
    void turnRight();
    // Move to a distance in meters. Negative values move backwards.
    // Default distance is 1 meter
    void move(int distance = 1);
    void moveForward();
    void moveBackward();
    void enableManualMode()
    {
        abort();
        _manualControl = true;
    }
    void enableAutoMode()
    {
        _manualControl = false;
    }
};

#endif // ELYIR_MOWER_NAVIGATION_MANAGER_H