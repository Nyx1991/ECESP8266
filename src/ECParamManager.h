#ifndef ECPARAMMANAGER_H
#define ECPARAMMANAGER_H

#include <EEPROM.h>

#define PARAM_ADDR_SSID     0x00
#define PARAM_ADDR_PASS     0x20
#define PARAM_ADDR_NAME     0x5F

#define PARAM_SIZE_SSID     0x20
#define PARAM_SIZE_PASS     0x3F
#define PARAM_SIZE_NAME     0x32

#define USED_MEMORY         0x91

class ECParamManager
{
    public:
        static char* ReadCharString(int _address, size_t _size);
        static void WriteCharString(int _address, size_t _size, char* _value);
};

#endif