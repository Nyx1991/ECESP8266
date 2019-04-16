#ifndef ECWIFIMANAGER_H
#define ECWIFIMANAGER_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <EEPROM.h>

#define OFFSET_SSID 0x00
#define OFFSET_PASS 0x50

class ECWiFiManager
{
  private:
    char  ssid[80];
    char  pass[80];
    void  LoadSsidFromEEPROM();
    void  LoadPassFromEEPROM();
  public:
    ECWiFiManager();
    void begin();
    bool isInApMode();
    void  SaveSsidToEEPROM(char* _ssid);
    void  SavePassToEEPROM(char* _pass);
};

#endif