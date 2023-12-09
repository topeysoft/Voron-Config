#ifndef ELYIR_DISPLAY_MANAGER_H
#define ELYIR_DISPLAY_MANAGER_H

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include <TimeLib.h>
#include <Every.h>
#include "UIStates.h"

class StatusInfo;
class DisplayManagerClass;

extern DisplayManagerClass displayManager;

class DisplayManagerClass
{
private:
    Adafruit_SSD1306 display;
    void _printDisplayData();
    UIStates::WifiStates wifiState;
    UIStates::GpsStates gpsState;
    UIStates::CasterStates casterState;
    StatusInfo *_info;
    int spinState;
    int lineState;
    Every _refreshNow;
    const char *_getWifiStateString();
    const char *_getGpsStateString();
    const char *_getCasterStateString();
    const char *_getInfoString();
    unsigned long _msLastBlink;
    unsigned long _msBlinkInterval;
    bool _blinkState;
    bool _ledState;

    void _blink();
    void _setLEDState(bool state);
    void _toggleLED();

public:
    void setup()
    {
        wifiState = UIStates::WifiStates::WIFI_STATE_IDLE;
        gpsState = UIStates::GpsStates ::GPS_STATE_IDLE;
        casterState = UIStates::CasterStates ::CASTER_STATE_IDLE;
        _refreshNow.reset(100, true);
        spinState = 0;
        lineState = 0;

        display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

        if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        { // Address 0x3D for 128x64
            Serial.println(F("SSD1306 allocation failed"));
            for (;;)
                ;
        }
        delay(2000);
        display.clearDisplay();
        _msLastBlink = millis();
        _msBlinkInterval = 0;
        _blinkState = false;
        _ledState = false;
        LEDoff();

        // display.setTextSize(1);
        // display.setTextColor(WHITE);
        // display.setCursor(0, 10);
        // // Display static text
        // display.println("Hello, world!");
        // display.display();
    }
    void work();

    void setNetworkIPString(const char *ipStr);
    void setWifiState(UIStates::WifiStates state)
    {
        wifiState = state;
    }
    void setGpsState(UIStates::GpsStates state)
    {
        gpsState = state;
    }
    void setCasterState(UIStates::CasterStates state)
    {
        casterState = state;
    }
    void setInfo(StatusInfo *info)
    {
        _info = info;
    }

    void blinkFast();
    void blinkSlow();
    void startBlink(unsigned long interval);
    void stopBlink(bool state);
    void LEDon();
    void LEDoff();

    // void setBatteryState(byte percent);
};

class StatusInfo
{
private:
    IPAddress _ipAddress;
    unsigned long _bytesSent;
    const char *_bytesSentUnit;
    const char *_uptimeUnit;
    unsigned long _resolvedBytesSent;
    unsigned long _resolvedUptime;
    unsigned long _uptime;
    double _gpsLat; // latitude
    double _gpsLon; // longitude
    double _gpsAlt; // altitude
    String _gpsIniTime;
    bool _gpsConnected;
    bool _wifiConnected;
    bool _ntripConnected;
    byte _gpsSiv; // Satellite in view

public:
    void setIpAddress(IPAddress ipAddress) { _ipAddress = ipAddress; }
    void setBytesSent(unsigned long bytesSent)
    {
        _bytesSent = bytesSent;
        _bytesSentUnit = "B";
        _resolvedBytesSent = _bytesSent;
        if (_bytesSent > 999)
        {
            _resolvedBytesSent = _bytesSent / 1024;
            _bytesSentUnit = "KB";
        }
        if (_bytesSent > 999999)
        {
            _resolvedBytesSent = _bytesSent / (1024 * 1024);
            _bytesSentUnit = "MB";
        }
        if (_bytesSent > 999999999)
        {
            _resolvedBytesSent = _bytesSent / (1024 * 1024 * 1024);
            _bytesSentUnit = "GB";
        }
    }
    void setUptime(unsigned long uptime)
    {
        _uptime = uptime;
        _resolvedUptime = _uptime;
        _uptimeUnit = "Sec";
        if (_uptime > 60)
        {
            _resolvedUptime = _uptime / 60;
            _uptimeUnit = "min";
        }
        if (_uptime > 3600)
        {
            _resolvedUptime = _uptime / 3600;
            _uptimeUnit = "hr";
        }
        if (_uptime > 86400)
        {
            _resolvedUptime = _uptime / 86400;
            _uptimeUnit = "days";
        }
    }
    int getResolvedBytesSent()
    {
        return _resolvedBytesSent;
    }
    const char *getBytesSentUnit()
    {
        return _bytesSentUnit;
    }
    int getResolvedUptime()
    {
        return _resolvedUptime;
    }
    const char *getUptimeUnit()
    {
        return _uptimeUnit;
    }
    IPAddress getIpAddress()
    {
        return _ipAddress;
    }

    unsigned long getBytesSent()
    {
        return _bytesSent;
    };
    double getGpsLat()
    {
        return _gpsLat;
    };
    double getGpsLon()
    {
        return _gpsLon;
    }
    double getGpsAlt()
    {
        return _gpsAlt;
    }
    byte getGpsSiv()
    {
        return _gpsSiv;
    }
    String getGpsInitTime()
    {
        return _gpsIniTime;
    }
    bool getGpsConnected()
    {
        return _gpsConnected;
    }
    bool getWifiConnected()
    {
        return _wifiConnected;
    }
    bool getNtripConnected()
    {
        return _ntripConnected;
    }

    void setGpsLat(double gpsLat)
    {
        _gpsLat = gpsLat;
    }
    void setGpsLon(double gpsLon)
    {
        _gpsLon = gpsLon;
    }
    void setGpsAlt(double gpsAlt)
    {
        _gpsAlt = gpsAlt;
    }
    void setGpsSiv(byte gpsSiv)
    {
        _gpsSiv = gpsSiv;
    }
    void setGpsInitTime(String gpsIniTime)
    {
        _gpsIniTime = gpsIniTime;
    }
    void setGpsConnected(bool gpsConnected)
    {
        _gpsConnected = gpsConnected;
    }
    void setWifiConnected(bool wifiConnected)
    {
        _wifiConnected = wifiConnected;
    }
    void setNtripConnected(bool ntripConnected)
    {
        _ntripConnected = ntripConnected;
    }
};
extern StatusInfo statusInfo;
#endif