#pragma once

#include <WString.h>
#include <WiFi.h>

class Wifi {
    public:
    
        Wifi(String ssid, String password, wifi_mode_t wifi_mode){
            WiFi.mode(wifi_mode);
            this->ssid = ssid;
            this->password = password;
        }
    
        void connect(int max_tries = 5){
            for(int i = 1; i <= max_tries; i++){
                Serial.println("Connecting To Wifi " + this->ssid + " (try number " + i + ")");
                WiFi.begin(this->ssid, this->password);
                switch (WiFi.status()){
                    case wl_status_t::WL_CONNECTED:
                        Serial.println("WiFi connected");
                        break;
                    default:
                        Serial.println("WiFi connection failed, retrying");
                }
            }
        }

    private:
        String ssid;
        String password;
};
