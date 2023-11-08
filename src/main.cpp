#include <Arduino.h>
#include "handler/Wifi_Handler.hpp"
#include <Arduino_MQTT_Client.h>
#include <time.h>

#define SERIAL_PORT 9600

#pragma region WIFI 
    #define WIFI_SSID "Ade"
    #define WIFI_PASSWORD "Ade1234567890"
#pragma endregion
#pragma region MODULES
    #define PIN_BUZZER 22
    #define PIN_SENSOR 2
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
    time_t t;
    t = time(NULL);
    tm* t_ptr = localtime(&t);
    Serial.println(asctime(t_ptr));
}


void init_wifi(){
    Wifi_Handler wifi(WIFI_SSID, WIFI_PASSWORD, WIFI_STA);
    bool wifiConnected = wifi.connect();
    if(!wifiConnected){
        exit(0);
    }
}

void init_modules(){
    pinMode(PIN_SENSOR, INPUT);
    pinMode(PIN_BUZZER, OUTPUT);
}

