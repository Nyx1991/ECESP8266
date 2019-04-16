#include "ECGPIODigitalInput.h"

int ECGPIODigitalInput::GetValue()
{
    return digitalRead(this->pPinNumber);
}

String ECGPIODigitalInput::GetValueText()
{
	if (digitalRead(this->pPinNumber) == LOW)
		return "OFF";
	if (digitalRead(this->pPinNumber) == HIGH)
		return "ON";

	return "N/A";
}

void ECGPIODigitalInput::SetValue(int _value)
{
    return;
}

ECGPIODigitalInput::ECGPIODigitalInput(uint8_t _pinNumber, char* _caption)
: ECGPIO(_pinNumber, INPUT, DIGITAL, _caption)
{    
    pinMode(_pinNumber, INPUT);
}
