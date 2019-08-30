#ifndef ECGPIOServo_H
#define ECGPIOServo_H

#include <stdint.h>
#include "ECGPIO.h"

class ECGPIOServo : public ECGPIO 
{
    private:
        const int minValue = 0;
        const int maxValue = 180;        
    public:
        int GetValue();
        String GetValueText();
        void SetValue(int _value);
        void Toggle();
        void Toggle(ulong _time);
        void ValueChanged();
        ECGPIOServo(uint8_t _pinNumber, char* _caption);
};

#endif