#ifndef ECMQTTMANAGER_H
#define ECMQTTMANAGER_H

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "ECParamManager.h"

extern ECParamManager   ecParamManager;

class ECMQTTManager
{
    private:
        WiFiClient espClient;
        PubSubClient client = PubSubClient(espClient);
        const char* topic;
        const char* fulltopic;
        const char* parseFulltopic(const char* _fulltopic);
        void callback(char* topic, byte* payload, unsigned int length);        
    public:
        void begin();
        void listen();        
};



#endif