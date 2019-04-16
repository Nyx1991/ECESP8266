#include "ECGPIOFactory.h"

ECGPIO* ECGPIOFactory::CreateECGPIO(uint8_t _pinNumber, uint8_t _pinMode, uint8_t _pinType, char* _caption)
{
    ECGPIO* ret = NULL;      

    if (_pinMode == OUTPUT) 
    {
        if (_pinType == ANALOG)
        {
            ret = new ECGPIOAnalogOutput(_pinNumber, _caption);
        }
        if (_pinType == DIGITAL)
        {
            ret = new ECGPIODigitalOutput(_pinNumber, _caption);
        }
    }

    if (_pinMode == INPUT)
    {
        if (_pinType == ANALOG)
        {
            ret = new ECGPIOAnalogInput(_pinNumber, _caption);
        }
        if (_pinType == DIGITAL)
        {
            ret = new ECGPIODigitalInput(_pinNumber, _caption);
        }
    }

    return ret;
}