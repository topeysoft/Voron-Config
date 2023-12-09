#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Every.h>
// #include <ESP32Servo.h>
#define DebugSerial Serial4
#define RcSerial Serial4
#define DataSerial Serial2
#include "Utils.h"
#include "RCManager.h"
#include "DataManager.h"
#include "NavigationManager.h"
#include "SensesManager.h"
#include "SoundManager.h"
#include "Properties.h"
#include "MotionManager.h"

bool ensureAllComponentsAreReady();

Every printNow(10000);
Every printMotionNow(1000);
Every sendEventsNow(200);
Every sendReadyNow(1000);

#define leftWheelPin PE7
#define rightWheelPin PE8
#define voltagePin PC1
#define chargerPin PC0
#define PIEZO_PIN PE6

unsigned long _lastRcDataPrinted = 0;
DataManagerClass locationDataManager;
SoftwareSerial LocationDataSerial(PE5, PE4);

int previousChannelOneValue = 1000;
bool _esp_is_ready = false;
bool _stm_is_ready_ack = false;

void setGoal(JsonVariant data)
{
    DebugSerial.println("Setting goal");
    Pose goal = navigationManager.getPose();
    goal.position.lat = data["lat"].as<double>();
    goal.position.lon = data["lon"].as<double>();
    goal.orientation.yaw = data["yaw"].as<int>();
}
void setCommand(JsonVariant data)
{
    DebugSerial.println("Setting naviation command");
    int command = data["command"].as<int>();
    switch (command)
    {
    case NAVIGATION_COMMAND_TURN_LEFT:
        navigationManager.turnLeft();
        break;
    case NAVIGATION_COMMAND_TURN_RIGHT:
        navigationManager.turnRight();
        break;
    case NAVIGATION_COMMAND_TURN_AROUND:
        navigationManager.turnAround();
        break;
    case NAVIGATION_COMMAND_MOVE_FORWARD:
        navigationManager.moveForward();
        break;
    case NAVIGATION_COMMAND_MOVE_BACKWARD:
        navigationManager.moveBackward();
        break;
    case NAVIGATION_COMMAND_STOP:
        navigationManager.stop();
        break;
    case NAVIGATION_COMMAND_AUTO_MODE:
        navigationManager.enableAutoMode();
        break;
    case NAVIGATION_COMMAND_MANUAL_MODE:
        navigationManager.enableManualMode();
        break;
    case NAVIGATION_COMMAND_ABORT:
        navigationManager.abort();
        break;
    default:
        break;
    }
}

