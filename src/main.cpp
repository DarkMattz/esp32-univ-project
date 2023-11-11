#include <Arduino.h>
#include <Update.h>
#include "Settings.hpp"
#include "handler/ThingsBoardHandler.hpp"
#include "handler/WifiHandler.hpp"
#include "model/SensorModel.hpp"

enum class DoorState{
    opened, notify, waiting, closing, stuck, closed
};

#pragma region INIT_FUNCTION
    void init_wifi();
    void init_modules();
    void check_sensor();
    void blynk_send_data();
    void motor_on();
    void motor_off();
    void door_state_change(DoorState state);
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
DoorState state = DoorState::closed;
unsigned long timeout = 0;
unsigned long buzzerTimeout = 0;
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
    sensor = new SensorModel();
    sensor->setAlarmStatus(false);
    sensor->setSoundOn(true);
    pinMode(ApplicationSettings.PIN_SENSOR, INPUT);
    pinMode(ApplicationSettings.PIN_BUZZER, OUTPUT);
    pinMode(ApplicationSettings.PIN_IA_MOTOR, OUTPUT);
    pinMode(ApplicationSettings.PIN_IB_MOTOR, OUTPUT);
}

void check_sensor(){
    if(!sensor->isSoundOn()){
        noTone(ApplicationSettings.PIN_BUZZER);
    }
    int sensorStatus = digitalRead(ApplicationSettings.PIN_SENSOR);
    
    if(state != DoorState::closed && sensorStatus == HIGH){
        door_state_change(DoorState::closed);
    } else if(state == DoorState::closed && sensorStatus == LOW) {
        door_state_change(DoorState::opened);
    } else if(state == DoorState::opened && millis() > timeout){
        door_state_change(DoorState::notify);
    } else if(state == DoorState::notify && millis() > timeout){
        door_state_change(DoorState::closing);
    } else if(state == DoorState::closing && millis() > timeout){
        door_state_change(DoorState::stuck);
    }
}

void door_state_change(DoorState current_state){
    switch (current_state){
        case DoorState::opened:
            Serial.println("Door Opened!");
            timeout = millis() + ApplicationSettings.INTERVAL_OPEN_MILISECONDS;
            break;
        case DoorState::notify:
            Serial.println("Notified");
            tone(ApplicationSettings.PIN_BUZZER, 1000);
            timeout = millis() + ApplicationSettings.INTERVAL_NOTIFY_MILISECONDS;
            break;
        case DoorState::closing:
            Serial.println("Closing the door!");
            noTone(ApplicationSettings.PIN_BUZZER);
            timeout = millis() + ApplicationSettings.INTERVAL_CLOSE_MILISECONDS;
            motor_on();
            break;
        case DoorState::stuck:
            Serial.println("Door Stuck!");
            tone(ApplicationSettings.PIN_BUZZER, 1000);
            sensor->setAlarmStatus(true);
            motor_off();
            break;
        case DoorState::closed:
            Serial.println("Door Closed!");
            noTone(ApplicationSettings.PIN_BUZZER);
            sensor->setAlarmStatus(false);
            sensor->setLimiter(false);
            motor_off();
            break;
    }
    state = current_state;
}

void motor_on(){
    Serial.println("Motor on");
    analogWrite(ApplicationSettings.PIN_IA_MOTOR, ApplicationSettings.MOTOR_SPEED);
    analogWrite(ApplicationSettings.PIN_IB_MOTOR, 0);
}

void motor_off(){
    Serial.println("Motor off");
    analogWrite(ApplicationSettings.PIN_IA_MOTOR, 0);
    analogWrite(ApplicationSettings.PIN_IB_MOTOR, 0);
}

BLYNK_WRITE(V1){
    sensor->setSoundOn(param.asInt() == 1);
}

void blynk_send_data(){
    Blynk.virtualWrite(V0, sensor->isAlarmStatus());
    Blynk.virtualWrite(V1, sensor->isSoundOn());
}
