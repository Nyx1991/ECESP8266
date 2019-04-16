#ifndef ECGPIODigitalOutput_H
#define ECGPIODigitalOutput_H

#include <stdint.h>
#include "ECGPIO.h"

class ECGPIODigitalOutput : public ECGPIO 
{
    public:
        int GetValue();
        String GetValueText();
        void SetValue(int _value);
        ECGPIODigitalOutput(uint8_t _pinNumber, char* _caption);
};

#endif