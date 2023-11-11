#pragma once

#include <Arduino.h>

typedef struct {
    String WIFI_SSID = "DMTZ A14";
    String WIFI_PASSWORD = "punyafebry00";
    String PHONE_NUMBER = "628119422580";
    String API_KEY = "5477213";
    
    int PIN_BUZZER = 22;
    int PIN_SENSOR = 2;
    int INTERVAL_MILISECONDS = 5000;
    int SERIAL_PORT = 9600;
} settings;

const settings ApplicationSettings;