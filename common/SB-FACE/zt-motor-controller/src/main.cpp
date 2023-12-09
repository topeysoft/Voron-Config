/*
Reading Values from an RC Receiver using Arduino
Brandon Tsuge
In this example, I demonstrate how to use Arduino to read RC (50Hz PWM) values using pulseIn() and external interrupts.
https://www.theboredrobot.com/post/reading-values-from-an-rc-receiver-using-arduino
 */

#include <Arduino.h>
// #define chIn1 2 // ATTINY85
// #define chIn2 5 // ATTINY85

#define chIn1 4
#define chIn2 6
// #define chIn3 6
// #define chIn4 7
// #define chIn5 8

// #define pwmOut1 3 // ATTINY85
// #define pwmOut2 4 // ATTINY85

#define pwmOut1 9
#define pwmOut2 10
// #define pwmOut3 8
// #define pwmOut4 9
// #define pwmOut5 10

#define pwmMin 0
#define pwmMax 255

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue)
{
    int ch = pulseIn(channelInput, HIGH, 30000);
    if (ch < 100)
        return defaultValue;
    int out = map(ch, 1000, 2000, minLimit, maxLimit);
    return constrain(out, minLimit, maxLimit);
}

// Red the channel and return a boolean value
bool redSwitch(byte channelInput, bool defaultValue)
{
    int intDefaultValue = (defaultValue) ? 100 : 0;
    int ch = readChannel(channelInput, 0, 100, intDefaultValue);
    return (ch > 50);
}

void setup()
{
    Serial.begin(115200);
    pinMode(chIn1, INPUT);
    pinMode(chIn2, INPUT);
    // pinMode(chIn3, INPUT);
    // pinMode(chIn4, INPUT);
    // pinMode(chIn5, INPUT);

    pinMode(pwmOut1, OUTPUT);
    pinMode(pwmOut2, OUTPUT);
    // pinMode(pwmOut3, OUTPUT);
    // pinMode(pwmOut4, OUTPUT);
    // pinMode(pwmOut5, OUTPUT);
}

int ch1Value, ch2Value, ch3Value, ch4Value, ch5Value;

void loop()
{
    ch1Value = readChannel(chIn1, pwmMin, pwmMax, 126);
    ch2Value = readChannel(chIn2, pwmMin, pwmMax, 126);
    // ch3Value = readChannel(chIn3, 0, 255, 126);
    // ch4Value = readChannel(chIn4, 0, 255, 126);
    // ch5Value = readChannel(chIn5, 0, 255, 126);

    analogWrite(pwmOut1, ch1Value);
    analogWrite(pwmOut2, ch2Value);
    // analogWrite(pwmOut3, ch3Value);
    // analogWrite(pwmOut4, ch4Value);
    // analogWrite(pwmOut5, ch5Value);

    // ch5Value = redSwitch(CH5, false);

    Serial.print("Ch1: ");
    Serial.print(ch1Value);
    Serial.print(" Ch2: ");
    Serial.println(ch2Value);
    // Serial.print(" Ch3: ");
    // Serial.print(ch3Value);
    // Serial.print(" Ch4: ");
    // Serial.print(ch4Value);
    // Serial.print(" Ch5: ");
    // Serial.println(ch5Value);
    // delay(500);
}