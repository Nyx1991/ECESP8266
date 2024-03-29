#ifndef ECHTMLBUILDER_H
#define ECHTMLBUILDER_H

#include <Arduino.h>
#include "ECGPIO.h"
#include "ECGPIOManager.h"
#include "ECSettingsManager.h"
#include "ECMQTTManager.h"
#include <ESP8266WiFi.h>

extern ECMQTTManager *ecMQTTManager;
extern ECSettings settings;

class ECHtmlBuilder
{
    private:     
        const String deviceNameStr = (String)settings.name;   
        const String htmlhead = "<html>"
        "<head>"
        "<style>"
        "body"
        "{"
            "background:#424242;"
            "font-family:'LucidaGrande','LucidaSansUnicode','LucidaSans','DejaVuSans',Verdana,'sans-serif';"
            "font-size:36px;"
            "color:white;"
            "text-align: center;"
        "}"
        "h1{"
        "    display:block;"
            "font-weight:bold;"
        "}"
        "h2"
        "{"
            "font-size: 22px;"
        "}"
        "table"
        "{"
        "	display: inline-table;"
            "text-align: left;	"
            "font-size: 14px;"
        "}"
        "tr"
        "{"
        "	height: 20px;"
        "}"
        "td"
        "{"
        "	width: 300px;"
        "}"
        ".nav"
        "{"
            "margin-top: 50px;"
            "color: #B9B9B9;"
            "font-size: 14px;"
        "}"
        ".nav a"
        "{"
            "color: #B9B9B9;"
            "text-decoration: none;"
        "}"
        ".nav a:hover"
        "{"
            "color: white;"
            "text-decoration: none;"
        "}"
        ".gpio.ON {"
            "background:#00C816;"
        "}"
        "	"
        ".gpio.OFF{"
            "background:#CC0003;"
        "}"
        "	"
        ".ON:hover {"
            "background:#00DC04;"
            "cursor:pointer;"
        "}"
        "	"
        ".OFF:hover {"
            "background:#FF0105;"
            "cursor:pointer;"
        "}"
        ".gpr{"
            "display:flex;"
            "width:auto;"
        "}"
        ".gps{"
            "display:inline-block;"
            "color:black;"
        "}"
        ".gpio{"
            "background:#C4C4C4;"
            "width:150px;"
            "height:150px;"
            "margin:5px;"
            "padding-left:10px;"
            "text-align:left;"
            "border-radius:20px;"
        "}"
        ".gpt{"
            "padding-top:15px;"
            "font-size:32px;"
            "font-family:'Lucida Grande','Lucida  SansUnicode','Lucida Sans','Deja Vu Sans',Verdana,'sans-serif';"
        "}"
        ".gst{"
            "padding-top:20px;"
            "font-size:42px;"
        "}"
        ".wr {"
            "text-align:center;"
        "}"
        "input, button {"        
            "margin-top: 10px;"
            "border: 0;"
            "background-color: #313131;"
            "font-size: 24px;"
            "text-align: center;"
            "color: white;"
            "height: 50px;"
            "width: 450px;"
            "border-radius: 50px;"
            "box-shadow: 5px 6px 2px 0px #0202021a;"
        "}"
        "textarea:focus, input:focus, button:focus"
        "{"
            "outline: none;"
        "}"
        "button:hover"
        "{"
            "cursor: pointer;"
            "color: #B5B5B5;"
        "}"
        "</style>"
        "<script>"        
            "var x, g, j, t, i;"
            "function initPage()"
            "{		"
                "g = document.getElementById('gps');"
                "x = new XMLHttpRequest();"
                "x.onreadystatechange = function()"
                "{"
                    "if (x.readyState == 4 && x.status == 200)"
                    "{"
                        "g.innerHTML = x.responseText;"
                        "updatePage();"
                    "}"
                "};"
                "x.open('GET', '/cmd?cmd=statushtml');"
                "x.send();"                
            "}"
            "function toggle(_g)"
            "{"
                "x = new XMLHttpRequest();"
                "x.open('GET', '/cmd?cmd=toggle&gpio='+_g);"
                "x.send();"
                "updatePage();"
            "}"
            "function updatePage()"
            "{"
                "if (t != null)"
                    "clearTimeout(t);"
                "x = new XMLHttpRequest();"
                "x.onreadystatechange = function()"
                "{"
                    "if (x.readyState == 4 && x.status == 200)"
                    "{"
                        "j = JSON.parse(x.responseText);"
                        "for(i in j)"
                        "{"
                            "g = document.getElementById(j[i].GPIO);"
                            "g.setAttribute('class', 'gpio '+j[i].ValueText);"
                            "g.getElementsByClassName('gst')[0].innerHTML = j[i].ValueText;"
                        "}"
                    "}"
                "};"
                "x.open('GET', '/cmd?cmd=status');"
                "x.send();"
                "t = setTimeout(updatePage, 1500);"
            "}"
            "window.onload = initPage;"
        "</script>"
        "<meta charset='utf-8'>"
        "<title>"+deviceNameStr+"</title>"
        "</head>"
        "<body>";
        const String body = "<div class='nav'><a href='/'>Home</a> | <a href='/wifi'>WiFi</a> | <a href='/mqtt'>MQTT</a> | <a href='/sysinfo'>System</a></div></body></html>";    
        const String wiFiConfigPage = "<div class='wr'><h1>WiFi</h1><form action='/cmd' method='get'>"
                                    "<input type='hidden' value='setwificonf' name='cmd' />"
                                    "<input value='"+String(settings.name)+"' name='name' type='text' placeholder='DEVICE NAME' /></br>"
                                    "<input value='"+String(settings.ssid)+"' name='ssid' type='text' placeholder='SSID' /></br>"
                                    "<input value='"+String(settings.pass)+"' name='password' type='password' placeholder='PASSWORD' /></br>"
                                    "<button type='submit'>Save and reboot</button></form></div>";

        const String indexPage = "<div class='wr'><h1>"+deviceNameStr+"</h1><div id='gps' class='gps'></div>";
        const String SystemInfoPage = "<div class='wr'><h1>System</h1>";
        const String MqttConfigurationPage = "<div class='wr'><h1>MQTT<form action='/cmd' method='get'></h1>";
        String GetECGPIOHtmlForECGPIO(ECGPIO* _gpio);     

    public:
        String GetWiFiConfigHtml();
        String GetIndexHtml();
        String GetSystemInfoHtml();
        String GetMqttConfHtml();
        //String GetBlynkConfHtml();
        String GetECGPIOHtml();
};

#endif