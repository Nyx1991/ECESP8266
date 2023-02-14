#include "ECGPIOServo.h"

ECGPIOServo::ECGPIOServo(uint8_t _pinNumber, char* _caption)
: ECGPIO(_pinNumber, OUTPUT, ANALOG, _caption) 
{
    pinMode(_pinNumber, OUTPUT);
}

int ECGPIOServo::GetValue()
{    
    return this->GetCurrentValue();
}

String ECGPIOServo::GetValueText()
{    
    return String(this->GetValue());
}

void ECGPIOServo::SetValue(int _value)
{    
    this->SetCurrentValue(_value);

    int puls = map(_value, minValue, maxValue, 544, 2400);

    for (int i=0; i < 20; i++)
    {
        digitalWrite(this->pPinNumber, HIGH);
        delayMicroseconds(puls);    
        digitalWrite(this->pPinNumber, LOW);
        delayMicroseconds(19000);
    }

    Serial.print("Set Servo to: ");
    Serial.println(_value);

    if (ecMQTTManager->isActive())
		ecMQTTManager->publishStat(GetCaption().c_str(), String(GetValue()).c_str());
}

void ECGPIOServo::Toggle()
{	
	return;
}

void ECGPIOServo::Toggle(ulong _time)
{	
	return;
}

void ECGPIOServo::ValueChanged()
{
	return;
}