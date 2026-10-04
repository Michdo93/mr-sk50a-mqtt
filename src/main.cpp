#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

bool lastRawState = false;
bool stableState = false;
unsigned long lastChange = 0;

bool detectorActive()
{
    int level = digitalRead(AC_DETECT_GPIO);

#if DETECTOR_ACTIVE_LOW
    return level == LOW;
#else
    return level == HIGH;
#endif
}

void publishState(bool active)
{
    const char* payload = active ? "ON" : "OFF";
    mqtt.publish(MQTT_STATE_TOPIC, payload, true);

    if (active) {
        mqtt.publish(MQTT_EVENT_TOPIC, "ON", false);
    }
}

void connectWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}

void connectMQTT()
{
    while (!mqtt.connected()) {
        String clientId = "mr-sk50a-" + String((uint32_t)ESP.getEfuseMac(), HEX);

        if (strlen(MQTT_USER) == 0) {
            mqtt.connect(clientId.c_str());
        } else {
            mqtt.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD);
        }

        if (!mqtt.connected()) {
            delay(2000);
        }
    }

    mqtt.publish(MQTT_STATUS_TOPIC, "online", true);
    publishState(stableState);
}

void setup()
{
    Serial.begin(115200);

    pinMode(AC_DETECT_GPIO, INPUT_PULLUP);

    lastRawState = detectorActive();
    stableState = lastRawState;

    connectWiFi();

    mqtt.setServer(MQTT_HOST, MQTT_PORT);

    connectMQTT();
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED) {
        connectWiFi();
    }

    if (!mqtt.connected()) {
        connectMQTT();
    }

    mqtt.loop();

    const bool rawState = detectorActive();

    if (rawState != lastRawState) {
        lastRawState = rawState;
        lastChange = millis();
    }

    if ((millis() - lastChange) >= INPUT_DEBOUNCE_MS &&
        rawState != stableState) {

        stableState = rawState;
        publishState(stableState);

        Serial.print("MR-SK50A output: ");
        Serial.println(stableState ? "ON" : "OFF");
    }

    delay(5);
}
