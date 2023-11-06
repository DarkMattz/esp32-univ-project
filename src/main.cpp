#include <Arduino.h>
#include "Wifi.hpp"

#define WIFI_SSID "Ade"
#define WIFI_PASSWORD "Ade1234567890"
#define SERIAL_PORT 9600

void init_wifi(){
    Wifi_Handler wifi(WIFI_SSID, WIFI_PASSWORD, WIFI_STA);
    bool wifiConnected = wifi.connect();
    if(!wifiConnected){
        exit(0);
    }
}

void setup() {
    Serial.begin(SERIAL_PORT);
    init_wifi();
}

void loop() {
  
}

