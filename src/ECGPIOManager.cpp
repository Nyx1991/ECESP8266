#include "ECGPIOManager.h"

int         gpioCount;
ECGPIO**    gpios;

ECGPIOManager::ECGPIOManager()
{           
    gpioCount = 0;
    gpios = new ECGPIO*[gpioCount];
}

ECGPIO** ECGPIOManager::GetGPIOArray()
{
    return gpios;
}

void ECGPIOManager::AddECGPIO(ECGPIO* _ecgpio)
{
    if (_ecgpio == NULL)
    {
        Serial.println("ERROR: NULL-Pointer.");
        return;
    }
    if (ECGPIOManager::GetECGPIOByPinNr(_ecgpio->GetPinNumber()) != nullptr)
    {
        Serial.println("Pin "+String(_ecgpio->GetPinNumber())+" already declared.");        
        return;
    }
    ECGPIO** tmp = { &_ecgpio };
	ECGPIO** newArray = new ECGPIO*[gpioCount+1];

	memcpy(newArray, gpios, gpioCount * sizeof(&_ecgpio));
	memcpy(newArray + gpioCount, tmp, sizeof(&_ecgpio));
	delete[] gpios;
	gpios = newArray;
    gpioCount++;    
}

int ECGPIOManager::GetECGPIOCount()
{
    return gpioCount;
}

ECGPIO* ECGPIOManager::GetECGPIOByPinNr(uint8_t _pinNr)
{    
    ECGPIO*  gpio;    
    for (int i=0; i < ECGPIOManager::GetECGPIOCount(); i++)
    {      
        gpio = gpios[i];
        if (gpio->GetPinNumber() == _pinNr)
        {
            return gpio;
        }
    }
    return nullptr;
}

ECGPIO* ECGPIOManager::GetECGPIOByCaption(const char* _caption)
{    
    ECGPIO*  gpio;
    for (int i=0; i < ECGPIOManager::GetECGPIOCount(); i++)
    {      
        gpio = gpios[i];
        if (gpio->GetCaption() == String(_caption))
        {
            return gpio;
        }
    }
    return nullptr;
}

void ICACHE_RAM_ATTR ECGPIOManager::HandleInterrupt()
{        
    ECGPIO* gpio;
    delay(10);
    for (int i = 0; i < ECGPIOManager::GetECGPIOCount(); i++)
    {
        gpio = gpios[i];
        if (gpio->GetPinMode() == INPUT && gpio->GetPinType() == DIGITAL)
        {            
            if (gpio->GetValue() != gpio->GetOldValue())
            {                                
                gpio->SetOldValue(gpio->GetValue());
                gpio->ValueChanged();
            }
        }
    }    
}

bool ECGPIOManager::IsGPIOCaption(const char* _value)
{    
    String val(_value);

    for (size_t i = 0; i < gpioCount; i++)
    {
        if (val.equals(gpios[i]->GetCaption()))
        {
            return true;
        }
    }
    
    return false;
}

ECGPIOManager::~ECGPIOManager()
{
    delete[] gpios;
}