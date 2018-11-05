#include <ESP8266WiFi.h>
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include "settings.h"
#include <ArduinoJson.h>


char JSONmessageBuffer[200];

#include "blink.h"
#include "update.h"
#include "json.h"
#include "mqtt.h"


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Load WLAN2...");
      WiFi.begin(ssid2, password2);
        while (WiFi.waitForConnectResult() != WL_CONNECTED) {
          Serial.println("Connection2 failed...reboot");
    delay(5000);
    ESP.restart();
  }
  }

    //Print MAC-Adress of ESP
   Serial.print("MAC: ");             
   Serial.println(WiFi.macAddress());

}

// the loop function runs over and over again forever
void loop() {
  mqttconnect();
  checkForUpdates();  //Unterprogramm update.h
  bmecode();
  json();
  mqttsend();

  
  Serial.println("Going to sleep");
  delay(2000); //Delay for running all processes before going to sleep
  ESP.deepSleep(60e6);
}
