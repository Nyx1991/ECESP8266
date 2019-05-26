#include "ECGPIOAnalogOutput.h"

ECGPIOAnalogOutput::ECGPIOAnalogOutput(uint8_t _pinNumber, char* _caption)
: ECGPIO(_pinNumber, OUTPUT, ANALOG, _caption) 
{
    pinMode(_pinNumber, OUTPUT);
}

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
    if (ecMQTTManager->isActive())
		ecMQTTManager->publishStat(GetCaption().c_str(), String(GetValue()).c_str());
}

void ECGPIOAnalogOutput::Toggle()
{	
	return;
}

void ECGPIOAnalogOutput::Toggle(ulong _time)
{	
	return;
}

void ECGPIOAnalogOutput::ValueChanged()
{
	return;
}