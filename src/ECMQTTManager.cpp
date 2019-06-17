#include "ECMQTTManager.h"
#include "ECGPIOManager.h"
#include "ECGPIO.h"

void ECMQTTManager::begin()
{    
    uint16_t *port = new uint16_t();
    ECUtil::str_to_uint16(settings.mqttPort, port);

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

void ECMQTTManager::callback(char* _topic, uint8_t* _payload, unsigned int length)
{        
    char *payload = new char[length+1]();
    for (unsigned int i = 0;  i < length+1; i++)
    {
        payload[i] = 0x00;
    }
    for (unsigned int i = 0;  i < length; i++)
    {
        payload[i] = (char)_payload[i];
    }    

    size_t payloadSize = ECMQTTManager::GetPayloadElementCount(payload);
    size_t topicSize = ECMQTTManager::GetTopicElementCount(_topic);        
    
    ECDictEntry* payloadDict[payloadSize];
    ECDictEntry* topicDict[topicSize];
    ECDictEntry* tmpEntry;

    ECMQTTManager::ParseMQTTPayload(payload, payloadDict);
    ECMQTTManager::ParseMQTTTopic(_topic, topicDict);    
    
    if (ECUtil::FindDictEntryByKey(topicDict, topicSize, "cmd") != nullptr)
    {
        ECMQTTManager::ProccessCommand(topicDict, topicSize, payloadDict, payloadSize);
    }

    delay(10);    
    delete tmpEntry;    
    for (size_t i = 0; i < topicSize; i++)
    {
        delete topicDict[i];
    }
    for (size_t i = 0; i < payloadSize; i++)
    {
        delete payloadDict[i];
    }
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

void ECMQTTManager::publishStat(const char* _topicExt, const char* _payload)
{
    String topic = String(parseFulltopic(settings.mqttFulltopic, "stat"));
    topic += "/" + String(_topicExt);
    client.publish(topic.c_str(), _payload);    
}

bool ECMQTTManager::IsPrefix(const char* _value)
{
    return (String(_value).equals("cmd")) || (String(_value).equals("stat"));
}

bool ECMQTTManager::IsTopic(const char* _value)
{
    return (String(_value).equals(settings.mqttTopic));
}

bool ECMQTTManager::IsGPIOCaption(const char* _value)
{    
    String val(_value);
    ECGPIO** gpios = ECGPIOManager::GetGPIOArray();

    for (size_t i = 0; i < ECGPIOManager::GetECGPIOCount(); i++)
    {
        if (val.equals(gpios[i]->GetCaption()))
        {
            return true;
        }
    }
    
    return false;
}

size_t ECMQTTManager::GetTopicElementCount(const char* _topicString)
{
    size_t ret = 0;    
    for (size_t i = 0; i < String(_topicString).length(); i++)
    {
        if (_topicString[i] == '/' || _topicString[i] == '\\')
        {
            ret++;
        }
    }
    return ret+1;
}

size_t ECMQTTManager::GetPayloadElementCount(const char* _payloadString)
{
    size_t ret = 0;
    if (String(_payloadString).length() > 0)
        ret = 1;

    for (size_t i = 0; i < String(_payloadString).length(); i++)
    {
        if (_payloadString[i] == ' ')
        {
            ret++;
        }
    }
    
    return ret;
}

void ECMQTTManager::ParseMQTTTopic(const char* _topicString, ECDictEntry* _topicDict[])
{
    bool lastWasCommand = false;
    int currElementId = 0;
    int topicLength = String(_topicString).length();
    String currElement = "";
    ECDictEntry* tmpEntry;

    for (size_t i = 0; i < topicLength; i++)
    {
        if (_topicString[i] == '/' || _topicString[i] == '\\' || i == topicLength-1)
        {
            if (i == topicLength-1)
            {
                currElement += _topicString[i];
            }
            tmpEntry = new ECDictEntry();
            strncpy(tmpEntry->value, currElement.c_str(), 40);

            if (lastWasCommand)
            {                                
                strncpy(tmpEntry->key, "cmd", 40);
                lastWasCommand = false;
            }
            else if (IsPrefix(currElement.c_str()))
            {
                strncpy(tmpEntry->key, "prefix", 40);
                lastWasCommand = currElement.equals("cmd");
            }
            else if (IsTopic(currElement.c_str()))
            {
                strncpy(tmpEntry->key, "topic", 40);
            }
            else if (IsGPIOCaption(currElement.c_str()))
            {
                strncpy(tmpEntry->key, "caption", 40);
            }
            else
            {
                strncpy(tmpEntry->key, String(currElementId).c_str(), 40);
            }
            
            _topicDict[currElementId] = tmpEntry;            
            currElement = "";
            currElementId++;
        }
        else
        {
            currElement += _topicString[i];
        }
    }
}

void ECMQTTManager::ParseMQTTPayload(const char* _payloadString, ECDictEntry* _payloadDict[])
{
    size_t payLoadStringLength = String(_payloadString).length();
    int currElementId = 0;
    String currElement = "";
    ECDictEntry* tmpEntry;

    for (size_t i = 0; i < payLoadStringLength; i++)
    {
        if (_payloadString[i] == ' ' || i == payLoadStringLength-1)
        {
            if (i == payLoadStringLength-1)
            {
                currElement += _payloadString[i];
            }
            tmpEntry = new ECDictEntry();            
            strncpy(tmpEntry->key, String(currElementId).c_str(), 40);
            strncpy(tmpEntry->value, currElement.c_str(), 40);
            _payloadDict[currElementId] = tmpEntry;
            currElementId++;
            currElement = "";
        }
        else
        {
            currElement += _payloadString[i];
        }
    }    
}

void ECMQTTManager::ProccessCommand(ECDictEntry* _topicDict[], size_t _topicDictSize, ECDictEntry* _payloadDict[], size_t _payLoadDictSize)
{
    ECDictEntry* cmd = ECUtil::FindDictEntryByKey(_topicDict, _topicDictSize, "cmd");
    ECDictEntry* caption = ECUtil::FindDictEntryByKey(_topicDict, _topicDictSize, "caption");

    if (cmd != nullptr && caption != nullptr)
    {
        ECGPIO* gpio = ECGPIOManager::GetECGPIOByCaption(caption->value);
        if (gpio == nullptr)
        {
            return;
        }

        String value = String(cmd->value);
        if (value.equals("get"))
        {
            ecMQTTManager->publishStat(gpio->GetCaption().c_str(), String(gpio->GetValue()).c_str());
        }
        else if (value.equals("set"))
        {            
            ECDictEntry* payload = ECUtil::FindDictEntryByKey(_payloadDict, _payLoadDictSize, "0");
            if (payload != nullptr)
            {
                gpio->SetValue(atoi(payload->value));
            }
        }
        else if (value.equals("toggle"))
        {
            gpio->Toggle();
            ECDictEntry* payloadDelay = ECUtil::FindDictEntryByKey(_payloadDict, _payLoadDictSize, "0");
            if (payloadDelay != nullptr)
            {                    
                delay(atoi(payloadDelay->value));
                gpio->Toggle();
            }            
        }        
    }
}