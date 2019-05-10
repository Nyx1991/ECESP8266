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
    ecWifiManager.SaveSsidToEEPROM(strdup(server->arg("ssid").c_str()));
    ecWifiManager.SavePassToEEPROM(strdup(server->arg("password").c_str()));
    ECParamManager::WriteCharString(PARAM_ADDR_NAME, PARAM_SIZE_NAME, strdup(server->arg("name").c_str()));
    ESP.reset();
  }
  else if(cmd == "setmqttconf")
  {
    IPAddress host;    
    host.fromString(server->arg("host"));
    const uint16_t* port = new uint16_t((uint16_t)atoi(server->arg("port").c_str()));
    const char* clientId = server->arg("clientId").c_str();
    const char* user = server->arg("username").c_str();
    const char* pass = server->arg("password").c_str();
    const char* topic = server->arg("topic").c_str();
    const char* fulltopic = server->arg("fulltopic").c_str();

    if(strlen(clientId) > 0)
      ECParamManager::WriteCharString(PARAM_ADDR_MQTT_CLIENTID, PARAM_SIZE_MQTT_CLIENTID, clientId);
    if(strlen(user) > 0)
      ECParamManager::WriteCharString(PARAM_ADDR_MQTT_USERNAME, PARAM_SIZE_MQTT_USERNAME, user);
    if(strlen(pass) > 0)
      ECParamManager::WriteCharString(PARAM_ADDR_MQTT_PASS, PARAM_SIZE_MQTT_PASS, pass);
    if(strlen(topic) > 0)
      ECParamManager::WriteCharString(PARAM_ADDR_MQTT_TOPIC, PARAM_SIZE_MQTT_TOPIC, topic);
    if(strlen(fulltopic) > 0)
      ECParamManager::WriteCharString(PARAM_ADDR_MQTT_FULLTOPIC, PARAM_SIZE_MQTT_FULLTOPIC, fulltopic);
    if(strlen(server->arg("host").c_str()) > 0)
      ECParamManager::WriteCharString(PARAM_ADDR_MQTT_HOST, PARAM_ADDR_MQTT_HOST, host.toString().c_str());
    if(strlen(server->arg("port").c_str()) > 0)
      ECParamManager::WriteUint16(PARAM_ADDR_MQTT_PORT, port);

    delete clientId;
    delete pass;
    delete user;
    delete topic;
    delete port;
    delete fulltopic;
    
    ESP.reset();
  }
  else if(cmd == "setdevicename")
  {
    ECParamManager::WriteCharString(PARAM_ADDR_NAME, PARAM_SIZE_NAME, strdup(server->arg("name").c_str()));
    ESP.reset();
  }
  else if(cmd == "getdevicename")
  {
    char* name = ECParamManager::ReadCharString(PARAM_ADDR_NAME, PARAM_SIZE_NAME);
    output = String(name);    
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