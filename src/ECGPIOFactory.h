#ifndef ECGPIOFactory_H
#define ECGPIOFactory_H

#include <stdint.h>
#include "ECGPIO.h"
#include "ECGPIODigitalOutput.h"
#include "ECGPIOAnalogInput.h"
#include "ECGPIOAnalogOutput.h"
#include "ECGPIODigitalInput.h"

class ECGPIOFactory
{
    public:
        static ECGPIO* CreateECGPIO(uint8_t _pinNumber, uint8_t _pinMode, uint8_t _pinType, char* _caption);
};

#endif