#include "ECGPIOAnalogInput.h"

int ECGPIOAnalogInput::GetValue()
{
    return analogRead(this->pPinNumber);
}

String ECGPIOAnalogInput::GetValueText()
{    
    
    return String(analogRead(this->pPinNumber));
}

void ECGPIOAnalogInput::SetValue(int _value)
{
    return;
}

ECGPIOAnalogInput::ECGPIOAnalogInput(uint8_t _pinNumber, char* _caption)
: ECGPIO(_pinNumber, INPUT, ANALOG, _caption)
{    
    pinMode(_pinNumber, INPUT);    
}