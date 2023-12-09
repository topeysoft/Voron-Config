   
   
   
   ESPNOW - Basic communication - Base
   Date: 26th September 2017
   Author: Arvind Ravulavaru <https://github.com/arvindr21>
   Purpose: ESPNow Communication between a Base ESP32 and multiple ESP32 Rovers
   Description: This sketch consists of the code for the Base module.
   Resources: (A bit outdated)
   a. https://espressif.com/sites/default/files/documentation/esp-now_user_guide_en.pdf
   b. http://www.esploradores.com/practica-6-conexion-esp-now/
This Device Base
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
