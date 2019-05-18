#include "ECSettingsManager.h"
#include <Arduino.h>
#include "ECTypes.h"

extern ECSettings settings;

void ECSettingsManager::SaveSettings()
{    
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.put(0, settings);
    delay(200);
    EEPROM.commit();
    EEPROM.end();
}

void ECSettingsManager::LoadSettings()
{  
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.get(0, settings);
    EEPROM.end();
}

void ECSettingsManager::DumpMemory()
{
    EEPROM.begin(sizeof(settings));
    for (int i=0; i < sizeof(settings); i++)
    {
        if (i % 10 == 0)
        {
            Serial.println();
        }
        Serial.print("  ");
        Serial.print((uint8_t)EEPROM.read(i));
    }
    EEPROM.end();
}

void ECSettingsManager::EraseEEPROM() 
{  
  EEPROM.begin(EEPROM_SIZE);
  for (int i = 0 ; i < sizeof(settings) ; i++) {
    EEPROM.write(i, 0);
  }
  delay(200);
  EEPROM.commit();
  EEPROM.end();
}