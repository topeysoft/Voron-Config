#ifndef ELYIR_MOWER_DATA_MANAGER_H
#define ELYIR_MOWER_DATA_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJson.h>

enum TxDataType
{
    TX_DATA_TYPE_RC,
    TX_DATA_TYPE_LOCATION,
    TX_DATA_TYPE_COMPASS,
    TX_DATA_TYPE_MOTION,
    TX_DATA_TYPE_TELEMETRY,
    TX_DATA_TYPE_SOUND,
    TX_DATA_TYPE_NAVIGATION,
    TX_DATA_TYPE_PROPERTIES,
    TX_DATA_TYPE_STATUS,
    TX_DATA_TYPE_DEBUG,
    TX_DATA_TYPE_ESP_READY,
    TX_DATA_TYPE_ESP_READY_REQUEST,
    TX_DATA_TYPE_ESP_READY_ACK,
    TX_DATA_TYPE_STM_READY,
    TX_DATA_TYPE_STM_READY_REQUEST,
    TX_DATA_TYPE_STM_READY_ACK,
    TX_DATA_TYPE_GOAL_REQUEST,
    TX_DATA_TYPE_GOAL_REQUEST_ACK,
    TX_DATA_TYPE_NAVIGATION_COMMAND_REQUEST,
    TX_DATA_TYPE_NAVIGATION_COMMAND_REQUEST_ACK,
    TX_DATA_TYPE_DEVICE_COMMAND_REQUEST,
    TX_DATA_TYPE_DEVICE_COMMAND_REQUEST_ACK,

};

enum NavigationCommand
{
    NAVIGATION_COMMAND_TURN_LEFT,
    NAVIGATION_COMMAND_TURN_RIGHT,
    NAVIGATION_COMMAND_TURN_AROUND,
    NAVIGATION_COMMAND_MOVE_FORWARD,
    NAVIGATION_COMMAND_MOVE_BACKWARD,
    NAVIGATION_COMMAND_ABORT,
    NAVIGATION_COMMAND_STOP,
    NAVIGATION_COMMAND_START,
    NAVIGATION_COMMAND_ABORT_GOAL,
    NAVIGATION_COMMAND_MANUAL_MODE,
    NAVIGATION_COMMAND_AUTO_MODE
};

struct TxData
{
    TxDataType type;
    const char *data;
    const char *typeString()
    {
        switch (type)
        {
        case TX_DATA_TYPE_RC:
            return "RC";
        case TX_DATA_TYPE_LOCATION:
            return "LOCATION";
        case TX_DATA_TYPE_COMPASS:
            return "COMPASS";
        case TX_DATA_TYPE_MOTION:
            return "MOTION";
        case TX_DATA_TYPE_TELEMETRY:
            return "TELEMETRY";
        case TX_DATA_TYPE_SOUND:
            return "SOUND";
        case TX_DATA_TYPE_NAVIGATION:
            return "NAVIGATION";
        case TX_DATA_TYPE_PROPERTIES:
            return "PROPERTIES";
        case TX_DATA_TYPE_STATUS:
            return "STATUS";
        case TX_DATA_TYPE_DEBUG:
            return "DEBUG";
        case TX_DATA_TYPE_ESP_READY:
            return "ESP_READY";
        case TX_DATA_TYPE_ESP_READY_REQUEST:
            return "ESP_READY_REQUEST";
        case TX_DATA_TYPE_ESP_READY_ACK:
            return "ESP_READY_ACK";
        case TX_DATA_TYPE_STM_READY:
            return "STM_READY";
        case TX_DATA_TYPE_STM_READY_REQUEST:
            return "STM_READY_REQUEST";
        case TX_DATA_TYPE_STM_READY_ACK:
            return "STM_READY_ACK";
        case TX_DATA_TYPE_GOAL_REQUEST:
            return "GOAL_REQUEST";
        case TX_DATA_TYPE_GOAL_REQUEST_ACK:
            return "GOAL_REQUEST_ACK";
        case TX_DATA_TYPE_NAVIGATION_COMMAND_REQUEST:
            return "NAVIGATION_COMMAND_REQUEST";
        case TX_DATA_TYPE_NAVIGATION_COMMAND_REQUEST_ACK:
            return "NAVIGATION_COMMAND_REQUEST_ACK";
        case TX_DATA_TYPE_DEVICE_COMMAND_REQUEST:
            return "DEVICE_COMMAND_REQUEST";
        case TX_DATA_TYPE_DEVICE_COMMAND_REQUEST_ACK:
            return "DEVICE_COMMAND_REQUEST_ACK";
        default:
            return "UNKNOWN";
        };
    };
};

typedef void (*DataManagerDataCallback)(TxData);
typedef void (*DataManagerJsonCallback)(JsonVariant);

// class DataManagerClass;

class DataManagerClass
{
private:
    DataManagerDataCallback _callback;
    DataManagerJsonCallback _locationCb;
    DataManagerJsonCallback _motionCb;
    DataManagerJsonCallback _goalRequestCb;
    DataManagerJsonCallback _navigationCommandRequestCb;
    DataManagerJsonCallback _deviceCommandRequestCb;
    Stream *_serial;
    bool _endOfTransmission = false;
    byte _endTagCount = 0;
    String _strBuffer;
    void _parseData();

public:
    void setup(Stream *serial);
    void work();
    void send(TxData data);
    void send(const char *data, TxDataType type);
    void send(String data, TxDataType type);
    void send(JsonVariant data, TxDataType type);
    void onReceiveMotion(DataManagerJsonCallback cb)
    {
        _motionCb = cb;
    }
    void onReceiveLocation(DataManagerJsonCallback cb)
    {
        _locationCb = cb;
    }
    void onReceive(DataManagerDataCallback callback)
    {
        _callback = callback;
    }
    void onReceiveGoalRequest(DataManagerJsonCallback cb)
    {
        _goalRequestCb = cb;
    }
    void onReceiveNavigationCommandRequest(DataManagerJsonCallback cb)
    {
        _navigationCommandRequestCb = cb;
    }
    void onReceiveDeviceCommandRequest(DataManagerJsonCallback cb)
    {
        _deviceCommandRequestCb = cb;
    }
};

extern DataManagerClass dataManager;

#endif // ELYIR_MOWER_DATA_MANAGER_H