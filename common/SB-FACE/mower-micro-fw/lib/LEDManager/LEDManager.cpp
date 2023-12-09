
#include "LEDManager.h"

LEDManager ledManager;

void LEDManager::begin(int pin, int count)
{
    begin(pin, count, NEO_GRB + NEO_KHZ800, 100);
}

void LEDManager::begin(int pin, int count, neoPixelType t, int brightness)
{
    _pin = pin;
    _led_count = count;
    _brightness = brightness;
    strip = Adafruit_NeoPixel(count, pin, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.setPin(pin);
    strip.updateLength(count);
    strip.updateType(t);
    strip.show(); // Turn OFF all pixels ASAP
    strip.setBrightness(_brightness);
}

void LEDManager::_indicateBatteryLevel(int level)
{
    uint32_t color = strip.Color(0, 0, 0);
    // Set pixel's color based on the percentage of the battery level
    switch (level)
    {
    case 0 ... 20:
        color = strip.Color(255, 0, 0);
        break;
    case 21 ... 40:
        color = strip.Color(255, 150, 0);
        break;
    case 41 ... 80:
        color = strip.Color(205, 164, 0);
        break;
    case 81 ... 100:
        color = strip.Color(0, 255, 0);
        break;
    default:
        color = strip.Color(0, 0, 0);
        break;
    }

    int ledCount = map(level, 0, 100, 0, _led_count);
    int wait = map(ledCount, 0, _led_count, 160, 80);

    // uint32_t color = strip.Color(0, 0, 0);
    for (int i = 0; i < ledCount; i++)
    {                                  // For each pixel in strip...
        strip.setPixelColor(i, color); //  Set pixel's color (in RAM)
        strip.show();                  //  Update strip to match
        delay(wait);                   //  Pause for a moment
    }
}
void LEDManager::_indicateCharging(int level)
{
    clearAll();
    uint32_t color = strip.Color(0, 0, 0);
    uint32_t moving_color = strip.Color(0, 255, 0);

    int levelCount = map(level, 0, 100, 0, _led_count);
    int wait = map(levelCount, 0, _led_count, 100, 10);

    for (int j = 0; j < levelCount; j++)
    {
        for (int i = 0; i < levelCount; i++)
        {

            // Set pixel's color based on the percentage of the battery level
            int iPercent = map(i, 0, _led_count, 0, 100);
            switch (iPercent)
            {
            case 0 ... 10:
                color = strip.Color(255, 0, 0);
                // moving_color = strip.Color(255, 150, 0);
                break;
            case 11 ... 30:
                color = strip.Color(255, 150, 0);
                // moving_color = strip.Color(205, 164, 0);
                break;
            case 31 ... 60:
                color = strip.Color(205, 164, 0);
                // moving_color = strip.Color(0, 255, 0);
                break;
            case 61 ... 100:
                color = strip.Color(0, 255, 0);
                break;
            default:
                color = strip.Color(0, 0, 0);
                break;
            }                              // For each pixel in strip...
            strip.setPixelColor(i, color); //  Set pixel's color (in RAM)
            strip.show();
        }
        // For each pixel in strip...
        // strip.setPixelColor(j - 1, moving_color); //  Set pixel's color (in RAM)
        // strip.setPixelColor(j + 1, moving_color); //  Set pixel's color (in RAM)
        if (j < levelCount - 1)
        {
            strip.setPixelColor(j, moving_color); //  Set pixel's color (in RAM)
        }
        else
        {
            strip.setPixelColor(j, color); //  Set pixel's color (in RAM)
        }
        strip.show(); //  Update strip to match
        delay(wait);  //  Pause for a moment
    }

    for (int i = levelCount; i < _led_count; i++)
    {

        // Set pixel's color based on the percentage of the battery level
        int iPercent = map(i, 0, _led_count, 0, 100);
        switch (iPercent)
        {
        case 0 ... 10:
            color = strip.Color(255, 0, 0);
            break;
        case 11 ... 30:
            color = strip.Color(255, 150, 0);
            break;
        case 31 ... 60:
            color = strip.Color(205, 164, 0);
            break;
        case 61 ... 100:
            color = strip.Color(0, 255, 0);
            break;
        default:
            color = strip.Color(0, 0, 0);
            break;
        }                              // For each pixel in strip...
        strip.setPixelColor(i, color); //  Set pixel's color (in RAM)
        strip.show();                  //  Update strip to match
        delay(wait);                   //  Pause for a moment
    }
}

void LEDManager::_indicateBatteryFull(int level)
{
    uint32_t color = strip.Color(255, 0, 0);

    int ledCount = map(level, 0, 100, 0, _led_count);
    int wait = 50;

    // for (int i = 0; i < _led_count; i++)
    // {                                                   // For each pixel in strip...
    //     strip.setPixelColor(i, strip.Color(0, 255, 0)); //  Set pixel's color (in RAM)
    //     strip.show();                                   //  Update strip to match
    // }
    for (int i = 0; i < _led_count; i++)
    {
        for (int j = 0; j < _led_count; j++)
        {                                                   // For each pixel in strip...
            strip.setPixelColor(j, strip.Color(0, 255, 0)); //  Set pixel's color (in RAM)
            strip.show();
        }                              // For each pixel in strip...
        strip.setPixelColor(i, color); //  Set pixel's color (in RAM)
        strip.show();                  //  Update strip to match
        delay(wait);                   //  Pause for a moment
    }
    for (int i = _led_count; i > 0; i--)
    {
        for (int j = 0; j < _led_count; j++)
        {                                                   // For each pixel in strip...
            strip.setPixelColor(j, strip.Color(0, 255, 0)); //  Set pixel's color (in RAM)
            strip.show();
        }                              // For each pixel in strip...
        strip.setPixelColor(i, color); //  Set pixel's color (in RAM)
        strip.show();                  //  Update strip to match
        delay(wait);                   //  Pause for a moment
    }
}
void LEDManager::work()
{
    if (_show_battery_status)
    {
        _indicateBatteryLevel(_battery_status);
    }
    else if (_is_charging)
    {
        if (_battery_status < 100)
        {
            _indicateCharging(_battery_status);
        }
        else
        {
            _indicateBatteryFull(_battery_status);
        }
    }
    else
    {
        clearAll();
    }
}

void LEDManager::setChargingMode()
{
    _is_charging = true;
}

void LEDManager::unsetChargingMode()
{
    _is_charging = false;
}

void LEDManager::setBatteryStatusMode()
{
    _show_battery_status = true;
    clearAll();
}

void LEDManager::unsetBatteryStatusMode()
{
    _show_battery_status = false;
}

void LEDManager::setBatteryStatus(int status)
{
    _battery_status = status;
}

void LEDManager::clearAll()
{
    // strip.clear();
    for (int i = 0; i < _led_count; i++)
    {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(20);
}