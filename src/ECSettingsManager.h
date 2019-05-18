#ifndef ECSETTINGSMANAGER_H
#define ECSETTINGSMANAGER_H

#include <EEPROM.h>
#include "ECTypes.h"

#define EEPROM_SIZE  0xFFF

class ECSettingsManager
{
    private:
        static void EraseEEPROM();
    public:
        static void SaveSettings();
        static void LoadSettings();
        static void DumpMemory();
};

#endif