void setup()
{
    DebugSerial.begin(115200); // debug info
    DataSerial.begin(115200);
    LocationDataSerial.begin(115200);
    Wire.setSDA(PB9);
    Wire.setSCL(PB8);
    Wire.begin();

    pinMode(LED_BUILTIN, OUTPUT); // set LED_BUILTING pin as output
    navigationManager.setup();
    navigationManager.setPoseUpdateCallback([](Pose pose, Pose goal)
                                            {
        DebugSerial.print("Pose -- ");
        DebugSerial.print(" Yaw: ");
        DebugSerial.print(pose.orientation.yaw); 
        DebugSerial.print(" Goal --  ");
        DebugSerial.print(" Yaw: ");
        DebugSerial.println(goal.orientation.yaw); });
    navigationManager.setGoalReachedCallback([](Pose pose)
                                             { DebugSerial.println("Goal reached"); });
    navigationManager.setMoveHandler([](int left, int right)
                                     {
                                        if(printMotionNow()){
                                        DebugSerial.print("Moving -- Left: ");
                                        DebugSerial.print(left);
                                        DebugSerial.print(" Right: ");
                                        DebugSerial.println(right);
                                        }
                                         motionManager.move(left, right); });
    motionManager.setup(leftWheelPin, rightWheelPin);
    rcManager.onReceive([](int *data)
                        {
        int count = 10; // rcManager.getChannelCount();
        // if (millis() - _lastRcDataPrinted >= 1000)
        // {
        //     _lastRcDataPrinted = millis();
        //     digitalWrite(LED_BUILTIN, HIGH);
        //     // DebugSerial.print("RC data: ");
        //     for (size_t i = 0; i < count; i++)
        //     {
        //         DebugSerial.print("CH" + String(i + 1) + ": ");
        //         DebugSerial.print(data[i]);
        //         DebugSerial.print(" ");
        //     }
        //     DebugSerial.println();
        //     DebugSerial.println("----------------------------------------------------");
        // }

        if (data[6] != previousChannelOneValue)
        {
            previousChannelOneValue = data[6];
           if(data[6] > 1500 ){
            DebugSerial.println("Channel 7: " + String(data[6]));
                // setGoal();
           }
        }
            // previousChannelOneVal = data[0]; // rcManager.getChannel(0);
        int right = data[1]; // rcManager.getChannel(1);
                             //  leftServo.writeMicroseconds(left);
                             //  rightServo.writeMicroseconds(right);

                             DebugSerial.print(""); });
    rcManager.setup(&RcSerial, IBUSBM_NOTIMER, &Serial1);
    dataManager.setup(&DataSerial);
    locationDataManager.setup(&LocationDataSerial);
    sensesManager.setup();
    sensesManager.setVoltageSensor(voltagePin, 12.8, 12.0);
    sensesManager.setChargerSensor(chargerPin, 15.0);
    sensesManager.setReadyCallback([]()
                                   {
        DebugSerial.println("Senses ready");
        navigationManager.resetGoal(); });

    locationDataManager.onReceiveLocation([](JsonVariant data)
                                          {
                                      sensesManager.setPosition(data["lat"].as<double>(), data["lon"].as<double>(), data["alt"].as<double>(), data["acc"].as<double>());
                                          DebugSerial.print("Location received --  ");
                                    //   DebugSerial.print("Lat: ");
                                    //   printDouble(&DebugSerial, data["lat"].as<double>(), 10000000000000);
                                    //   DebugSerial.print(" Lon: ");
                                    //   printDouble(&DebugSerial, data["lon"].as<double>(), 10000000000000);
                                    //   DebugSerial.print(" Acc: ");
                                    //   printDouble(&DebugSerial, data["acc"].as<double>(), 10000000000000);
                                    //   DebugSerial.println();
                                      DebugSerial.print(""); });
    dataManager.onReceiveGoalRequest([](JsonVariant data)
                                     { 
                                setGoal(data);
                                 dataManager.send("ack", TX_DATA_TYPE_GOAL_REQUEST_ACK); });
    dataManager.onReceiveNavigationCommandRequest([](JsonVariant data)
                                                  { setCommand(data);
                                                        dataManager.send("ack", TX_DATA_TYPE_NAVIGATION_COMMAND_REQUEST_ACK); });
    dataManager.onReceive([](TxData data)
                          {
        DebugSerial.println("Data received -- ");
        DebugSerial.print(" Type: ");
        DebugSerial.println(data.typeString());
        DebugSerial.print(" Data: ");
        DebugSerial.println(data.data);
        if (data.type == TX_DATA_TYPE_ESP_READY)
        {
            _esp_is_ready = true;
            dataManager.send("ready", TX_DATA_TYPE_ESP_READY_ACK);
        }
        else if (data.type == TX_DATA_TYPE_STM_READY_ACK)
        {
            _stm_is_ready_ack = true;
        }
        else if (data.type == TX_DATA_TYPE_STM_READY_REQUEST)
        {
            _stm_is_ready_ack = false;
        } });
    soundManager.setup(PIEZO_PIN);
    soundManager.playStartup();
    DebugSerial.println("STM32 Started");
    delay(1000);
    soundManager.playStmReady();
    DebugSerial.println("STM32 is ready");
    dataManager.send("ready", TX_DATA_TYPE_STM_READY);
    ensureAllComponentsAreReady();
}

