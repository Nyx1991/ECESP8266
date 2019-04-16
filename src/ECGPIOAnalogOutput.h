#ifndef ECGPIOAnalogOutput_H
#define ECGPIOAnalogOutput_H

#include <stdint.h>
#include "ECGPIO.h"

class ECGPIOAnalogOutput : public ECGPIO 
{
    public:        
        int GetValue();
        String GetValueText();
        void SetValue(int _value);
        ECGPIOAnalogOutput(uint8_t _pinNumber, char* _caption);
};

#endif