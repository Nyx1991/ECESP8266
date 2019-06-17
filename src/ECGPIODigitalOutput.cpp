#include "ECGPIODigitalOutput.h"

ECGPIODigitalOutput::ECGPIODigitalOutput(uint8_t _pinNumber, char* _caption)
: ECGPIO(_pinNumber, OUTPUT, DIGITAL, _caption)
{    
    pinMode(_pinNumber, OUTPUT);
}

int ECGPIODigitalOutput::GetValue()
{
	int value = this->GetCurrentValue();
	Serial.print("Reading Pin ");
	Serial.print(GetPinNumber());
	Serial.print(": ");
	Serial.println(this->GetCurrentValue());
	return value;
}

String ECGPIODigitalOutput::GetValueText()
{	
	if (this->GetCurrentValue() == LOW)
		return "OFF";
	if (this->GetCurrentValue() == HIGH)
		return "ON";

	return "N/A";
}

void ECGPIODigitalOutput::SetValue(int _value)
{
	this->SetCurrentValue(_value);

	if (_value == 0)
	{
    	digitalWrite(this->pPinNumber, LOW);
		Serial.print("Setting Pin ");
		Serial.print(GetPinNumber());
		Serial.print(" to ");
		Serial.println(_value);
	}
	if (_value == 1)
	{
		digitalWrite(this->pPinNumber, HIGH);
		Serial.print("Setting Pin ");
		Serial.print(GetPinNumber());
		Serial.print(" to ");
		Serial.println(_value);
	}	
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