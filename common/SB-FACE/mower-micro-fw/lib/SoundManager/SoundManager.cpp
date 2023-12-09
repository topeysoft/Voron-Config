

#include "SoundManager.h"
#include "pitches.h"

SoundManagerClass soundManager;

int notes[] = {0,
               NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
               NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
               NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
               NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7};

void SoundManagerClass::warning()
{
    if (millis() - _lastTime >= 3000)
    {
        _lastTime = millis();
        tone(_pin, NOTE_E3, 100);
        delay(200);
        tone(_pin, NOTE_E3, 100);
        delay(200);
        noTone(_pin);
    }
}
void SoundManagerClass::alert()
{
    if (millis() - _lastTime >= 1000)
    {
        _lastTime = millis();
        tone(_pin, NOTE_E3, 100);
        delay(200);
        tone(_pin, NOTE_E3, 100);
        delay(200);
        tone(_pin, NOTE_E3, 100);
        delay(200);
        tone(_pin, NOTE_E3, 100);
        delay(200);
        noTone(_pin);
    }
}

void SoundManagerClass::chargerConnected()
{
    tone(_pin, NOTE_C4, 1000);
    delay(100);
    tone(_pin, NOTE_G5, 1000);
    delay(100);
    noTone(_pin);
    delay(500);
}

void SoundManagerClass::chargerDisconnected()
{
    tone(_pin, NOTE_G5, 1000);
    delay(100);
    tone(_pin, NOTE_C4, 1000);
    delay(100);
    noTone(_pin);
    delay(500);
}

void SoundManagerClass::batteryFull()
{
    tone(_pin, NOTE_C4, 200);
    delay(200);
    tone(_pin, NOTE_E5, 200);
    delay(200);
    tone(_pin, NOTE_E5, 200);
    delay(300);
    tone(_pin, NOTE_G5, 200);
    delay(200);
    noTone(_pin);
    delay(500);
}