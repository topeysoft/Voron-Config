#ifndef ELYIR_MOWER_SENSES_MANAGER_H
#define ELYIR_MOWER_SENSES_MANAGER_H

#include <Arduino.h>
#include <Every.h>
#include <Every.h>
#include <QMC5883LCompass.h>
#include "Utils.h"
#include "Properties.h"

class SensesManagerClass;
extern SensesManagerClass sensesManager;

typedef void (*SensesManagerLowVoltageCallback)(double, int);
typedef void (*SensesManagerFullVoltageCallback)(double, int);
typedef void (*SensesManagerChargerStatusCallback)(bool, double);
typedef void (*SensesManagerReadyCallback)();

class SensesManagerClass
{
private:
    // Position _position;
    // Orientation _orientation;
    double _voltage;
    double _chargerVoltage;
    double _highestChargerVoltage;
    const double _noChargerVoltage = 5.0;
    int _voltagePercent;
    double _lowestVoltage;
    double _highestVoltage;
    bool _voltageMessageAcknowledged;
    byte _chargerPin;
    byte _voltagePin;
    unsigned long _last_read;
    const int _readInterval = 200;

    SensesManagerLowVoltageCallback _lowVoltageCallback;
    SensesManagerFullVoltageCallback _fullVoltageCallback;
    SensesManagerChargerStatusCallback _chargerStatusCallback;
    SensesManagerReadyCallback _readyCallback;

public:
    void setup();
    void work();
    void setVoltageSensor(int pin, double chargedVoltage = 12.6, double lowVoltage = 11.6)
    {
        _voltagePin = pin;
        _lowestVoltage = lowVoltage;
        _highestVoltage = chargedVoltage;
        pinMode(_voltagePin, INPUT);
    }
    void setChargerSensor(int pin, double chargerVoltage = 14.5)
    {
        _chargerPin = pin;
        _highestChargerVoltage = chargerVoltage;
        pinMode(_voltagePin, INPUT);
    }
    void setPosition(double lat, double lon, double alt)
    {
        _pose.position.lat = lat;
        _pose.position.lon = lon;
        _pose.position.alt = alt;
    }
    void setPosition(double lat, double lon, double alt, double acc)
    {
        _pose.position.lat = lat;
        _pose.position.lon = lon;
        _pose.position.alt = alt;
        _pose.position.acc = acc;
    }
    void setPosition(Position position)
    {
        _pose.position = position;
    }
    Position getPosition()
    {
        return _pose.position;
    }
    void setOrientation(Orientation orientation)
    {
        _pose.orientation = orientation;
    }
    Orientation getOrientation()
    {
        return _pose.orientation;
    }
    void setVoltage(double voltage)
    {
        _voltage = voltage;
    }
    double getVoltage()
    {
        return _voltage;
    }
    int getVoltagePercent()
    {
        return _voltagePercent;
    }
    void setChargerVoltage(double voltage)
    {
        _chargerVoltage = voltage;
    }
    double getChargerVoltage()
    {
        return isChargerConnected() ? _chargerVoltage : 0;
    }
    bool isChargerConnected()
    {
        return _chargerVoltage > _noChargerVoltage;
    }
    void acknowledgeVoltageMessage()
    {
        _voltageMessageAcknowledged = true;
    }
    void setLowVoltageCallback(SensesManagerLowVoltageCallback callback)
    {
        _lowVoltageCallback = callback;
    }
    void setFullVoltageCallback(SensesManagerFullVoltageCallback callback)
    {
        _fullVoltageCallback = callback;
    }
    void setReadyCallback(SensesManagerReadyCallback callback)
    {
        _readyCallback = callback;
    }
};

#endif // ELYIR_MOWER_SENSES_MANAGER_H