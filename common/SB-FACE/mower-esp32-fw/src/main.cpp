#include <Arduino.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>
#include "RCManager.h"
#include "DataManager.h"
#include "ApiServerManager.h"
#include "NetworkManager.h"
#include "OTAManager.h"
#include "FirebaseManager.h"
#include <Every.h>

bool ensureAllComponentsAreReady();

Every printNow(5000);
Every sendReadyNow(1000);
Every sendDeviceStatusNow(500);

/*
  Translate iBUS signal to servo - ESP32 version
  This example uses Esp32Servo library (https://github.com/madhephaestus/ESP32Servo) that can be
  downloaded using the Arduino library manager.

  Supports ESP32 boards where serial1 is available (most ESP32 boards).
  Alternatively you can change the code below to use the serial2 port.
  Serial1 port RX/TX connected as follows:
  - RX connected to the iBUS servo pin
  - TX can be left open as the iBUS protocol for servos is one way only
*/

// IBusBM IBus;      // IBus object
// Servo leftServo;  // create servo object to control a servo
// Servo rightServo; // create servo object to control a servo

// Possible PWM GPIO pins on the ESP32: 0(used by on-board button),2,4,5(used by on-board LED),12-19,21-23,25-27,32-33
// #define leftWheelPin 18
// #define rightWheelPin 19

unsigned long _lastStatusSentMillis = 0;
bool _stm_is_ready = false;
bool _esp_is_ready_ack = false;

void setupDataManager()
{
    dataManager.onReceive([](TxData data)
                          { 
    //                         Serial.println("Data received -- "); 
    //                         Serial.print(" Type: "); 
    //                         Serial.println(data.typeString()); 
    // Serial.print(" Data: ");
    // Serial.println(data.data);
    if (data.type == TX_DATA_TYPE_STATUS)
    {
        settingsManager.setStatusJsonString(data.data);
        // Serial.println(data.data);
    }else if(data.type == TX_DATA_TYPE_STM_READY){
        _stm_is_ready = true;
        dataManager.send("ready", TX_DATA_TYPE_STM_READY_ACK);
    } else if(data.type == TX_DATA_TYPE_ESP_READY_ACK){
        _esp_is_ready_ack = true;
    }
    else if (data.type == TX_DATA_TYPE_ESP_READY_REQUEST)
    {
        _esp_is_ready_ack = false;
    }

    if(millis()-_lastStatusSentMillis> 1000){
        _lastStatusSentMillis = millis();
        // Serial.println(settingsManager.getStatusJson());
        // apiServerManager.sendWebSocketMessage(String(data.data), String(data.typeString()));
 } });
    dataManager.setup(&Serial2);
}
void setup()
{
    Serial.begin(115200);
    Serial2.begin(115200);
    Serial.println("AutoMower - By Elyir LLC");
    Serial.println("----------------------------------------");
    settingsManager.setup();
    settingsManager.readSetting("hostname", "elyirmower");
    settingsManager.readSetting("wifi_ap_ssid", "Elyir_Robotix_Mower");
    settingsManager.readSetting("wifi_ap_pass", "elyir1234");
    settingsManager.readSetting("wifi_sta_ssid", "");
    settingsManager.readSetting("wifi_sta_pass", "");
    settingsManager.readSetting("fw_version", "0.0.1-alpha");
    settingsManager.readSetting("fs_version", "0.1.1-alpha");
    settingsManager.readSetting("fw_hash", "");
    settingsManager.readSetting("fs_hash", "");
    settingsManager.readSetting("build_date", "");
    settingsManager.readSetting("user_name", "Elyir LLC");
    settingsManager.readSetting("user_email", "info@elyir.com");
    settingsManager.readSetting("fbEmail", "temi.adeyeri@gmail.com");
    settingsManager.readSetting("fbPass", "Tinbed1!");
    settingsManager.readSetting("fbDbSecret", "kyKn0ZflOAwi6NYdekTMnjBYlv6CqwYh57Gpf7ZH");
    settingsManager.readSetting("fbApiKey", "AIzaSyCxHy8Cw05QPkRPFmT_DlpMkk952yWAbsQ");
    settingsManager.readSetting("fbDbUrl", "https://elyir-d4ede.firebaseio.com");
    settingsManager.readSetting("idToken", "eyJhbGciOiJSUzI1NiIsImtpZCI6IjA2M2E3Y2E0M2MzYzc2MDM2NzRlZGE0YmU5NzcyNWI3M2QwZGMwMWYiLCJ0eXAiOiJKV1QifQ.eyJpc3MiOiJodHRwczovL3NlY3VyZXRva2VuLmdvb2dsZS5jb20vZWx5aXItZDRlZGUiLCJhdWQiOiJlbHlpci1kNGVkZSIsImF1dGhfdGltZSI6MTY1OTcyNjQ4NCwidXNlcl9pZCI6Ill0VGZOOTFBVVFOcmd1dEkxZFoySlJ3bUt3cTIiLCJzdWIiOiJZdFRmTjkxQVVRTnJndXRJMWRaMkpSd21Ld3EyIiwiaWF0IjoxNjU5NzI2NDg0LCJleHAiOjE2NTk3MzAwODQsImVtYWlsIjoidGVtaS5hZGV5ZXJpQGdtYWlsLmNvbSIsImVtYWlsX3ZlcmlmaWVkIjpmYWxzZSwiZmlyZWJhc2UiOnsiaWRlbnRpdGllcyI6eyJlbWFpbCI6WyJ0ZW1pLmFkZXllcmlAZ21haWwuY29tIl19LCJzaWduX2luX3Byb3ZpZGVyIjoicGFzc3dvcmQifX0.bN0YSW_c-bnUFKw2wIgqwEmUswwjuVECLozW_yaEH8e8gSREUilRNe0P_aGAEcGqS-8fx6srkuG_LUbBvA99eAvkNymKDPUmZ66P9_q6jHRJCK6-X9c9zguxt1lYADDLXQNT39cmVl6r01V8YPSRMVE7rf26wO7t1MPYFp93MHHJ_mwbbKjyNcaOpm107WjAFA7VyQXnf6sNPiup3bOrM3Ho48y14K6gqlVIK_CuySd3A2YpcQvvPLcRGSe8lDQW7OqPaWrvdgvvdkcBT7FMEC_wSNWHophL0ANnHKtIrBGc94CWl7vnWTvEQGik6K2BtOsnc8JNpojBWaszIB1dTg");
    settingsManager.readSetting("refToken", "AOEOulZDI4N3QWhdtTjLANf6zZ597pltdcvDv1i0qL-91SIq8744hjdPafcjH1C0nyvt2h2oUbDsj88nLR0v0Ink3RnxbtEnbgEbcBvKujMSWRVhWl-FcjnVHnDLNxIII1_jt3H65NuN_6OESDgPlOFi98ttF3fMtw_0X2Ui0IZ8oGnzD7y6SBvLFtQsTiLde0BcFPjI33UMvQnJNV1VuN7wM9NpF487vA");
    setupDataManager();

    Trace("Setting up network...");
    networkManager.setAPCredentials(settings["wifi_ap_ssid"], settings["wifi_ap_pass"]);
    networkManager.setSTACredentials(settings["wifi_sta_ssid"], settings["wifi_sta_pass"]);
    networkManager.setHostname(settings["hostname"]);
    Trace("Configuring WiFi...");
    networkManager.setup();
    Trace("WiFi setup complete.");
    Trace("Setting up OTA ...");
    otaManager.setup(apiServerManager.getServer());
    Trace("OTA setup complete.");
    Trace("Setting up web server ...");
    apiServerManager.setup();
    Trace("Web server setup complete.");
    Trace("Setting up firebase client ...");
    // firebaseManager.setDbSecretCredentials(settings["fbDbSecret"]);
    firebaseManager.setUserPasswordCredentials(settings["fbEmail"], settings["fbPass"]);
    // firebaseManager.setIdTokenCredentials(settings["idToken"], settings["refToken"]);
    firebaseManager.setDataCallback([](String path, String eventType, String type, String data)
                                    { Trace("Firebase callback"); });
    firebaseManager.subscribe("mower/commands");
    firebaseManager.setup(settings["fbApiKey"], settings["fbDbUrl"]);

    Trace("Firebase client setup complete.");
    pinMode(LED_BUILTIN, OUTPUT); // set LED_BUILTIN pin as output
    dataManager.send("ready", TX_DATA_TYPE_ESP_READY);
    ensureAllComponentsAreReady();
}

