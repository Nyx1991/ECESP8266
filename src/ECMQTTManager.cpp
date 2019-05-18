#include "ECMQTTManager.h"


void ECMQTTManager::begin()
{    
    uint16_t *port = new uint16_t();
    str_to_uint16(settings.mqttPort, port);

    Serial.println("MQTT starting");
    client.setServer(settings.mqttHost, *port);
    client.setCallback(ECMQTTManager::callback);
    if (client.connect(settings.mqttClientid, settings.mqttUsername, settings.mqttPass))
    {
        Serial.println("MQTT ready");
    }
    else
    {
        Serial.println("MQTT connection failed");        
    }
}

void ECMQTTManager::callback(char* topic, uint8_t* payload, unsigned int length)
{
    Serial.println(String(topic));
}

bool ECMQTTManager::isActive()
{
    return client.connected();
}

void ECMQTTManager::listen()
{
    client.loop();
}

void ECMQTTManager::str_to_uint16(char *str, uint16_t *res)
{
    char *end;
    const char *strConst = str;
    intmax_t val = strtoimax(strConst, &end, 10);
    if (val < 0 || val > UINT16_MAX || end == strConst || *end != '\0')
    {
        *res = 0;    
    }
    else
    {
        *res = (uint16_t) val;  
    }  
}

const char*  ECMQTTManager::parseFulltopic(const char* _fulltopic, const char *_prefix)
{
    String ret="";
    bool ctrlCharActive=false;
    String plchldr="";
    for (size_t i = 0; i < strlen(_fulltopic); i++)
    {
        if (ctrlCharActive)
        {
            if (_fulltopic[i] == '%')
            {
                ret += replacePlaceholder(plchldr.c_str(), _prefix);
            }
            else
            {
                plchldr += String(_fulltopic[i]);
            }            
        }
    }
    
    return ret.c_str();
}

const char* ECMQTTManager::replacePlaceholder(const char* _placeholder, const char *_prefix)
{
    String ret = "";
    String plchldrStr = String(_placeholder);
    
    if (plchldrStr == "prefix")
    {
        return String(_prefix).c_str();
    }
    else if (plchldrStr == "topic")
    {
        return String(settings.mqttTopic).c_str;
    }

    return String("").c_str();
}