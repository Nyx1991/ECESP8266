#include "ECOTAManager.h"
#include "ECWiFiManager.h"
#include "ECWebServer.h"
#include "ECGPIOFactory.h"
#include "ECGPIO.h"
#include "ECGPIOManager.h"
#include "ECHtmlBuilder.h"
#include "ECSettingsManager.h"
#include "ECMQTTManager.h"
#include "ECTypes.h"

ECOTAManager      *ecOTA;
ECWebServer       *ecWebserver;
ECWiFiManager     *ecWifiManager;
ECHtmlBuilder     *ecHtmlBuilder;
ECSettingsManager *ecSettingsManager;
ECMQTTManager     *ecMQTTManager;

ECSettings        settings;

void setup() 
{      
  Serial.begin(115200);
  ECSettingsManager::LoadSettings();

  ecOTA = new ECOTAManager();
  ecWebserver = new ECWebServer();
  ecWifiManager = new ECWiFiManager();
  ecHtmlBuilder = new ECHtmlBuilder();
  ecSettingsManager = new ECSettingsManager();
  ecMQTTManager = new ECMQTTManager();

  ecWifiManager->begin();

  if (!ecWifiManager->isInApMode())
  {
    ecOTA->begin();
  }  

  ecWebserver->begin();
  ecMQTTManager->begin();
  Serial.println("Ready");

  ECGPIOManager::AddECGPIO(ECGPIOFactory::CreateECGPIO(17, INPUT, ANALOG, "Light"));
  ECGPIOManager::AddECGPIO(ECGPIOFactory::CreateECGPIO(16, OUTPUT, DIGITAL, "LED"));
  ECGPIOManager::AddECGPIO(ECGPIOFactory::CreateECGPIO(14, INPUT, DIGITAL, "BTN"));
}

void loop() 
{  
  ecOTA->listen();
  ecWebserver->listen();
  ecMQTTManager->listen();
}