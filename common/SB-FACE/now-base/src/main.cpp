/**
   ESPNOW - Basic communication - Base
   Date: 26th September 2017
   Author: Arvind Ravulavaru <https://github.com/arvindr21>
   Purpose: ESPNow Communication between a Base ESP32 and multiple ESP32 Rovers
   Description: This sketch consists of the code for the Base module.
   Resources: (A bit outdated)
   a. https://espressif.com/sites/default/files/documentation/esp-now_user_guide_en.pdf
   b. http://www.esploradores.com/practica-6-conexion-esp-now/
   << This Device Base >>
   Flow: Base
   Step 1 : ESPNow Init on Base and set it in STA mode
   Step 2 : Start scanning for Rover ESP32 (we have added a prefix of `rover` to the SSID of rover for an easy setup)
   Step 3 : Once found, add Rover as peer
   Step 4 : Register for send callback
   Step 5 : Start Transmitting data from Base to Rover(s)
   Flow: Rover
   Step 1 : ESPNow Init on Rover
   Step 2 : Update the SSID of Rover with a prefix of `rover`
   Step 3 : Set Rover in AP mode
   Step 4 : Register for receive callback and wait for data
   Step 5 : Once data arrives, print it in the serial monitor
   Note: Base and Rover have been defined to easily understand the setup.
         Based on the ESPNOW API, there is no concept of Base and Rover.
         Any devices can act as base or salve.
  // Sample Serial log with 1 base & 2 rovers
      Found 12 devices
      1: Rover:24:0A:C4:81:CF:A4 [24:0A:C4:81:CF:A5] (-44)
      3: Rover:30:AE:A4:02:6D:CC [30:AE:A4:02:6D:CD] (-55)
      2 Rover(s) found, processing..
      Processing: 24:A:C4:81:CF:A5 Status: Already Paired
      Processing: 30:AE:A4:2:6D:CD Status: Already Paired
      Sending: 9
      Send Status: Success
      Last Packet Sent to: 24:0a:c4:81:cf:a5
      Last Packet Send Status: Delivery Success
      Send Status: Success
      Last Packet Sent to: 30:ae:a4:02:6d:cd
      Last Packet Send Status: Delivery Success
*/

#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include "JC_Button.h"

#include <esp_now.h>

#include "Tracing.h"
#include "NetworkManager.h"
#include "GNSSManager.h"
#include "OTAManager.h"
#include "SettingsManager.h"
#include "BluetoothManager.h"
// #include "RadioManager.h"
#include "WebServerManager.h"
#include "UIStates.h"

// Global copy of rover
#define NUMROVERS 20
esp_now_peer_info_t rovers[NUMROVERS] = {};
int RoverCnt = 0;

#define CHANNEL 1
#define PRINTSCANRESULTS 0

void sendData(uint8_t *data, size_t len);
void scanForRover();
void manageRover();
void broadcastData(uint8_t data);
unsigned long prevMillis = 0;
unsigned long prevLogTime = 0;
unsigned long roverScanFrequency = 10000;
unsigned long logFrequency = 3000;

// This function gets called from the SparkFun Ublox Arduino Library.
// As each RTCM byte comes in you can specify what to do with it
// Useful for passing the RTCM correction data to a radio, Ntrip broadcaster, etc.
const size_t buf_size = 248;
uint8_t buffer[buf_size + 1];
int currIndex = 0;
void SFE_UBLOX_GNSS::processRTCM(uint8_t incoming)
// void GNSSManagerClass::onReceivedRTCM(uint8_t incoming)
{
    // Let's just pretty-print the HEX values for now
    //  if (myGPS.rtcmFrameCounter % 16 == 0)
    //      Serial.println();
    //  Serial.print(" ");
    //  if (incoming < 0x10)
    //  Serial.print("0");
    // Serial.print(incoming, HEX);
    // broadcastData(incoming);
    // Serial.println("Got data: ");
    // Serial.println(incoming, HEX);
    if (RoverCnt > 0)
    { // check if rover channel is defined
        // `rover` is defined
        // Add rover as peer if it has not been added already
        manageRover();
        // pair success or already paired
        // Send data to device
        if (currIndex < buf_size)
        {
            buffer[currIndex] = incoming;
            currIndex++;
        }
        else
        {
            sendData(buffer, buf_size);
            currIndex = 0;
        }
    }
    else
    {
        // No rover found to process
        // Serial.println("Discarding correction message since there is no rover connected");
    }
    if ((millis() - prevMillis) > roverScanFrequency)
    {
        // In the loop we scan for rover
        prevMillis = millis();
        scanForRover();
    }
}

