#include "ECWebServer.h"
#include "ECGPIOManager.h"
#include "ECWiFiManager.h"
#include "ECGPIO.h"

extern ECGPIOManager  ecGPIOManager;
extern ECWiFiManager  ecWifiManager;
extern ECSettings     settings;

ECWebServer::ECWebServer()
{
  if (!Serial)
  {
    Serial.begin(115200);
  }

  server = new ESP8266WebServer(80);
  server->on("/", std::bind(&ECWebServer::onIndex, this));
  server->on("/cmd", std::bind(&ECWebServer::onCmd, this));
  server->on("/mqtt", std::bind(&ECWebServer::onMqtt, this));
  server->on("/sysinfo", std::bind(&ECWebServer::onSysInfo, this));
}

void ECWebServer::listen()
{
  server->handleClient();
}

void ECWebServer::begin()
{  
  Serial.println("Webserver starting");
  server->begin();
  Serial.println("Webserver ready");    
}

ECWebServer::~ECWebServer()
{
  delete server;
  server = NULL;
}

void ECWebServer::sendToClient(String _message)
{
  server->send(200, "text/html", _message);
}

void ECWebServer::onIndex()
{
  if (ecWifiManager.isInApMode() || server->arg("page") == "wifi")
  {
    sendToClient(ecHtmlBuilder.GetWiFiConfigPage());
  }
  else
  {
    sendToClient(ecHtmlBuilder.GetIndexHtml());
  }  
}

void ECWebServer::onMqtt()
{
  sendToClient(ecHtmlBuilder.GetMqttConfHtml());
}

void ECWebServer::onSysInfo()
{
  sendToClient(ecHtmlBuilder.GetSystemInfoHtml());
}

void ECWebServer::onCmd()
{
  String output;
  String cmd = server->arg("cmd");
  ECGPIO* gpio = nullptr;
  ECGPIO* gpios = nullptr;    
  int gpioCount = ecGPIOManager.GetECGPIOCount();
  
  output = "Commands";

  if(cmd == "status" && server->arg("gpio") != "")
  {
    gpio = ecGPIOManager.GetECGPIOByPinNr(server->arg("gpio").toInt());
    if (gpio != nullptr)
      output = gpio->GetJSON();
    else
      output = "GPIO "+String(server->arg("gpio"))+" not found";
      
  } 
  else if(cmd == "status" && server->arg("gpio") == "")
  {
    output = "[";
    for (int i=0; i < ecGPIOManager.GetECGPIOCount(); i++)
    {
      gpio = ecGPIOManager.GetGPIOArray()[i];
      output += gpio->GetJSON();
      if (i+1 != ecGPIOManager.GetECGPIOCount())
      {
        output += ",";
      }
    }    
    output += "]";
  }
  else if(cmd == "statushtml")
  {
    output = ecHtmlBuilder.GetECGPIOHtml();
  }
  else if(cmd == "set")
  {
      gpio = ecGPIOManager.GetECGPIOByPinNr(server->arg("gpio").toInt());
      if (gpio != nullptr)
      {
        gpio->SetValue(server->arg("value").toInt());
        output = String(gpio->GetValue());
      }
      else
        output = "GPIO "+String(server->arg("gpio"))+" not found";   
  }
  else if(cmd == "get")
  {
      gpio = ecGPIOManager.GetECGPIOByPinNr(server->arg("gpio").toInt());
      if (gpio != nullptr)
        output = String(gpio->GetValue());
      else
        output = "GPIO "+String(server->arg("gpio"))+" not found";
  }
  else if(cmd == "setwificonf")
  {
    memcpy(settings.ssid, server->arg("ssid").c_str(), sizeof(settings.ssid));
    memcpy(settings.pass, server->arg("password").c_str(), sizeof(settings.pass));
    memcpy(settings.name, server->arg("name").c_str(), sizeof(settings.name));
    
    ECSettingsManager::SaveSettings();
    
    ESP.reset();    
  }
  else if(cmd == "setmqttconf")
  {
    IPAddress host;    
    host.fromString(server->arg("host"));
    const uint16_t* port = new uint16_t((uint16_t)atoi(server->arg("port").c_str()));                    
        
    memcpy(settings.mqttClientid, server->arg("clientid").c_str(), sizeof(settings.mqttClientid));
    memcpy(settings.mqttUsername, server->arg("username").c_str(), sizeof(settings.mqttUsername));
    memcpy(settings.mqttPass, server->arg("pass").c_str(), sizeof(settings.mqttPass));
    memcpy(settings.mqttTopic, server->arg("topic").c_str(), sizeof(settings.mqttTopic));
    memcpy(settings.mqttFulltopic, server->arg("fulltopic").c_str(), sizeof(settings.mqttFulltopic));
    memcpy(settings.mqttHost, server->arg("host").c_str(), sizeof(settings.mqttHost));
    memcpy(settings.mqttPort, server->arg("port").c_str(), sizeof(settings.mqttPort));

    ECSettingsManager::SaveSettings();  

    ESP.reset();
  }
  else if(cmd == "setdevicename")
  {
    memcpy(settings.name, server->arg("name").c_str(), sizeof(settings.name));
    ECSettingsManager::SaveSettings();
    ESP.reset();
  }
  else if(cmd == "getdevicename")
  {    
    output = String(settings.name);
  }
  else if(cmd == "toggle")
  {
    gpio = ecGPIOManager.GetECGPIOByPinNr(server->arg("gpio").toInt());    
    if (gpio != nullptr)
    {
      if (gpio->GetPinMode() == OUTPUT && gpio->GetPinType() == DIGITAL)
      {
        if (gpio->GetValue() == 1)
          gpio->SetValue(0);
        else
          gpio->SetValue(1);
      }
      output = String(gpio->GetValue());
    }
    else
      output = "GPIO "+String(server->arg("gpio"))+" not found";
  }

  gpio = nullptr;
  gpios = nullptr;  
  gpioCount = NULL;

  this->sendToClient(output);

}