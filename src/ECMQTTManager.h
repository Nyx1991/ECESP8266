#ifndef ECMQTTMANAGER_H
#define ECMQTTMANAGER_H

#include <AsyncMqttClient.h>
#include <ESP8266WiFi.h>
#include "ECSettingsManager.h"
#include "ECTypes.h"
#include "ECUtil.h"

extern ECSettings settings;

class ECMQTTManager
{
    private:
        WiFiClient espClient;        
                 
        static String replacePlaceholder(const char* _placeholder, const char *_prefix);
        static String parseFulltopic(const char* _fulltopic, const char *_prefix);
        //static void callback(char* _topic, uint8_t* payload, unsigned int length);
        
        static void onMqttMessage(char* _topic, char* _payload, AsyncMqttClientMessageProperties _properties, size_t _len, size_t _index, size_t _total);
        static void onMqttConnect(bool sessionPresent);
        static void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);

        static bool IsPrefix(const char* _value);
        static bool IsTopic(const char* _value);
        static bool IsGPIOCaption(const char* _value);

        static size_t GetTopicElementCount(const char* _topicString);
        static size_t GetPayloadElementCount(const char* _payloadString);

        static void ParseMQTTTopic(const char* _topicString, ECDictEntry* _topicDict[]);
        static void ParseMQTTPayload(const char* _payloadString, ECDictEntry* _payloadDict[]);

        static void ProccessCommand(ECDictEntry* _topicDict[], size_t _topicDictSize, ECDictEntry* _payloadDict[], size_t _payLoadDictSize);

    public:
        void begin();
        //void listen();
        bool isActive();
        void publishStat(const char* _topicExt, const char* _payload);
};

extern ECMQTTManager *ecMQTTManager;

#endif