void setupGPSBaseStation()
{
    // networkManager.setAPCredentials(settings["wifi_ap_ssid"], settings["wifi_ap_pass"]);
    // networkManager.setSTACredentials(settings["wifi_sta_ssid"], settings["wifi_sta_pass"]);
    // networkManager.setHostname(settings["hostname"]);
    // Trace("Setting up WiFi...");
    // networkManager.setup();
    // Trace("WiFi setup complete.");
    // // networkManager.setup(ssid, password, settings["hostname"]);
    // otaManager.setup(webServerManager.getServer());
    // // otaManager.setup(settings["hostname"], settings["ota_port"]);
    // webServerManager.setup();
    // gnssManager.setSurveyMode(settings["useSurveyIn"], settings["gpsSvInAcc"], settings["gpsSvInMsec"]);
    gnssManager.setSurveyMode(true, settings["gpsSvInAcc"], settings["gpsSvInMsec"]);
    // gnssManager.setSurveyMode(false, settings["gpsSvInAcc"], settings["gpsSvInMsec"]);
    gnssManager.setPosition(settings["ecefX"], settings["ecefY"], settings["ecefZ"]);
    gnssManager.setupAsBase();

    // gnssManager.setSurveyMode(settings["useSurveyIn"], settings["gpsSvInAcc"], settings["gpsSvInMsec"]);
    // // gnssManager.setSurveyMode(false, 0, 0);
    // Trace("Base Setup: Setting Static Position");
    // gnssManager.setPosition(settings["ecefX"], settings["ecefY"], settings["ecefZ"]);
    // // gnssManager.setPosition(-184941.9219, -4987754, 3957936.25);
    // Trace("Base Setup: Setting up as base");
    // gnssManager.setupAsBase();
    Trace("Base Setup Complete");
}

void runGps()
{
    gnssManager.work();
}

// Init ESP Now with fallback
void InitESPNow()
{
    WiFi.disconnect();
    if (esp_now_init() == ESP_OK)
    {
        Serial.println("ESPNow Init Success");
    }
    else
    {
        Serial.println("ESPNow Init Failed");
        // Retry InitESPNow, add a counte and then restart?
        // InitESPNow();
        // or Simply Restart
        ESP.restart();
    }
}

// Scan for rovers in AP mode
void scanForRover()
{
    int8_t scanResults = WiFi.scanNetworks();
    // reset rovers
    memset(rovers, 0, sizeof(rovers));
    RoverCnt = 0;
    Serial.println("");
    if (scanResults == 0)
    {
        Serial.println("No WiFi devices in AP Mode found");
    }
    else
    {
        Serial.print("Found ");
        Serial.print(scanResults);
        Serial.println(" devices ");
        for (int i = 0; i < scanResults; ++i)
        {
            // Print SSID and RSSI for each device found
            String SSID = WiFi.SSID(i);
            int32_t RSSI = WiFi.RSSI(i);
            String BSSIDstr = WiFi.BSSIDstr(i);

            if (PRINTSCANRESULTS)
            {
                Serial.print(i + 1);
                Serial.print(": ");
                Serial.print(SSID);
                Serial.print(" [");
                Serial.print(BSSIDstr);
                Serial.print("]");
                Serial.print(" (");
                Serial.print(RSSI);
                Serial.print(")");
                Serial.println("");
            }
            // delay(10);
            // Check if the current device starts with `Rover`
            if (SSID.indexOf("RTK_Rover") == 0)
            {
                // SSID of interest
                Serial.print(i + 1);
                Serial.print(": ");
                Serial.print(SSID);
                Serial.print(" [");
                Serial.print(BSSIDstr);
                Serial.print("]");
                Serial.print(" (");
                Serial.print(RSSI);
                Serial.print(")");
                Serial.println("");
                // Get BSSID => Mac Address of the Rover
                int mac[6];

                if (6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]))
                {
                    for (int ii = 0; ii < 6; ++ii)
                    {
                        rovers[RoverCnt].peer_addr[ii] = (uint8_t)mac[ii];
                    }
                }
                rovers[RoverCnt].channel = CHANNEL; // pick a channel
                rovers[RoverCnt].encrypt = 0;       // no encryption
                RoverCnt++;
            }
        }
    }

    if (RoverCnt > 0)
    {
        Serial.print(RoverCnt);
        Serial.println(" Rover(s) found, processing..");
    }
    else
    {
        Serial.print("No Rover found, but I will again in ");
        Serial.print(roverScanFrequency / 1000);
        Serial.println(" seconds");
    }

    // clean up ram
    WiFi.scanDelete();
}

