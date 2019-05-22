#include "ECGPIODigitalInput.h"

ECGPIODigitalInput::ECGPIODigitalInput(uint8_t _pinNumber, char* _caption)
: ECGPIO(_pinNumber, INPUT, DIGITAL, _caption)
{   	
	pinMode(_pinNumber, INPUT);
	SetOldValue(GetValue());
	attachInterrupt(digitalPinToInterrupt(_pinNumber), ECGPIOManager::HandleInterrupt, CHANGE);
}

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

void ECGPIODigitalInput::Toggle()
{	
	return;
}

void ECGPIODigitalInput::Toggle(ulong _time)
{	
	return;
}

void ECGPIODigitalInput::ValueChanged()
{	
	if (ecMQTTManager->isActive())
		ecMQTTManager->publishStat(GetCaption().c_str(), String(GetValue()).c_str());
}