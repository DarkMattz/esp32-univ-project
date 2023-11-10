#include <Arduino.h>
#include <Update.h>
#include <time.h>
#include <HttpClient.h>
#include <URLEncoder.h>
#include "handler/ThingsBoardHandler.hpp"
#include "handler/WifiHandler.hpp"
#include "model/SensorModel.hpp"

#define SERIAL_PORT 9600
#define BLYNK_AUTH 

#pragma region WIFI 
    #define WIFI_SSID "Jevon"
    #define WIFI_PASSWORD "twwg5855"
#pragma endregion
#pragma region MODULES
    #define PIN_BUZZER 22
    #define PIN_SENSOR 2
    #define INTERVAL_MILISECOND 5000
#pragma endregion
#pragma region INIT_FUNCTION
    void init_wifi();
    void init_modules();
#pragma endregion

WifiHandler *wifi = nullptr;
SensorModel *sensor;
long long watchTime;

void setup() {
    Serial.begin(SERIAL_PORT);
    Serial.println("Starting Microcontroller...");
    watchTime = -1;
    init_wifi();
    init_modules();
    sensor = new SensorModel();
    sensor->setAlarmStatus(false);
}

void loop() {
    wifi->checkAndReconnect();
    int sensorStatus = digitalRead(PIN_SENSOR);
    if(watchTime != -1 && millis() > watchTime + INTERVAL_MILISECOND && sensorStatus != HIGH){
        sensor->setAlarmStatus(true);
    } else if(watchTime == -1 && sensorStatus != HIGH) {
        watchTime = millis();
    } else if(sensorStatus == HIGH) {
        sensor->setAlarmStatus(false);
        watchTime = -1;
    }
    thingsbord_do(sensor);
}


void init_wifi(){
    wifi = new WifiHandler(WIFI_SSID, WIFI_PASSWORD, WIFI_STA);
    bool wifiConnected = wifi->connect();
    if(!wifiConnected){
        exit(0);
    }
}

void init_modules(){
    pinMode(PIN_SENSOR, INPUT);
    pinMode(PIN_BUZZER, OUTPUT);
}

