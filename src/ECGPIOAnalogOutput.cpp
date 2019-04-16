#include "ECGPIOAnalogOutput.h"

int ECGPIOAnalogOutput::GetValue()
{
    return analogRead(this->pPinNumber);
}

String ECGPIOAnalogOutput::GetValueText()
{
    return String(analogRead(this->pPinNumber));
}

void ECGPIOAnalogOutput::SetValue(int _value)
{    
    analogWrite(this->pPinNumber, _value);
}

ECGPIOAnalogOutput::ECGPIOAnalogOutput(uint8_t _pinNumber, char* _caption)
: ECGPIO(_pinNumber, OUTPUT, ANALOG, _caption) 
{
    pinMode(_pinNumber, OUTPUT);
}