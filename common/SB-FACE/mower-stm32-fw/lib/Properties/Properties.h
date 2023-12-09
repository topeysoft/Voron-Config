#ifndef ELYIR_MOWER_PROPERTY_MANAGER_H
#define ELYIR_MOWER_PROPERTY_MANAGER_H

struct LinearSpeed
{
    int x;
    int y;
    int z;
};
struct AngularSpeed
{
    int x;
    int y;
    int z;
};

struct Twist
{
    LinearSpeed linear;
    AngularSpeed angular;
};
struct Position
{
    double lat;
    double lon;
    double alt;
    double acc;
};

struct Orientation
{
    double roll;
    double pitch;
    double yaw;
};
struct Pose
{
    Position position;
    Orientation orientation;
};

extern Pose _pose;
// extern Pose _goal;

#endif // ELYIR_MOWER_PROPERTY_MANAGER_H