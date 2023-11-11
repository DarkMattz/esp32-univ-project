#pragma once

#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <URLEncoder.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <certs.h>

class WhatsappAPIHandler{
    public:
        static void sendMessageToWhatsapp(String message){
            String url = "https://api.callmebot.com";
            WiFiClientSecure wifi;
            wifi.setCACert(cert_ISRG_Root_X1);
            HttpClient client = HttpClient(wifi, url);

            String contentType = "application/x-www-form-urlencoded";
            message = URLEncoder.encode(message);
            message = "phone=" + ApplicationSettings.PHONE_NUMBER + "&text=" + message + "&apikey=" + ApplicationSettings.API_KEY;
            client.post("/whatsapp.php" + message);
            int httpResponseCode = client.responseStatusCode();
            String response = client.responseBody();
            Serial.println(message);
            if (httpResponseCode == 200){
                Serial.print("Message sent successfully");
            }
            else{
                Serial.println("Error sending the message");
                Serial.print("HTTP response code: ");
                Serial.println(httpResponseCode);
                Serial.println(response);
            }
        }
};
