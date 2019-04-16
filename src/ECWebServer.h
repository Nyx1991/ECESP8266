#ifndef ECWEBSERVER_H
#define ECWEBSERVER_H

#include <ESP8266WebServer.h>
#include "ECHtmlBuilder.h"

class ECWebServer
{
  private:
    ESP8266WebServer* server;    
    void onIndex();
    void onCmd();
    void sendToClient(String _message);    
    ECHtmlBuilder ecHtmlBuilder;
    
  public: 
    ECWebServer();
    ~ECWebServer();
    void begin();
    void listen();    
};

#endif