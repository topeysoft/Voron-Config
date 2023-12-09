#ifndef ELYIR_MOWER_SOUND_MANAGER_H
#define ELYIR_MOWER_SOUND_MANAGER_H

#include <Arduino.h>

class SoundManagerClass;
extern SoundManagerClass soundManager;

class SoundManagerClass
{
private:
    int dutyCycle = 256;
    int channel = 0;
    int resolution = 8;
    int freq = 2000;
    byte _pin;
    unsigned long _lastTime = 0;

    void _play(unsigned long duration)
    {
        tone(_pin, dutyCycle, duration);
        // ledcWrite(channel, dutyCycle);
        // delay(duration);
        // ledcWrite(channel, 0);
    }

public:
    void
    begin(byte pin)
    {

        _pin = pin;
        pinMode(pin, OUTPUT);
        // ledcSetup(channel, freq, resolution);
        // ledcAttachPin(_pin, channel);
    }
    void work()
    {
    }
    void warning();
    void alert();
    void chargerConnected();
    void chargerDisconnected();
    void batteryFull();
    void stop()
    {
        // ledcWrite(channel, 0);
    }
};

#endif // ELYIR_MOWER_SOUND_MANAGER_H