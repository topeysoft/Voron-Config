#ifndef ELYIR_MOWER_RC_MANAGER_H
#define ELYIR_MOWER_RC_MANAGER_H

#include <Arduino.h>
#include <Every.h>
#include <IBusBM.h>

// DebugSerial

// #include "Tracing.h"

// struct RCData
// {
//     int ch1;
//     int ch2;
//     int ch3;
//     int ch4;
//     int ch5;
//     int ch6;
//     int ch7;
//     int ch8;
//     int ch9;
//     int ch10;
//     int ch11;
//     int ch12;
// };

class RCManagerClass;
extern RCManagerClass rcManager;

typedef void (*RCManagerDataCallback)(int *);
class RCManagerClass
{
private:
    int16_t _speed;
    unsigned long _uptime;
    bool _ready()
    {
        return millis() - _uptime > 2000;
    }

    RCManagerDataCallback _callback;
    IBusBM _iBus; // IBus object
    const size_t channelCount = 12;
    int *_data;
    HardwareSerial *_serial;

public:
    void setup(HardwareSerial *serial, int8_t timerId = IBUSBM_NOTIMER, HardwareSerial *debugSerial = nullptr)
    {
        _serial = serial;
        // HardwareSerial SerialPort(2); // create a serial port object to communicate with the ESP32
        // SerialPort.begin(115200, SERIAL_8N1, 16, 17);
        _uptime = millis();
        _iBus.begin(*_serial, timerId);
        if (debugSerial != nullptr)
        {
            debugSerial->println("iBUS Initialized");
        }
        // while (_iBus.cnt_rec == 0)
        // {                 // Wait until first Ibus messages is recieved
        //     _iBus.loop(); // Call the Ibus loop to check for Ibus messages from the receiver
        //     if (debugSerial != nullptr)
        //     {
        //         debugSerial->println("Starting iBUS, Waiting for Reciever");
        //     }
        //     delay(1); // Wait 1 Milllisecond before checking for Ibus messages again
        // }
        _data = new int[channelCount + 1];
        // _data = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }
    void work();
    size_t getChannelCount()
    {
        return channelCount;
    }
    void onReceive(RCManagerDataCallback callback)
    {

        _callback = callback;
    }
};

#endif // ELYIR_MOWER_MOTION_MANAGER_H