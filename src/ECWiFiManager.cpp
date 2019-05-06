#include "ECWiFiManager.h"

ECWiFiManager::ECWiFiManager()
{
  if (!Serial)    
  {
    Serial.begin(115200);
  }  
  LoadSsidFromEEPROM();
  LoadPassFromEEPROM();
}

void ECWiFiManager::begin()
{  
  Serial.println("WiFi starting");
  
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, pass);

  if (WiFi.waitForConnectResult() == WL_CONNECTED)
  {
    Serial.println("WiFi ready");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
  { 
    Serial.println("Connection failed... setting up access point");    
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ecESP8266");
    Serial.println("AP ready: " + WiFi.softAPIP().toString());
  }
}

bool ECWiFiManager::isInApMode()
{
  return WiFi.getMode() == WIFI_AP;
}

void ECWiFiManager::LoadSsidFromEEPROM()
{   
  char* ret = ECParamManager::ReadCharString(PARAM_ADDR_SSID, PARAM_SIZE_SSID);
  for(size_t i = 0; i < PARAM_SIZE_SSID; i++)
  {
    ssid[i] = ret[i];
  }
}

void ECWiFiManager::LoadPassFromEEPROM()
{
  char* ret = ECParamManager::ReadCharString(PARAM_ADDR_PASS, PARAM_SIZE_PASS);
  for(size_t i = 0; i < PARAM_SIZE_PASS; i++)
  {
    pass[i] = ret[i];
  }
}

void  ECWiFiManager::SaveSsidToEEPROM(char* _ssid)
{  
  ECParamManager::WriteCharString(PARAM_ADDR_SSID, PARAM_SIZE_SSID, _ssid);
}

void  ECWiFiManager::SavePassToEEPROM(char* _pass)
{  
  ECParamManager::WriteCharString(PARAM_ADDR_PASS, PARAM_SIZE_PASS, _pass);
}