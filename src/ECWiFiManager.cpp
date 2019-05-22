#include "ECWiFiManager.h"

ECWiFiManager::ECWiFiManager()
{
  if (!Serial)    
  {
    Serial.begin(115200);
  }
}

void ECWiFiManager::begin()
{  
  Serial.println("WiFi starting");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(settings.ssid, settings.pass);
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