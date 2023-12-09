#ifndef ELYIR_MOWER_SOUND_MANAGER_H
#define ELYIR_MOWER_SOUND_MANAGER_H

#include <Arduino.h>
#include <Every.h>

class SoundManagerClass;
extern SoundManagerClass soundManager;

class SoundManagerClass
{
private:
    byte _pin;
    bool _isDigit(char n)
    {
        return isDigit(n);
    };
    void _playNote(unsigned int note, unsigned long duration)
    {
        tone(_pin, note, duration);
    }
    void _stopNote()
    {
        noTone(_pin);
    }
    void _playNote(unsigned int note)
    {
        _playNote(note, 1);
    }
    void _playRtttl(char *song);
    void _playMelody(int *melody, int tempo = 85)
    {
        _playMelody(melody, sizeof(*melody), tempo);
    }
    void _playMelody(int *melody, size_t length, int tempo = 85);

public:
    void setup(byte pin)
    {
        _pin = pin;
    }
    void work()
    {
    }
    void playStartup();
    void playStmReady();
    void playEspReady();
    void playShutdown();
    // void playError();
    // void playWarning();
    // void playSuccess();
    // void playInfo();
    // void playAlarm();
};

#endif // ELYIR_MOWER_SOUND_MANAGER_H