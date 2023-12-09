#include "DisplayManager.h"

const unsigned long FAST_BLINK_INTERVAL = 100, SLOW_BLINK_INTERVAL = 1000;

DisplayManagerClass displayManager;

// void setup();
void DisplayManagerClass::work()
{
    if (_refreshNow())
    {
        display.clearDisplay();
        _printDisplayData();
        display.display();
    }

    if (_blinkState)
        _blink();
}

const char *DisplayManagerClass::_getWifiStateString()
{
    const char *wifiStateString = "";
    switch (wifiState)
    {
    case UIStates::WifiStates::WIFI_STATE_IDLE:
        wifiStateString = "IDLE";
        break;
    case UIStates::WifiStates::WIFI_STATE_CONNECTING:
        wifiStateString = "CONNECTING";
        break;
    case UIStates::WifiStates::WIFI_STATE_CONNECTED:
        wifiStateString = "CONNECTED";
        break;
    case UIStates::WifiStates::WIFI_STATE_DISCONNECTED:
        wifiStateString = "DISCONNECTED";
        break;
    case UIStates::WifiStates::WIFI_STATE_ERROR:
        wifiStateString = "ERROR";
        break;
    }
    return wifiStateString;
}
const char *DisplayManagerClass::_getCasterStateString()
{
    const char *casterStateString = "";
    switch (casterState)
    {
    case UIStates::CasterStates::CASTER_STATE_IDLE:
        casterStateString = "IDLE";
        break;
    case UIStates::CasterStates::CASTER_STATE_CONNECTING:
        casterStateString = "CONNECTING";
        break;
    case UIStates::CasterStates::CASTER_STATE_AUTHENTICATING:
        casterStateString = "AUTHENTICATE";
        break;
    case UIStates::CasterStates::CASTER_STATE_CONNECTED_NO_RTCM:
        casterStateString = "AWAITING RTCM";
        break;
    case UIStates::CasterStates::CASTER_STATE_CONNECTED_SENDING_RTCM:
        casterStateString = "SENDING RTCM";
        break;
    case UIStates::CasterStates::CASTER_STATE_DISCONNECTED:
        casterStateString = "DISCONNECTED";
        break;
    case UIStates::CasterStates::CASTER_STATE_ERROR:
        casterStateString = "ERROR";
        break;
    }
    return casterStateString;
}
const char *DisplayManagerClass::_getGpsStateString()
{
    const char *gpsStateString = "";
    switch (gpsState)
    {
    case UIStates::GpsStates::GPS_STATE_IDLE:
        gpsStateString = "IDLE";
        break;
    case UIStates::GpsStates::GPS_STATE_SURVEY_MODE:
        gpsStateString = "SURVEY MODE ON";
        break;
    case UIStates::GpsStates::GPS_STATE_SURVEY_IN_PROGRESS:
        gpsStateString = "SURVEYING...";
        break;
    case UIStates::GpsStates::GPS_STATE_GETTING_RTCM:
        gpsStateString = "GETTING RTCM";
        break;
    case UIStates::GpsStates::GPS_STATE_HAS_RTCM:
        gpsStateString = "HAS RTCM";
        break;
    case UIStates::GpsStates::GPS_STATE_NO_RTCM:
        gpsStateString = "NO RTCM";
        break;
    case UIStates::GpsStates::GPS_STATE_ERROR:
        gpsStateString = "ERROR";
        break;
    }
    return gpsStateString;
}

void DisplayManagerClass::_printDisplayData()
{
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.print(F("WIFI: "));
    display.println(_getWifiStateString());

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.print(F("GPS: "));
    display.println(_getGpsStateString());

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.print(F("Caster: "));
    display.println(_getCasterStateString());

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 30);
    display.print(F("Uptime: "));
    display.print(_info->getResolvedUptime());
    display.print(_info->getUptimeUnit());
    display.print(F(" "));
    switch (spinState)
    {
    case 0:
    case 3:
        display.println("-");
        break;
    case 1:
        display.println("|");
        break;
    case 2:
        display.println("/");
        break;
    case 4:
        display.println("\\");
        break;
    default:
        break;
    }
    spinState++;
    if (spinState > 4)
    {
        spinState = 0;
    }

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 40);
    display.print("Sent: ");
    display.print(_info->getResolvedBytesSent());
    display.println(_info->getBytesSentUnit());

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 48);

    for (size_t i = 0; i < lineState; i++)
    {
        display.print("-");
    }
    display.println(">");

    lineState++;
    if (lineState > 20)
    {
        lineState = 0;
    }

    // display.print("-------------------- ");

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 56);
    display.print("IP: ");
    display.println(_info->getIpAddress());

    // display.println(_getInfoString());
}

void DisplayManagerClass::LEDon()
{
    _setLEDState(true);
}
void DisplayManagerClass::LEDoff()
{
    _setLEDState(false);
}
void DisplayManagerClass::_blink()
{
    if (millis() - _msLastBlink >= _msBlinkInterval)
        _toggleLED();
    _msLastBlink = millis();
}
void DisplayManagerClass::_setLEDState(bool state)
{
    _ledState = state;
    digitalWrite(LED_BUILTIN, _ledState);
}
void DisplayManagerClass::_toggleLED()
{
    _setLEDState(!_ledState);
}

// switch the LED on and off every BLINK_INTERVAL milliseconds.
void DisplayManagerClass::startBlink(unsigned long interval)
{
    _msBlinkInterval = interval;
    _blinkState = true;
}
void DisplayManagerClass::stopBlink(bool state)
{
    _blinkState = false;
    _setLEDState(state);
}
void DisplayManagerClass::blinkSlow()
{
    startBlink(SLOW_BLINK_INTERVAL);
}
void DisplayManagerClass::blinkFast()
{
    startBlink(FAST_BLINK_INTERVAL);
}
StatusInfo statusInfo;