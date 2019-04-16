#include "ECGPIOManager.h"

int      gpioCount;
ECGPIO*  gpios;

ECGPIOManager::ECGPIOManager()
{           
    gpioCount = 0;
    gpios = new ECGPIO[gpioCount];
}

ECGPIO* ECGPIOManager ::GetGPIOArray()
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
    ECGPIO* tmp = { _ecgpio };
	ECGPIO* newArray = new ECGPIO[gpioCount+1];

	memcpy(newArray, gpios, gpioCount * sizeof(ECGPIO));
	memcpy(newArray + gpioCount, tmp, sizeof(ECGPIO));
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
        gpio = &gpios[i];
        if (gpio->GetPinNumber() == _pinNr)
        {
            return gpio;
        }
    }
    return nullptr;
}

ECGPIOManager::~ECGPIOManager()
{
    delete[] gpios;
}