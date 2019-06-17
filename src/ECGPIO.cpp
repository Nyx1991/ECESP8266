#include "ECGPIO.h"

ECGPIO::ECGPIO()
{
    
}

ECGPIO::ECGPIO(uint8_t _pinNumber, uint8_t _pinMode, uint8_t _pinType, char* _caption)
{
    this->pPinNumber = _pinNumber;
    this->pPinMode = _pinMode;
    this->pPinType = _pinType;
    if (strlen(_caption) <= sizeof(caption))
        strcpy(caption, _caption);
    else        
        strlcpy(caption, _caption, sizeof(caption));
}

String ECGPIO::GetCaption()
{
    return this->caption;
}

uint8_t ECGPIO::GetPinNumber()
{
    return this->pPinNumber;
}

String ECGPIO::GetJSON()
{
    String type;
    String mode;
    if (this->pPinMode == INPUT)
        mode = INPUT_STR;
    else
        mode = OUTPUT_STR;

    if (this->pPinType == ANALOG)
        type = ANALOG_STR;
    else    
        type = DIGITAL_STR;    
    
    return "{\"GPIO\": \""+String(pPinNumber)+"\", \"Caption\":\""+GetCaption()+"\", \"Value\": \""+String(GetValue())+"\", \"ValueText\":\""+GetValueText()+"\", \"Mode\":\""+mode+"\", \"Type\":\""+type+"\" }";    
}

String ECGPIO::ToString()
{
    return "GPIO: " + String(pPinNumber) + " Caption: " + GetCaption() + "  Value: " + this->GetValueText() + " Mode: " + String(pPinMode) + " Type: " + String(pPinType);
}

int ECGPIO::GetValue()
{
    return -1;
}

String ECGPIO::GetValueText()
{
    return "";
}

void ECGPIO::SetValue(int _value)
{
    return;
}

void ECGPIO::Toggle()
{	
	return;
}

void ECGPIO::Toggle(ulong _time)
{	
	return;
}

uint8_t ECGPIO::GetPinMode()
{
    return pPinMode;
}

uint8_t ECGPIO::GetPinType()
{
    return pPinType;
}

void ECGPIO::SetCurrentValue(int i)
{
    this->currentValue = i;
}

int ECGPIO::GetCurrentValue()
{
    return this->currentValue;
}

void ECGPIO::SetOldValue(int i)
{
    oldValue = i;
}

int ECGPIO::GetOldValue()
{
    return oldValue;
}

void ECGPIO::ValueChanged()
{
    return;
}

ECGPIO::~ECGPIO()
{
    delete caption;
}