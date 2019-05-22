#ifndef ECGPIODigitalInput_H
#define ECGPIODigitalInput_H

#include <stdint.h>
#include "ECGPIO.h"
#include "ECGPIOMANAGER.h"

class ECGPIODigitalInput : public ECGPIO 
{
    public:        
        int GetValue();
        String GetValueText();
        void SetValue(int _value);
        void Toggle();
        void Toggle(ulong _time);
        void ValueChanged();
        ECGPIODigitalInput(uint8_t _pinNumber, char* _caption);
};

#endif