bool ensureAllComponentsAreReady()
{
    Trace("Waiting for STM...");
    while (!_stm_is_ready)
    {
        if (printNow())
        {
            Trace("Waiting for STM...");
        }
        if (sendReadyNow())
        {
            dataManager.send("ready", TX_DATA_TYPE_STM_READY_REQUEST);
            dataManager.send("ready", TX_DATA_TYPE_ESP_READY);
        }
        dataManager.work();
    }
    while (!_esp_is_ready_ack)
    {
        if (printNow())
        {
            Trace("Sending ESP32 Ready Message");
        }
        if (sendReadyNow())
        {
            dataManager.send("ready", TX_DATA_TYPE_ESP_READY);
        }
        dataManager.work();
    }
    Trace("STM is ready.");
    return true;
}

void loop()
{
    dataManager.work();
    networkManager.work();
    otaManager.work();
    firebaseManager.work();
    apiServerManager.work();
    digitalWrite(LED_BUILTIN, LOW);
    if (!_esp_is_ready_ack)
    {
        dataManager.send("ready", TX_DATA_TYPE_ESP_READY);
    }

    if (sendDeviceStatusNow())
    {
        if (firebaseManager.isReady())
        {
            JsonVariant statusData = settingsManager.getStatusJson();
            statusData["online"] = true;
            String result = firebaseManager.publish("mower/status", statusData);
            // Serial.print("Publish result: ");
            // Serial.println(result);
        }
        else
        {
            Serial.println("Firebase not ready");
        }
        // Serial.println("Token expiration time: " + String(firebaseManager.getTokenExpirationTime()));

        // String statusStr = settingsManager.getStatusJson();
        // Serial.println("Sending status to all clients");
        // Serial.println(statusStr);
        // events.send(statusStr.c_str(), "status", millis());
        // textToAllAuthWsClients(statusStr, "status");
    }

    // delay(10);
}