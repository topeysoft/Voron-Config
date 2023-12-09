#include <Arduino.h>
#include "lvgl_hal.h"
#include "pinout.h"
#include "SettingsManager.h"

#include "ui/ui.h"

// Hardware init
#ifdef I2C0_SUPPORT
TwoWire i2c0 = TwoWire(0);
// TwoWire i2c1 = TwoWire(1);
#endif

knomi_config_t knomi_config = {
    .sta_ssid = "",
    .sta_pwd = "",
    .sta_auth = WIFI_AUTH_WPA2_PSK,
    .ap_ssid = AP_SSID, // Create a SSID for BTT KNOMI Access Point
    .ap_pwd = AP_PWD,   // Create Password for BTT KNOMI AP
    .hostname = HOSTNAME,
    .moonraker_ip = "0.0.0.0",
    .mode = "ap",
    .theme_color = lv_color_hex(LV_DEFAULT_COLOR),
};

void lvgl_ui_task(void *parameter);
void lis2dw12_task(void *parameter);
void wifi_task(void *parameter);
void moonraker_task(void *parameter);
void setup()
{
    Serial.begin(115200);
    while (!Serial)
        delay(10);
    Serial.println("\r\n\r\n------------- Knomi startup -----------\r\n");
    Serial.println("SPI Flash: ");
    Serial.print("  Size: ");
    Serial.println(ESP.getFlashChipSize());
    Serial.print("  Speed: ");
    Serial.println(ESP.getFlashChipSpeed());
    Serial.print("  Mode: ");
    Serial.println(ESP.getFlashChipMode());
    Serial.println("SPI PSRAM: ");
    Serial.print("  Found: ");
    Serial.println(psramFound());
    Serial.print("  Size: ");
    Serial.println(ESP.getPsramSize());
    Serial.println("\r\n\r\n------------------------------------------\r\n");

    settingsManager.setup();
    settingsManager.readSetting("hostname", "elyir-3d-printer");
    settingsManager.readSetting("wifi_ap_ssid", "Elyir-3D-Printer");
    settingsManager.readSetting("wifi_ap_pass", "elyir1234");
    settingsManager.readSetting("wifi_sta_ssid", "");
    settingsManager.readSetting("wifi_sta_pass", "");
    settingsManager.readSetting("wifi_mode", "ap");
    settingsManager.readSetting("moonraker_host", "troodon-v2.local");

    knomi_config.sta_ssid = settings["wifi_sta_ssid"].as<String>();
    knomi_config.sta_pwd = settings["wifi_sta_pass"].as<String>();
    knomi_config.ap_ssid = settings["wifi_ap_ssid"].as<String>();
    knomi_config.ap_pwd = settings["wifi_ap_pass"].as<String>();
    knomi_config.hostname = settings["hostname"].as<String>();
    knomi_config.moonraker_ip = settings["moonraker_host"].as<String>();
    knomi_config.mode = settings["wifi_mode"].as<String>();
    knomi_config.theme_color = lv_color_hex(LV_DEFAULT_COLOR);
    serializeJson(settings, Serial);

#ifdef I2C0_SUPPORT
    i2c0.begin(I2C0_SDA_PIN, I2C0_SCL_PIN, I2C0_SPEED);
    // i2c1.begin(I2C1_SDA_PIN, I2C1_SCL_PIN, I2C1_SPEED);
#endif

    xTaskCreate(lvgl_ui_task, "lvgl ui",
                4096, // Stack size (bytes)
                NULL, // Parameter to pass
                10,   // Task priority
                NULL  // Task handle
    );

#ifdef LIS2DW_SUPPORT
    xTaskCreate(lis2dw12_task, "lis2dw12",
                4096, // Stack size (bytes)
                NULL, // Parameter to pass
                9,    // Task priority
                NULL  // Task handle
    );
#endif

    xTaskCreate(wifi_task, "wifi",
                4096, // Stack size (bytes)
                NULL, // Parameter to pass
                8,    // Task priority
                NULL  // Task handle
    );

    xTaskCreate(moonraker_task, "moonraker",
                4096, // Stack size (bytes)
                NULL, // Parameter to pass
                7,    // Task priority
                NULL  // Task handle
    );
}

void loop()
{
}