// Check if the rover is already paired with the base.
// If not, pair the rover with base
void manageRover()
{
    if (RoverCnt > 0)
    {
        for (int i = 0; i < RoverCnt; i++)
        {
            Serial.print("Processing: ");
            for (int ii = 0; ii < 6; ++ii)
            {
                Serial.print((uint8_t)rovers[i].peer_addr[ii], HEX);
                if (ii != 5)
                    Serial.print(":");
            }
            Serial.print(" Status: ");
            // check if the peer exists
            bool exists = esp_now_is_peer_exist(rovers[i].peer_addr);
            if (exists)
            {
                // Rover already paired.
                Serial.println("Already Paired");
            }
            else
            {
                // Rover not paired, attempt pair
                esp_err_t addStatus = esp_now_add_peer(&rovers[i]);
                if (addStatus == ESP_OK)
                {
                    // Pair success
                    Serial.println("Pair success");
                }
                else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT)
                {
                    // How did we get so far!!
                    Serial.println("ESPNOW Not Init");
                }
                else if (addStatus == ESP_ERR_ESPNOW_ARG)
                {
                    Serial.println("Add Peer - Invalid Argument");
                }
                else if (addStatus == ESP_ERR_ESPNOW_FULL)
                {
                    Serial.println("Peer list full");
                }
                else if (addStatus == ESP_ERR_ESPNOW_NO_MEM)
                {
                    Serial.println("Out of memory");
                }
                else if (addStatus == ESP_ERR_ESPNOW_EXIST)
                {
                    Serial.println("Peer Exists");
                }
                else
                {
                    Serial.println("Not sure what happened");
                }
                // delay(100);
            }
        }
    }
    else
    {
        // No rover found to process
        Serial.println("No Rover found to process");
    }
}

// uint8_t data[15];

// void readData()
// {
// //    memcpy((uint8_t) "Anybody there?"
// }
// send data
void broadcastData(uint8_t *data, size_t len)
{
    uint8_t b_macAddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    esp_err_t result = esp_now_send(b_macAddr, data, len);
    Serial.print("Send Status: ");
    if (result == ESP_OK)
    {
        Serial.println("Success");
    }
    else if (result == ESP_ERR_ESPNOW_NOT_INIT)
    {
        // How did we get so far!!
        Serial.println("ESPNOW not Init.");
    }
    else if (result == ESP_ERR_ESPNOW_ARG)
    {
        Serial.println("Invalid Argument");
    }
    else if (result == ESP_ERR_ESPNOW_INTERNAL)
    {
        Serial.println("Internal Error");
    }
    else if (result == ESP_ERR_ESPNOW_NO_MEM)
    {
        Serial.println("ESP_ERR_ESPNOW_NO_MEM");
    }
    else if (result == ESP_ERR_ESPNOW_NOT_FOUND)
    {
        Serial.println("Peer not found.");
    }
    else
    {
        Serial.println("Not sure what happened");
    }
    // delay(100);
}
void sendData(uint8_t *data, size_t len)
{
    // data++;
    for (int i = 0; i < RoverCnt; i++)
    {
        const uint8_t *peer_addr = rovers[i].peer_addr;
        if (i == 0)
        { // print only for first rover
          // Serial.print("Sending: ");
          // Serial.println(data);
        }
        // esp_err_t result = esp_now_send(peer_addr, data, len);
        esp_err_t result = esp_now_send(peer_addr, data, len);
        Serial.print("Send Status: ");
        if (result == ESP_OK)
        {
            Serial.println("Success");
        }
        else if (result == ESP_ERR_ESPNOW_NOT_INIT)
        {
            // How did we get so far!!
            Serial.println("ESPNOW not Init.");
        }
        else if (result == ESP_ERR_ESPNOW_ARG)
        {
            Serial.println("Invalid Argument");
        }
        else if (result == ESP_ERR_ESPNOW_INTERNAL)
        {
            Serial.println("Internal Error");
        }
        else if (result == ESP_ERR_ESPNOW_NO_MEM)
        {
            Serial.println("ESP_ERR_ESPNOW_NO_MEM");
        }
        else if (result == ESP_ERR_ESPNOW_NOT_FOUND)
        {
            Serial.println("Peer not found.");
        }
        else
        {
            Serial.println("Not sure what happened");
        }
        // delay(100);
    }
}

