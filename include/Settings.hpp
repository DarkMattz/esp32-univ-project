#pragma once

#include <Arduino.h>

typedef struct {
    String WIFI_SSID = "DMTZ A14";
    String WIFI_PASSWORD = "punyafebry00";
    String PHONE_NUMBER = "628119422580";
    String API_KEY = "5477213";
    int MOTOR_SPEED = 250;
    int PIN_IA_MOTOR = 25;
    int PIN_IB_MOTOR = 26;
    int PIN_BUZZER = 22;
    int PIN_SENSOR = 2;
    int INTERVAL_OPEN_MILISECONDS = 10000;
    int INTERVAL_NOTIFY_MILISECONDS = 1500;
    int INTERVAL_CLOSE_MILISECONDS = 30000;
    int SERIAL_PORT = 9600;
} settings;

const settings ApplicationSettings;