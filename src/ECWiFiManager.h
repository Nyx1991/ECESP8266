#ifndef ECWIFIMANAGER_H
#define ECWIFIMANAGER_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "ECSettingsManager.h"

extern ECSettings settings;

class ECWiFiManager
{
  public:
    ECWiFiManager();
    void  begin();
    bool  isInApMode();
};

#endif