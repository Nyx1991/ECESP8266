#include "ECWebServer.h"
#include "ECGPIOManager.h"
#include "ECWiFiManager.h"
#include "ECGPIO.h"

extern ECGPIOManager ecGPIOManager;
extern ECWiFiManager ecWifiManager;

ECWebServer::ECWebServer()
{
  if (!Serial)
  {
    Serial.begin(115200);
  }

  server = new ESP8266WebServer(80);
  server->on("/", std::bind(&ECWebServer::onIndex, this));
  server->on("/cmd", std::bind(&ECWebServer::onCmd, this));  
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
    sendToClient("Index");
  }  
}

void ECWebServer::onCmd()
{
  String output;
  String cmd = server->arg("cmd");
  ECGPIO* gpio = nullptr;
  ECGPIO* gpios = nullptr;    
  int gpioCount = ecGPIOManager.GetECGPIOCount();  
  int pin;
  
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
      gpio = &ecGPIOManager.GetGPIOArray()[i];
      output += gpio->GetJSON();
      if (i+1 != ecGPIOManager.GetECGPIOCount())
      {
        output += ",";
      }
    }    
    output += "]";
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
    ecWifiManager.SaveSsidToEEPROM(strdup(server->arg("ssid").c_str()));
    ecWifiManager.SavePassToEEPROM(strdup(server->arg("password").c_str()));
    ESP.reset();
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
  pin = NULL;
  gpioCount = NULL;

  this->sendToClient(output);

}