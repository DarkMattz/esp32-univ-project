#include <Arduino.h>
#include "Wifi.hpp"

#define WIFI_SSID "Ade"
#define WIFI_PASSWORD "Ade1234567890"
#define SERIAL_PORT 9600

void setup() {
    Serial.begin(SERIAL_PORT);
    Wifi wifi(WIFI_SSID, WIFI_PASSWORD, WIFI_STA);
    wifi.connect();
}

void loop() {
  
}

