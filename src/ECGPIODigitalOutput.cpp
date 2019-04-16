#include "ECGPIODigitalOutput.h"

int ECGPIODigitalOutput::GetValue()
{
	return digitalRead(this->pPinNumber);
}

String ECGPIODigitalOutput::GetValueText()
{
	if (digitalRead(this->pPinNumber) == LOW)
		return "OFF";
	if (digitalRead(this->pPinNumber) == HIGH)
		return "ON";

	return "N/A";
}

void ECGPIODigitalOutput::SetValue(int _value)
{
	if (_value == 0)
    	digitalWrite(this->pPinNumber, LOW);
	if (_value == 1)
		digitalWrite(this->pPinNumber, HIGH);
}

ECGPIODigitalOutput::ECGPIODigitalOutput(uint8_t _pinNumber, char* _caption)
: ECGPIO(_pinNumber, OUTPUT, DIGITAL, _caption)
{    
    pinMode(_pinNumber, OUTPUT);
}