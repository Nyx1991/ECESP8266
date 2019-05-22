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
         
        String parseFulltopic(const char* _fulltopic, const char *_prefix);
        String replacePlaceholder(const char* _placeholder, const char *_prefix);
        static void callback(char* topic, uint8_t* payload, unsigned int length);
        void str_to_uint16(char *str, uint16_t *res);
    public:
        void begin();
        void listen();
        bool isActive();
        void publishStat(const char* _topicExt, const char* _payload);
};

#endif