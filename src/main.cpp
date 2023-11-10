#include <Arduino.h>
#include <Update.h>
#include <Settings.hpp>
#include "handler/ThingsBoardHandler.hpp"
#include "handler/WifiHandler.hpp"
#include <Callmebot_ESP32.h>
#include "model/SensorModel.hpp"

#pragma region INIT_FUNCTION
    void init_wifi();
    void init_modules();
    void check_sensor();
#pragma endregion

// Global Variabels Area
WifiHandler *wifi;
SensorModel *sensor;
long long timer;

// Default Arduino Function Area
void setup() {
    Serial.begin(ApplicationSettings.SERIAL_PORT);
    Serial.println("Starting Microcontroller...");
    init_wifi();
    init_modules();
}

void loop() {
    wifi->checkAndReconnect();
    check_sensor();
    thingsboard_handle(sensor);

    // Send data to whatsapp after sending data to thingsboard
    if(sensor->isAlarmStatus() && !sensor->isLimiter() && THINGSBOARD_DATA_SENT){

        // Limit data sending
        sensor->setLimiter(true);
    }
}

// User Defined Function Area
void init_wifi(){
    wifi = new WifiHandler(ApplicationSettings.WIFI_SSID, ApplicationSettings.WIFI_PASSWORD, WIFI_STA);
    bool wifiConnected = wifi->connect();
}

void init_modules(){
    timer = -1;
    sensor = new SensorModel();
    sensor->setAlarmStatus(false);
    pinMode(ApplicationSettings.PIN_SENSOR, INPUT);
    pinMode(ApplicationSettings.PIN_BUZZER, OUTPUT);
}

void check_sensor(){
    int sensorStatus = digitalRead(ApplicationSettings.PIN_SENSOR);
    if(timer != -1 && millis() > timer + ApplicationSettings.INTERVAL_MILISECONDS && sensorStatus != HIGH){ // Set alarm if the count reach maximum
        sensor->setAlarmStatus(true);
    } else if(timer == -1 && sensorStatus != HIGH) { // Start counting if the sensor not detecting
        timer = millis();
        Serial.println("Counting Started!");
    } else if(sensorStatus == HIGH) { // Reset if the sensor detecting
        sensor->setAlarmStatus(false);
        sensor->setLimiter(false);
        timer = -1;
    }
}

