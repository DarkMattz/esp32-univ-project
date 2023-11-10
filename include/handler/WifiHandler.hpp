#pragma once

#include <WString.h>
#include <WiFi.h>

class WifiHandler {
    public:
    
        WifiHandler(String ssid, String password, wifi_mode_t wifi_mode){
            WiFi.mode(wifi_mode);
            this->ssid = ssid;
            this->password = password;
        }
    
        bool connect(int waitSecond = 10){
            Serial.print("Connecting to Wifi " + this->ssid);
            WiFi.begin(this->ssid, this->password);

            waitSecond *= 1000;

            while(WiFi.status() != WL_CONNECTED && waitSecond > 0){
                Serial.print(".");
                delay(100);
                waitSecond -= 100;
            }

            Serial.print("\n");

            if(waitSecond <= 0){
                Serial.println("Fail to connect to " + this->ssid);
                return false;
            }

            Serial.println("Connected to " + this->ssid);
            return true;
        }

        void checkAndReconnect() {
            if(WiFi.status() != WL_CONNECTED) {
                connect();
            }
        }

    private:
        String ssid;
        String password;
};
