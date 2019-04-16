#ifndef ECGPIOAnalogInput_H
#define ECGPIOAnalogInput_H

#include <stdint.h>
#include "ECGPIO.h"

class ECGPIOAnalogInput : public ECGPIO 
{
    public:
        ECGPIOAnalogInput(uint8_t _pinNumber, char* _caption);
        int GetValue();
        String GetValueText();
        void SetValue(int _value);
};

#endif