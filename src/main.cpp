#include "ECOTAManager.h"
#include "ECWiFiManager.h"
#include "ECWebServer.h"
#include "ECGPIOFactory.h"
#include "ECGPIO.h"
#include "ECGPIOManager.h"
#include "ECHtmlBuilder.h"

ECOTAManager  ecOTA;
ECWebServer   ecWebserver;
ECWiFiManager ecWifiManager;
ECGPIOManager ecGPIOManager;
ECHtmlBuilder ecHtmlBuilder;

ECGPIO* gpio;

void setup() 
{    
  Serial.begin(115200);
  ecWifiManager.begin();
  if (!ecWifiManager.isInApMode())
  {
    ecOTA.begin();
  }
  ecWebserver.begin();
  Serial.println("Ready");

  ECGPIOManager::AddECGPIO(ECGPIOFactory::CreateECGPIO(16, OUTPUT, DIGITAL, "LED"));
}

void loop() 
{
  ecOTA.listen();
  ecWebserver.listen();
}