#include <Arduino.h>
#include "handler/Wifi_Handler.hpp"

#define SERIAL_PORT 9600

#pragma region WIFI 
    #define WIFI_SSID "Ade"
    #define WIFI_PASSWORD "Ade1234567890"
#pragma endregion
#pragma region MODULES
    #define PIN_BUZZER 1
    #define PIN_
#pragma endregion
#pragma region INIT_FUNCTION
    void init_wifi();
    void init_modules();
#pragma endregion

void setup() {
    Serial.begin(SERIAL_PORT);
    init_wifi();
    init_modules();
}

void loop() {
    
}


void init_wifi(){
    Wifi_Handler wifi(WIFI_SSID, WIFI_PASSWORD, WIFI_STA);
    bool wifiConnected = wifi.connect();
    if(!wifiConnected){
        exit(0);
    }
}

void init_modules(){
    
}

