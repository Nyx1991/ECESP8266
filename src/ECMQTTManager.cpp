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
        String topic = parseFulltopic(settings.mqttFulltopic, "cmd") + "/#";
        client.subscribe(topic.c_str());
        Serial.println("MQTT ready");
    }
    else
    {
        Serial.println("MQTT connection failed");        
    }
}

void ECMQTTManager::callback(char* topic, uint8_t* _payload, unsigned int length)
{
    Serial.println(String(topic));
    char *payload = new char[length+1]();
    for (unsigned int i = 0;  i < length+1; i++)
    {
        payload[i] = 0x00;
    }
    for (unsigned int i = 0;  i < length; i++)
    {
        payload[i] = (char)_payload[i];
    }
    Serial.println(payload);
    delete payload;
}

bool ECMQTTManager::isActive()
{
    return client.connected();
}

void ECMQTTManager::listen()
{
    client.loop();
}

String ECMQTTManager::parseFulltopic(const char* _fulltopic, const char *_prefix)
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
                ret += String(replacePlaceholder(plchldr.c_str(), _prefix));                
                ctrlCharActive = false;
            }
            else
            {                
                plchldr += String(_fulltopic[i]);
            }
        }
        else
        {
            if (_fulltopic[i] == '%')
            {                
                plchldr = "";
                ctrlCharActive = true;                
            }
            else
            {                
                ret += String(_fulltopic[i]);
            }
        }        
    }
    
    return ret;
}

String ECMQTTManager::replacePlaceholder(const char* _placeholder, const char *_prefix)
{

    String plchldrStr = String(_placeholder);
    if (plchldrStr == "prefix")
    {        
        return String(_prefix);
    }
    else if (plchldrStr == "topic")
    {        
        return String(settings.mqttTopic);
    }

    return String("");
}

void ECMQTTManager::str_to_uint16(char *str, uint16_t *res)
{
    char *end;
    long val = strtol(str, &end, 10);
    if (end == str || *end != '\0' || val < 0 || val >= 0x10000) {
        res = new uint16_t(0);
    }
    else
    {
        *res = (uint16_t)val;
    }
}

void ECMQTTManager::publishStat(const char* _topicExt, const char* _payload)
{
    String topic = String(parseFulltopic(settings.mqttFulltopic, "stat"));
    topic += "/" + String(_topicExt);
    client.publish(topic.c_str(), _payload);    
}