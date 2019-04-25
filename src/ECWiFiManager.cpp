#include "ECWiFiManager.h"

ECWiFiManager::ECWiFiManager()
{
  if (!Serial)    
  {
    Serial.begin(115200);
  }
  LoadPassFromEEPROM();
  LoadSsidFromEEPROM();
}

void ECWiFiManager::begin()
{  
  Serial.println("WiFi starting");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  if (WiFi.waitForConnectResult() == WL_CONNECTED)
  {
    Serial.println("WiFi ready");
    Serial.print("IP address: ");
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

void  ECWiFiManager::LoadSsidFromEEPROM()
{
  EEPROM.begin(160);
  for (int i=0; i < sizeof(ssid); i++)
  {
    ssid[i] = EEPROM.read(OFFSET_SSID + i);
  }
  EEPROM.end();
}

void  ECWiFiManager::LoadPassFromEEPROM()
{
  EEPROM.begin(160);
  
  for (int i=0; i < sizeof(pass); i++)
  {
    pass[i] = EEPROM.read(OFFSET_PASS + i);
  }
  EEPROM.end(); 
}

void  ECWiFiManager::SaveSsidToEEPROM(char* _ssid)
{
  Serial.println("Saving ssid to eeprom... " + String(_ssid));
  EEPROM.begin(160);
  for (int i=0; i < sizeof(ssid); i++)
  {
    EEPROM.write(OFFSET_SSID + i, _ssid[i]);
  }
  EEPROM.end();
}

void  ECWiFiManager::SavePassToEEPROM(char* _pass)
{
  Serial.println("Saving ssid to eeprom... " + String(_pass));
  EEPROM.begin(160);
  for (int i=0; i < 80; i++)
  {
    EEPROM.write(OFFSET_PASS + i, _pass[i]);
  }
  EEPROM.end();
}