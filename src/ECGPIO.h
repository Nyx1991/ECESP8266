#ifndef ECGPIO_H
#define ECGPIO_H

#define ANALOG 0x00
#define DIGITAL 0x01

#define ANALOG_STR "ANALOG"
#define DIGITAL_STR "DIGITAL"
#define OUTPUT_STR "OUTPUT"
#define INPUT_STR "INPUT"

#include <Arduino.h>
#include <stdint.h>
#include <string>

class ECGPIO
{
    protected:
        uint8_t pPinNumber;
        uint8_t pPinMode;
        uint8_t pPinType;
        char    caption[10];
        ECGPIO(uint8_t _pinNumber, uint8_t _pinMode, uint8_t _pinType, char* _caption);
    public:
        virtual int GetValue();
        virtual String GetValueText();
        virtual void SetValue(int _value);
        ECGPIO();
        uint8_t GetPinNumber();
        uint8_t GetPinMode();
        uint8_t GetPinType();
        String GetCaption();
		String GetJSON();
		String ToString();        
        ~ECGPIO();
};

#endif