#ifndef ELIYR_FIREBASE_MANAGER_H
#define ELIYR_FIREBASE_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>

#include "Utils.h"

class FirebaseManagerClass;
extern FirebaseManagerClass firebaseManager;

typedef void (*FirebaseManagerDataCallback)(String path, String eventType, String type, String data);

class FirebaseManagerClass
{
private:
    const char *_api_key;
    const char *_db_url;
    const char *_id_token;
    const char *_refresh_token;
    const char *_email;
    const char *_password;
    int _expiration_time;
    bool _ready;
    const char *_getResolvedPath(String path);

    // const char *_getResolvedPath(const char *path)
    // {
    //     return _getResolvedPath(String(path));
    // }
    volatile bool dataChanged = false;
    String _getID()
    {
        String id = "";
#if defined(ESP8266)
        id = String(ESP.getChipId());
#elif defined(ESP32)
        id = String((uint32_t)ESP.getEfuseMac(), HEX);
#endif
        id.toUpperCase();
        return id;
    }

public:
    void setup(const char *api_key, const char *db_url);
    void setIdTokenCredentials(const char *api_key, const char *db_url);
    void setUserPasswordCredentials(const char *email, const char *password);
    void setDbSecretCredentials(const char *dbSecret);
    // void setup(const char *api_key, const char *db_url, const char *email, const char *password);
    void work();
    String publish(String path, String data);
    String publish(String path, JsonVariant data);
    void subscribe(String path);
    void unsubscribe(String path);
    FirebaseManagerDataCallback _dataCallback; // Do not use this directly, use setDataCallback instead
    void setDataCallback(FirebaseManagerDataCallback dataCallback)
    {
        _dataCallback = dataCallback;
    }
    bool isReady()
    {
        return _ready;
    }
    int getTokenExpirationTime()
    {
        return _expiration_time;
    }
};

#endif // ELIYR_FIREBASE_MANAGER_H