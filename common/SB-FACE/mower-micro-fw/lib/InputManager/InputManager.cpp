#include "InputManager.h"
#include <Arduino.h>

InputManager inputManager;

void InputManager::begin(int charger_pin, int battery_status_button_pin, int battery_level_pin)
{
    _charger_pin = charger_pin;
    _battery_status_button_pin = battery_status_button_pin;
    _battery_pin = battery_level_pin;
    pinMode(_charger_pin, INPUT);
    pinMode(_battery_status_button_pin, INPUT);
    pinMode(_uav_status_trigger_pin, OUTPUT);
    pinMode(_battery_status_trigger_pin, OUTPUT);
}

void InputManager::work()
{
    _readBattery();
    bool battery_status_button_pressed = digitalRead(_battery_status_button_pin) == HIGH;
    if (battery_status_button_pressed != _is_button_pressed)
    {
        _is_button_pressed = battery_status_button_pressed;
        if (_is_button_pressed && isBatteryWarning())
        {
            suppress_battery_warning = true;
        }
        if (_batteryStatusButtonListener != NULL)
        {
            _batteryStatusButtonListener(_is_button_pressed);
        }
    }

    bool is_charging = digitalRead(_charger_pin) == HIGH;
    if (is_charging != _is_charging)
    {
        _is_charging = is_charging;
        if (_chargerConnectionListener != NULL)
        {
            _chargerConnectionListener(_is_charging);
        }
    }

    if (softSwitchTriggered())
    {
        triggerBatteryStatus();
    }
    else
    {
        triggerUavStatus();
    }

    if (isBatteryCritical())
    {
        if (_batteryCriticalListener != NULL)
        {
            _batteryCriticalListener();
        }
    }
    else if (isBatteryWarning() && !suppress_battery_warning)
    {
        if (_batteryWarningListener != NULL)
        {
            _batteryWarningListener();
        }
        // suppress_battery_warning = true;
    }
}