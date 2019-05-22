#ifndef ECGPIO_H
#define ECGPIO_H

#define ANALOG_STR "ANALOG"
#define DIGITAL_STR "DIGITAL"
#define OUTPUT_STR "OUTPUT"
#define INPUT_STR "INPUT"

#define ANALOG 0x00
#define DIGITAL 0x01

#include <Arduino.h>
#include <stdint.h>
#include <string>
#include "ECMQTTManager.h"
#include "ECTypes.h"

extern ECMQTTManager *ecMQTTManager;

class ECGPIO
{
    protected:
        uint8_t pPinNumber;
        uint8_t pPinMode;
        uint8_t pPinType;
        char    caption[10];
        int     oldValue = -1;
        ECGPIO(uint8_t _pinNumber, uint8_t _pinMode, uint8_t _pinType, char* _caption);
    public:
        ECGPIO();
        void SetOldValue(int i);
        int GetOldValue();
        virtual void ValueChanged();
        virtual int GetValue();
        virtual String GetValueText();
        virtual void SetValue(int _value);
        virtual void Toggle();
        virtual void Toggle(ulong _time);    
        uint8_t GetPinNumber();
        uint8_t GetPinMode();
        uint8_t GetPinType();
        String GetCaption();
		String GetJSON();
		String ToString();
        ~ECGPIO();
};

#endif