#ifndef ECGPIOManager_H
#define ECGPIOManager_H

#include <stdint.h>
#include "ECGPIO.h"
#include "ECGPIODigitalInput.h"

class ECGPIOManager
{ 
    public:
        ECGPIOManager();
        ~ECGPIOManager();
        static void     AddECGPIO(ECGPIO* _ecgpio);                        
        static ECGPIO*  GetECGPIOByPinNr(uint8_t _pinNr);
        static ECGPIO*  GetECGPIOByCaption(const char* _caption);
        static int      GetECGPIOCount();
        static ECGPIO** GetGPIOArray();
        static void     ICACHE_RAM_ATTR HandleInterrupt();
};

#endif