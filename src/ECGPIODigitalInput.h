#ifndef ECGPIODigitalInput_H
#define ECGPIODigitalInput_H

#include <stdint.h>
#include "ECGPIO.h"

class ECGPIODigitalInput : public ECGPIO 
{
    public:        
        int GetValue();
        String GetValueText();
        void SetValue(int _value);
        ECGPIODigitalInput(uint8_t _pinNumber, char* _caption);
};

#endif