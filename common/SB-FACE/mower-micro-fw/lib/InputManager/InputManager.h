#ifndef ELYIR_INPUT_MANAGER_H
#define ELYIR_INPUT_MANAGER_H

#include <Arduino.h>

class InputManager;

extern InputManager inputManager;

typedef void (*InputManagerChargerConnectionListener)(bool);
typedef void (*InputManagerBatteryStatusButtonListener)(bool);
typedef void (*InputManagerBatteryLevelChangeListener)(int);
typedef void (*InputManagerBatteryWarningListener)();
typedef void (*InputManagerBatteryCriticalListener)();
typedef void (*InputManagerSoftSwitchTriggerChangeListener)(bool);

class InputManager
{
private:
    bool _is_charging = false;
    bool _is_button_pressed = false;
    int _charger_pin;
    int _battery_pin;
    int _battery_status_button_pin;
    double _max_input_voltage = 5.0;
    double _battery_min = 6.0;
    double _battery_max = 12.0;
    double _resistance1 = 10000.0;
    double _resistance2 = 2000.0;
    double _battery_reading;
    int _battery_level = 0;
    int _prev_battery_level = 0;
    int _battery_warning = 18;
    int _battery_critical = 10;
    bool suppress_battery_warning = false;
    int _uav_status_trigger_pin = 6;
    int _battery_status_trigger_pin = 7;
    int _prev_soft_switch_state = false;

    // int _last_digital_state = LOW;
    // DebounceEvent *button;
    // int custom_debounce_delay 50;

    // // Time the library waits for a second (or more) clicks
    // // Set to 0 to disable double clicks but get a faster response
    // int custom_repeat_delay 500;

    InputManagerChargerConnectionListener _chargerConnectionListener;
    InputManagerBatteryStatusButtonListener _batteryStatusButtonListener;
    InputManagerBatteryLevelChangeListener _batteryLevelChangeListener;
    InputManagerBatteryWarningListener _batteryWarningListener;
    InputManagerBatteryCriticalListener _batteryCriticalListener;
    InputManagerSoftSwitchTriggerChangeListener _softSwitchTriggerChangeListener;

    // map battery input voltage to battery level
    void _batteryLevelPercent()
    {
        _battery_level = map(_batteryVoltage(), _battery_min, _battery_max, 0, 100);
        if (_battery_level > 100)
        {
            _battery_level = 100;
        }
        else if (_battery_level < 0)
        {
            _battery_level = 0;
        }
        if (_battery_level != _prev_battery_level)
        {
            _prev_battery_level = _battery_level;
            suppress_battery_warning = false;
            if (_batteryLevelChangeListener != NULL)
            {
                _batteryLevelChangeListener(_battery_level);
            }
        }
    }

    // map double
    double _mapDouble(double x, double in_min, double in_max, double out_min, double out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
    // calculate battery input voltage from battery pin reading and resistor values
    double _batteryVoltage()
    {
        // convert the analog reading (which goes from 0 - 1023) to a voltage (0 - _max_input_voltage):
        double input_voltage = (_battery_reading * _max_input_voltage) / 1024.0;
        double batteryVoltage = input_voltage * ((_resistance1 + _resistance2) / _resistance2);
        return batteryVoltage;
    }

    void _readBattery()
    {
        // get average of 10 readings
        _battery_reading = 0;
        for (int i = 0; i < 10; i++)
        {
            _battery_reading += analogRead(_battery_pin);
        }
        _battery_reading /= 10.0;
        _batteryLevelPercent();
    }

public:
    // InputManager(/* args */);
    // ~InputManager();
    void begin(int charger_pin, int battery_status_button_pin, int battery_level_pin);
    void work();
    int getBatteryLevel() { return _battery_level; }
    void triggerUavStatus()
    {
        digitalWrite(_uav_status_trigger_pin, HIGH);
        digitalWrite(_battery_status_trigger_pin, LOW);
    }
    void triggerBatteryStatus()
    {
        digitalWrite(_uav_status_trigger_pin, LOW);
        digitalWrite(_battery_status_trigger_pin, HIGH);
    }
    bool isCharging() { return _is_charging; }
    bool isBatteryCritical()
    {
        return !_is_charging && _battery_level < _battery_critical;
    }
    bool isBatteryWarning()
    {
        return !_is_charging && _battery_level < _battery_warning && _battery_level > _battery_critical;
    }
    void setUavStatusTriggerPin(int pin)
    {
        _uav_status_trigger_pin = pin;
    }
    void setBatteryStatusTriggerPin(int pin)
    {
        _battery_status_trigger_pin = pin;
    }
    void setChargerConnectionListener(InputManagerChargerConnectionListener listener)
    {
        _chargerConnectionListener = listener;
    }
    void setBatteryStatusButtonListener(InputManagerBatteryStatusButtonListener listener)
    {
        _batteryStatusButtonListener = listener;
    }
    void setBatteryLevelChangeListener(InputManagerBatteryLevelChangeListener listener)
    {
        _batteryLevelChangeListener = listener;
    }
    void setBatteryWarningListener(InputManagerBatteryWarningListener listener)
    {
        _batteryWarningListener = listener;
    }
    void setBatteryCriticalListener(InputManagerBatteryCriticalListener listener)
    {
        _batteryCriticalListener = listener;
    }
    void setSoftSwitchTriggerChangeListener(InputManagerSoftSwitchTriggerChangeListener listener)
    {
        _softSwitchTriggerChangeListener = listener;
    }
    void setMaxInputVoltage(double voltage)
    {
        _max_input_voltage = voltage;
    }
    void setBatteryMin(double voltage)
    {
        _battery_min = voltage;
    }
    void setBatteryMax(double voltage)
    {
        _battery_max = voltage;
    }
    void setBatteryWarningLevel(int level)
    {
        _battery_warning = level;
    }
    void setBatteryCriticalLevel(int level)
    {
        _battery_critical = level;
    }
    void setResistance1(double resistance)
    {
        _resistance1 = resistance;
    }
    void setResistance2(double resistance)
    {
        _resistance2 = resistance;
    }
    bool softSwitchTriggered()
    {
        bool state = _is_button_pressed || _is_charging;
        if (state != _prev_soft_switch_state)
        {
            _prev_soft_switch_state = state;
            if (_softSwitchTriggerChangeListener != NULL)
            {
                _softSwitchTriggerChangeListener(state);
            }
        }
        return state;
    }
};

#endif