#include "ECGPIOAnalogInput.h"

ECGPIOAnalogInput::ECGPIOAnalogInput(uint8_t _pinNumber, char* _caption)
: ECGPIO(_pinNumber, INPUT, ANALOG, _caption)
{    
    pinMode(_pinNumber, INPUT);
    SetOldValue(GetValue());    
}

int ECGPIOAnalogInput::GetValue()
{
    this->SetCurrentValue(analogRead(this->pPinNumber));
    return this->GetCurrentValue();
}

String ECGPIOAnalogInput::GetValueText()
{        
    return String(this->GetCurrentValue());
}

void ECGPIOAnalogInput::SetValue(int _value)
{
    return;
}

void ECGPIOAnalogInput::Toggle()
{
    return;
}

void ECGPIOAnalogInput::Toggle(ulong _time)
{
    return;
}

void ECGPIOAnalogInput::ValueChanged()
{
	Serial.println("Interrupt on Pin "+String(this->GetPinNumber()+", aka "+String(this->GetCaption())));
	if (ecMQTTManager->isActive())
		ecMQTTManager->publishStat(GetCaption().c_str(), String(GetValue()).c_str());
}