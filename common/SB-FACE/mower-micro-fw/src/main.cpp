// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Arduino.h>
#include "InputManager.h"
#include "LEDManager.h"
#include "SoundManager.h"

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:

// InputManager inputManager;
// LEDManager ledManager;

#define buttonPin 9        // the number of the pushbutton pin
#define batteryPin A0      // the number of the battery pin
#define chargePin 8        // the number of the charge pin
#define buzzerPin 5        // the number of the buzzer pin
#define ledPin 4           // the number of the led pin
#define ledCount 20        // the number of LEDs
#define brightness 50      // the brightness of the LEDs
#define softSwitchOnePin 7 // the number of the soft switch one pin
#define softSwitchTwoPin 6 // the number of the soft switch two pin

void setup()
{
    // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
    // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif

    Serial.begin(9600);
    inputManager.setUavStatusTriggerPin(softSwitchOnePin);
    inputManager.setBatteryStatusTriggerPin(softSwitchTwoPin);
    inputManager.setBatteryMax(27.20);
    inputManager.setBatteryMin(20.0);
    inputManager.setBatteryWarningLevel(25.8);
    inputManager.setBatteryCriticalLevel(24.0);
    inputManager.begin(chargePin, buttonPin, batteryPin);
    ledManager.begin(ledPin, ledCount, NEO_GRB + NEO_KHZ800, brightness);
    soundManager.begin(buzzerPin);
    inputManager.setChargerConnectionListener([](bool connected)
                                              { Serial.println("Charger connected: " + String(connected));
                                              if(connected)
                                                {
                                                    soundManager.chargerConnected();
                                                    ledManager.setChargingMode();
                                                }
                                                else
                                                {
                                                    ledManager.unsetChargingMode();
                                                    soundManager.chargerDisconnected();
                                                } });
    inputManager.setBatteryStatusButtonListener([](bool pressed)
                                                { 
                                                    Serial.println("Battery status button pressed: " + String(pressed));
                                                   if(pressed){ ledManager.setBatteryStatusMode(); 
                                                   } else { ledManager.unsetBatteryStatusMode(); } });
    inputManager.setBatteryWarningListener([]()
                                           { Serial.println("Battery warning");
        if (!inputManager.isCharging())
        {
        soundManager.warning();
        } });
    inputManager.setBatteryCriticalListener([]()
                                            {
                                                //  Serial.println("Battery critical");
                                                // if (!inputManager.isCharging()){
                                                //     soundManager.alert();
                                                // }
                                            });
    inputManager.setBatteryLevelChangeListener([](int level)
                                               { Serial.println("Battery level changed: " + String(level));
                                                ledManager.setBatteryStatus(level);
                                                if (inputManager.isCharging() && level == 100)
                                                {
                                                    soundManager.batteryFull();
                                                } });
    inputManager.setSoftSwitchTriggerChangeListener([](int triggered)
                                                    { 
                                                        Serial.println("Soft switch triggered: " + String(triggered));
                                                        ledManager.clearAll(); });
}

void loop()
{
    inputManager.work();
    ledManager.work();
    soundManager.work();
}
