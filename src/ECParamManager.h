#ifndef ECPARAMMANAGER_H
#define ECPARAMMANAGER_H

#include <EEPROM.h>

//ADDRESSES
#define PARAM_ADDR_SSID             0x00
#define PARAM_ADDR_PASS             0x20
#define PARAM_ADDR_NAME             0x5F

#define PARAM_ADDR_MQTT_CLIENTID    0x91
#define PARAM_ADDR_MQTT_USERNAME    0xB1
#define PARAM_ADDR_MQTT_PASS        0xD1
#define PARAM_ADDR_MQTT_TOPIC       0xF1
#define PARAM_ADDR_MQTT_FULLTOPIC   0x111
#define PARAM_ADDR_MQTT_HOST        0x175 
#define PARAM_ADDR_MQTT_PORT        0x184

//NEXT START ADDR 0x186

//SIZES
#define PARAM_SIZE_SSID             0x20
#define PARAM_SIZE_PASS             0x3F
#define PARAM_SIZE_NAME             0x32

#define PARAM_SIZE_MQTT_CLIENTID    0x20
#define PARAM_SIZE_MQTT_USERNAME    0x20
#define PARAM_SIZE_MQTT_PASS        0x20
#define PARAM_SIZE_MQTT_TOPIC       0x20
#define PARAM_SIZE_MQTT_FULLTOPIC   0x64
#define PARAM_ADDR_MQTT_HOST        0xF0
#define PARAM_ADDR_MQTT_PORT        0x02
//REMEMBER %topic% and %prefix%

#define USED_MEMORY                 0x267

class ECParamManager
{
    public:
        static char* ReadCharString(int _address, size_t _size);
        static void WriteCharString(int _address, size_t _size, const char* _value);
        static uint16_t ReadUint16(int _address);
        static void WriteUint16(int _address, const uint16_t* _value);
};

#endif