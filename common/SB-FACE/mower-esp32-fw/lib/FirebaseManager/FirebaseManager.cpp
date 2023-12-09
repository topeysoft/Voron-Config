#include "FirebaseManager.h"
#include <Firebase_ESP_Client.h>
// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

FirebaseManagerClass firebaseManager;

FirebaseData fbdo;
FirebaseData stream;

FirebaseAuth auth;
FirebaseConfig config;
DynamicJsonDocument _subscribedPaths(200);

// unsigned long sendDataPrevMillis = 0;

// String parentPath = "/test/stream/data";
// String childPath[2] = {"/node1", "/node2"};

// int count = 0;

JsonObject _parseToken(const char *jwt)
{
    unsigned char tokenDataString[200];
    base64Decode((unsigned char *)jwt, tokenDataString);
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, tokenDataString);
    return doc.as<JsonObject>();
}
void streamCallback(MultiPathStream stream)
{
    Serial.print("Stream callback: ");
    Serial.println(stream.dataPath.c_str());
    for (JsonVariant value : _subscribedPaths.as<JsonArray>())
    {
        const char *path = value.as<char *>();
        if (stream.get(path))
        {
            // Serial.printf("path: %s, event: %s, type: %s, value: %s%s", stream.dataPath.c_str(), stream.eventType.c_str(), stream.type.c_str(), stream.value.c_str(), i < numChild - 1 ? "\n" : "");
            firebaseManager._dataCallback(stream.dataPath.c_str(), stream.eventType.c_str(), stream.type.c_str(), stream.value.c_str());
        }
    }
    // dataChanged = true;
}

void streamTimeoutCallback(bool timeout)
{
    if (timeout)
        Serial.println("stream timed out, resuming...\n");

    if (!stream.httpConnected())
        Serial.printf("error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
}

void FirebaseManagerClass::work()
{
    _ready = Firebase.ready();
    if (dataChanged)
    {
        dataChanged = false;
        // When stream data is available, do anything here...
    }
}

String FirebaseManagerClass::publish(String path, JsonVariant data)
{
    FirebaseJson json;
    for (JsonPair kv : data.as<JsonObject>())
    {
        json.set(kv.key().c_str(), kv.value().as<String>());
    }
    // Serial.printf("Sending -- Current UID: %s\n", auth.token.uid.c_str());
    bool sent = Firebase.RTDB.setJSONAsync(&fbdo, _getResolvedPath(path), &json);
    return sent ? "ok" : String(fbdo.errorReason().c_str());
}

String FirebaseManagerClass::publish(String path, String data)
{
    // Serial.printf("Sending -- Current UID: %s\n", auth.token.uid.c_str());
    bool sent = Firebase.RTDB.setStringAsync(&fbdo, _getResolvedPath(path), data);
    return sent ? "ok" : String(fbdo.errorReason().c_str());
}
const char *FirebaseManagerClass::_getResolvedPath(String pathSufix)
{
    String path = "/" + String(auth.token.uid.c_str()) + "/" + _getID() + "/" + pathSufix;
    path.replace("//", "/");
    return path.c_str();
}

void FirebaseManagerClass::setIdTokenCredentials(const char *id_token, const char *refresh_token)
{
    _id_token = id_token;
    _refresh_token = refresh_token;
    _expiration_time = 3600;
    // JsonObject tokenData = _parseToken(_id_token);
    // _expiration_time = tokenData["exp"].as<int>() - tokenData["iat"].as<int>();
    // if (!_expiration_time)
    // {
    //     _expiration_time = 3600;
    // };
    Firebase.setIdToken(&config, _id_token, _expiration_time, _refresh_token);

    // To refresh the token 15 minutes before expired
    config.signer.preRefreshSeconds = _expiration_time - 5 * 60;
}
void FirebaseManagerClass::setDbSecretCredentials(const char *dbSecret)
{
    config.signer.tokens.legacy_token = dbSecret;
}
void FirebaseManagerClass::setUserPasswordCredentials(const char *email, const char *password)
{
    _email = email;
    _password = password;
    auth.user.email = email;
    auth.user.password = password;
}
void FirebaseManagerClass::setup(const char *api_key, const char *db_url)
{
    _api_key = api_key;
    _db_url = db_url;

    /* Assign the API key (required) */
    config.api_key = _api_key;
    /* Assign the RTDB URL */
    config.database_url = _db_url;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    struct tm timeinfo;
    while (!getLocalTime(&timeinfo))
    {
        Serial.println("Setting time zone");
        configTime(-5 * 3600, 3600, "pool.ntp.org"); // change accordingly to your timezone
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    Firebase.begin(&config, &auth);
}
void FirebaseManagerClass::subscribe(String path)
{
    _subscribedPaths[_getResolvedPath(path)] = true;
}
void FirebaseManagerClass::unsubscribe(String path)
{
    _subscribedPaths.remove(_getResolvedPath(path));
}