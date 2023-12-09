#include "DataManager.h"

DataManagerClass dataManager;

void DataManagerClass::setup(Stream *serial)
{
    _serial = serial;
    _endOfTransmission = false;
    _endTagCount = 0;
    _strBuffer = "";
    // _serial->begin(baudrate);
}

void DataManagerClass::_parseData()
{
    StaticJsonDocument<1024> json;
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(json, _strBuffer);
    if (!error)
    {
        TxData txData;
        txData.type = json["type"];
        txData.data = json["data"].as<char *>();
        if (_callback)
        {
            _callback(txData);
        }
        StaticJsonDocument<1024> dataJson;
        // Deserialize the JSON document
        DeserializationError dataError = deserializeJson(dataJson, json["data"]);

        if (!dataError)
        {

            switch (txData.type)
            {
            case TX_DATA_TYPE_LOCATION:
                if (_locationCb)
                {
                    _locationCb(dataJson);
                }
                break;
            case TX_DATA_TYPE_GOAL_REQUEST:

                if (_goalRequestCb)
                {
                    _goalRequestCb(dataJson);
                }
                break;

            case TX_DATA_TYPE_MOTION:

                if (_motionCb)
                {
                    _motionCb(dataJson);
                }
                break;
            case TX_DATA_TYPE_NAVIGATION_COMMAND_REQUEST:

                if (_navigationCommandRequestCb)
                {
                    _navigationCommandRequestCb(dataJson);
                }
                break;
            case TX_DATA_TYPE_DEVICE_COMMAND_REQUEST:

                if (_deviceCommandRequestCb)
                {
                    _deviceCommandRequestCb(dataJson);
                }
                break;
            default:
                break;
            }
        }
    }
    _strBuffer = "";
}
void DataManagerClass::work()
{

    if (_serial->available())
    {
        char c = _serial->read();
        if (c == '\n')
        {
            _endTagCount++;
            if (_endTagCount >= 3)
            {
                _parseData();
                _endTagCount = 0;
                _endOfTransmission = true;
            }
        }
        else
        {
            _strBuffer += c;
            _endTagCount = 0;
            _endOfTransmission = false;
        }
    }
}
void DataManagerClass::send(TxData data)
{
    StaticJsonDocument<200> json;
    json["type"] = data.type;
    json["data"] = data.data;
    String jsonStr;
    serializeJson(json, jsonStr);
    _serial->write((jsonStr + String("\n\n\n")).c_str());
}
void DataManagerClass::send(const char *data, TxDataType type)
{
    TxData txData;
    txData.type = type;
    txData.data = (char *)data;
    send(txData);
}
void DataManagerClass::send(String data, TxDataType type)
{
    send(data.c_str(), type);
}
void DataManagerClass::send(JsonVariant data, TxDataType type)
{
    TxData txData;
    txData.type = type;
    String json;
    serializeJson(data, json);
    txData.data = (char *)json.c_str();
    send(txData);
}