// callback when data is sent from Base to Rover
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print("Last Packet Sent to: ");
    Serial.println(macStr);
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
    Serial.begin(115200);
    // Set device in STA mode to begin with
    WiFi.mode(WIFI_STA);
    Serial.println("Elyir GPS-RTK2 Base Station (Using ESPNow)");
    settingsManager.setup();
    settingsManager.readSetting("casterPort", 0);
    settingsManager.readSetting("casterHost", "");
    settingsManager.readSetting("hostname", "elyircaster");
    settingsManager.readSetting("ntrip_sName", "");
    settingsManager.readSetting("rtk_mntpnt_pw", "");
    settingsManager.readSetting("rtk_mntpnt", "");
    settingsManager.readSetting("ecefX", -184941.9219);
    settingsManager.readSetting("ecefY", -4987754);
    settingsManager.readSetting("ecefZ", 3957936.25);
    settingsManager.readSetting("useSurveyIn", true);
    settingsManager.readSetting("gpsSvInAcc", 5.0);
    settingsManager.readSetting("gpsSvInMsec", 60000);
    settingsManager.readSetting("rtk_user", "");
    settingsManager.readSetting("rtk_user_pw", "");
    settingsManager.readSetting("rtk_svr_name", "");
    settingsManager.readSetting("wifi_ap_ssid", "Elyir_RTK_BaseStation");
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
    settingsManager.readSetting("connectNtrip", false);
    settingsManager.readSetting("connectWs", false);
    settingsManager.readSetting("nrf24Adr", "00001");
    // settingsManager.readSetting("nrf24Ce", 15);
    // settingsManager.readSetting("nrf24Csn", 14);
    ;
    // Print settings for debug purposes
    serializeJson(settings, Serial);
    // This is the mac address of the Base in Station Mode
    Serial.println();
    Serial.print("STA MAC: ");
    Serial.println(WiFi.macAddress());
    // Init ESPNow with a fallback logic
    InitESPNow();
    setupGPSBaseStation();
    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);
}
void logData()
{
    if ((millis() - prevLogTime) > logFrequency)
    {
        // In the loop we scan for rover
        prevLogTime = millis();
        gnssManager.printPositionData();
        // Serial.print(" Accuracy: ");
        // Serial.print((String)myGPS.svin.meanAccuracy);
        // Serial.println();
    }
}
void loop()
{
    runGps();
    logData();

    // If Rover is found, it would be populated in `rover` variable
    // We will check if `rover` is defined and then we proceed further
    // if (RoverCnt > 0)
    // { // check if rover channel is defined
    //     // `rover` is defined
    //     // Add rover as peer if it has not been added already
    //     manageRover();
    //     // pair success or already paired
    //     // Send data to device
    //     // sendData();
    // }
    // else
    // {
    //     // No rover found to process
    // }

    // wait for 3seconds to run the logic again
    // delay(1000);
}