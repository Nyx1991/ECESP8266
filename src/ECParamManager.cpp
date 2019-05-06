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

void ECParamManager::WriteCharString(int _address, size_t _size, char* _value)
{
    EEPROM.begin(USED_MEMORY);
    for(size_t i = 0; i < _size; i++)
    {
        EEPROM.write(_address + i, _value[i]);
    }
    EEPROM.commit();
    EEPROM.end();
}