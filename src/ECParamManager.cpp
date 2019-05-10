#include "ECParamManager.h"
#include <Arduino.h>

char* ECParamManager::ReadCharString(int _address, size_t _size)
{
    char ret[_size];
    EEPROM.begin(USED_MEMORY);
    for(size_t i = 0; i < _size; i++)
    {
        ret[i] = EEPROM.read(_address + i);        
    }    
    EEPROM.end();
    return ret;
}

void ECParamManager::WriteCharString(int _address, size_t _size, const char* _value)
{
    EEPROM.begin(USED_MEMORY);
    for(size_t i = 0; i < _size; i++)
    {
        EEPROM.write(_address + i, _value[i]);
    }
    EEPROM.commit();
    EEPROM.end();
}

uint16_t ECParamManager::ReadUint16(int _address)
{
    uint16_t ret = 0;
    EEPROM.begin(USED_MEMORY);
    EEPROM.get(_address, ret);
    EEPROM.end();
    return ret;
}

void ECParamManager::WriteUint16(int _address, const uint16_t* _value)
{
    EEPROM.begin(USED_MEMORY);
    EEPROM.put(_address, _value);
    EEPROM.commit();
    EEPROM.end();
}