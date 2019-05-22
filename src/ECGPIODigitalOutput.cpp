#include "ECGPIODigitalOutput.h"

ECGPIODigitalOutput::ECGPIODigitalOutput(uint8_t _pinNumber, char* _caption)
: ECGPIO(_pinNumber, OUTPUT, DIGITAL, _caption)
{    
    pinMode(_pinNumber, OUTPUT);
}

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
	if (ecMQTTManager->isActive())
		ecMQTTManager->publishStat(GetCaption().c_str(), String(GetValue()).c_str());
}

void ECGPIODigitalOutput::Toggle()
{	
	if (GetValue() == 1)
		SetValue(0);
	else
		SetValue(1);
}

void ECGPIODigitalOutput::Toggle(ulong _time)
{	
	Toggle();
	delay(_time);
	Toggle();
}

void ECGPIODigitalOutput::ValueChanged()
{
	return;
}