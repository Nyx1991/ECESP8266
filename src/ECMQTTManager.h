#ifndef ECMQTTMANAGER_H
#define ECMQTTMANAGER_H

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "ECSettingsManager.h"
#include "ECTypes.h"

extern ECSettings settings;

class ECMQTTManager
{
    private:
        WiFiClient espClient;
        PubSubClient client = PubSubClient(espClient);

        void str_to_uint16(char *str, uint16_t *res);
        const char* parseFulltopic(const char* _fulltopic, const char *_prefix);
        const char* replacePlaceholder(const char* _placeholder, const char *_prefix);
        static void callback(char* topic, uint8_t* payload, unsigned int length);
    public:
        void begin();
        void listen();
        bool isActive();
};

#endif