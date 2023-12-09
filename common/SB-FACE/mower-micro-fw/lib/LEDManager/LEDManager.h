#ifndef LEDMANAGER_H
#define LEDMANAGER_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

class LEDManager;

extern LEDManager ledManager;

class LEDManager
{
private:
    int _pin;
    int _led_count;
    bool _is_charging = false;
    int _battery_status = 0;
    int _brightness = 100; // 0 to 255
    bool _show_battery_status;
    void _indicateBatteryLevel(int level);
    void _indicateCharging(int level);
    void _indicateBatteryFull(int level);
    Adafruit_NeoPixel strip; // = &Adafruit_NeoPixel(20, 0, NEO_GRB + NEO_KHZ800);

public:
    // LEDManager(/* args */);
    // ~LEDManager();
    void begin(int pin, int count);
    void begin(int pin, int count, neoPixelType t, int brightness);
    void work();
    void setChargingMode();
    void unsetChargingMode();
    void setBatteryStatusMode();
    void unsetBatteryStatusMode();
    void setBatteryStatus(int status);
    void clearAll();
    void setBrightness(int brightness)
    {
        _brightness = brightness;
    }
};

#endif