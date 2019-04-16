#ifndef ECOTAMANAGER_H
#define ECOTAMANAGER_H

#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

class ECOTAManager
{
  private:
    void initOTA();
  
  public:
    ECOTAManager();
    void begin();
    void listen();
};

 #endif