bool ensureAllComponentsAreReady()
{
    DebugSerial.println("Waiting for ESP32...");
    while (!_esp_is_ready)
    {
        if (printNow())
        {
            DebugSerial.println("Waiting for ESP32...");
        }
        if (sendReadyNow())
        {
            dataManager.send("ready", TX_DATA_TYPE_ESP_READY_REQUEST);
            dataManager.send("ready", TX_DATA_TYPE_STM_READY);
        }
        dataManager.work();
    }
    while (!_stm_is_ready_ack)
    {
        if (printNow())
        {
            DebugSerial.println("Sending STM32 Ready Message");
        }
        if (sendReadyNow())
        {
            dataManager.send("ready", TX_DATA_TYPE_STM_READY);
        }
        dataManager.work();
    }
    delay(1000);
    soundManager.playEspReady();
    DebugSerial.println("ESP32 is ready");
    return true;
}
void loop()
{
    rcManager.work();
    dataManager.work();
    navigationManager.work();
    motionManager.work();
    locationDataManager.work();
    sensesManager.work();

    digitalWrite(LED_BUILTIN, LOW);
    if (printNow())
    {

        Orientation orient = sensesManager.getOrientation();
        Position position = sensesManager.getPosition();
        DebugSerial.print("Orientation: ");
        DebugSerial.print("Pitch: ");
        DebugSerial.print(orient.pitch);
        DebugSerial.print(" Roll: ");
        DebugSerial.print(orient.roll);
        DebugSerial.print(" Yaw: ");
        DebugSerial.print(orient.yaw);
        DebugSerial.println();
        DebugSerial.print("Position: ");
        DebugSerial.print(" Lat: ");
        printDouble(&DebugSerial, position.lat, 10000000000000);
        DebugSerial.print(" Lon: ");
        printDouble(&DebugSerial, position.lon, 10000000000000);
        DebugSerial.print(" Alt: ");
        printDouble(&DebugSerial, position.alt, 10000000000000);
        DebugSerial.print(" Acc: ");
        printDouble(&DebugSerial, position.acc, 10000000000000);
        DebugSerial.println();
        double voltage = sensesManager.getVoltage();
        int voltagePercent = sensesManager.getVoltagePercent();
        DebugSerial.print("Voltage: ");
        DebugSerial.print(voltage);
        DebugSerial.print("v: ");
        DebugSerial.print(voltagePercent);
        DebugSerial.print("%");
        DebugSerial.println();
    }
    if (sendEventsNow())
    {

        Orientation orient = sensesManager.getOrientation();
        Position position = sensesManager.getPosition();
        double voltage = sensesManager.getVoltage();
        int voltagePercent = sensesManager.getVoltagePercent();
        StaticJsonDocument<200> root;
        root["pitch"] = orient.pitch;
        root["roll"] = orient.roll;
        root["yaw"] = orient.yaw;
        root["lat"] = position.lat;
        root["lon"] = position.lon;
        root["alt"] = position.alt;
        root["acc"] = position.acc;
        root["battery_voltage"] = voltage;
        root["battery_level"] = voltagePercent;
        root["chargerConnected"] = sensesManager.isChargerConnected();
        root["chargerVoltage"] = sensesManager.getChargerVoltage();
        dataManager.send(root, TX_DATA_TYPE_STATUS);
    }
    if (!_stm_is_ready_ack)
    {
        dataManager.send("ready", TX_DATA_TYPE_STM_READY);
    }

    // data.type = DATA_TYPE_MOTION;
    // dataManager.send(data);
    // if (DataSerial.available())
    // {
    //     DebugSerial.println("Got String from DataSerial");
    //     String data = DataSerial.readString();
    //     DebugSerial.println(data);
    // }
}
