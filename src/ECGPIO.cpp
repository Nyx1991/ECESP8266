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
    
    return "{\"GPIO\": \""+String(pPinNumber)+"\", \"Caption\":\""+GetCaption()+"\", \"Value\": \""+String(GetValue())+"\", \"Mode\":\""+mode+"\", \"Type\":\""+type+"\" }";    
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

}

uint8_t ECGPIO::GetPinMode()
{
    return pPinMode;
}

uint8_t ECGPIO::GetPinType()
{
    return pPinType;
}

ECGPIO::~ECGPIO()
{
    delete caption;
}