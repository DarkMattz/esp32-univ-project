#include <Arduino.h>
#include <Update.h>
#include "Settings.hpp"
#include "handler/ThingsBoardHandler.hpp"
#include "handler/WifiHandler.hpp"
#include "model/SensorModel.hpp"

#pragma region INIT_FUNCTION
    void init_wifi();
    void init_modules();
    void check_sensor();
    void blynk_send_data();
#pragma endregion

#pragma region BLYNK // COME ON BLYNK? WHYY???
    #define BLYNK_TEMPLATE_ID "TMPL6NGShoeNr"
    #define BLYNK_TEMPLATE_NAME "Door Automation"
    #define BLYNK_AUTH_TOKEN "4JhP9Cdxelr-SK48UdMnOdVrP7l1Gv3U"
    #include <BlynkSimpleEsp32.h> //ahh damn
#pragma endregion


// Global Variabels Area
WifiHandler *wifi;
SensorModel *sensor;
long long timer;
BlynkTimer blynkTimer;

// Default Arduino Function Area
void setup() {
    Serial.begin(ApplicationSettings.SERIAL_PORT);
    Serial.println("Starting Microcontroller...");
    init_wifi();
    init_modules();
    Blynk.config(BLYNK_AUTH_TOKEN);
    blynkTimer.setInterval(telemetrySendInterval, blynk_send_data);
}

void loop() {
    wifi->checkAndReconnect();
    check_sensor();
    thingsboard_handle(sensor);
    Blynk.run();
    blynkTimer.run();
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

BLYNK_WRITE(V1){
    sensor->setSoundOn(param.asInt() == 1);
}

void blynk_send_data(){
    Blynk.virtualWrite(V0, sensor->isAlarmStatus());
    Blynk.virtualWrite(V1, sensor->isSoundOn());
}
