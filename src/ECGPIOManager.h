#ifndef ECGPIOManager_H
#define ECGPIOManager_H

#include <stdint.h>
#include "ECGPIO.h"

class ECGPIOManager
{
    private:
        
    public:
        ECGPIOManager();
        ~ECGPIOManager();
        static void     AddECGPIO(ECGPIO* _ecgpio);
        static ECGPIO*  GetECGPIOByPinNr(uint8_t _pinNr);
        static int      GetECGPIOCount();
        static ECGPIO*  GetGPIOArray();
};

#endif