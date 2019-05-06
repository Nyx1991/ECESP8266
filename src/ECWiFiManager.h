#ifndef ECWIFIMANAGER_H
#define ECWIFIMANAGER_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "ECParamManager.h"

class ECWiFiManager
{
  private:
    char   ssid[PARAM_SIZE_SSID];
    char   pass[PARAM_SIZE_PASS];
    void   LoadSsidFromEEPROM();
    void   LoadPassFromEEPROM();
  public:
    ECWiFiManager();
    void  begin();
    bool  isInApMode();
    void  SaveSsidToEEPROM(char* _ssid);
    void  SavePassToEEPROM(char* _pass);
};

#endif