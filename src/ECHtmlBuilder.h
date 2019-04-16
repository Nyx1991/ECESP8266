#ifndef ECHTMLBUILDER_H
#define ECHTMLBUILDER_H

#include <Arduino.h>
#include "ECGPIO.h"

class ECHtmlBuilder
{
    private:
        const String css = "<style>body{background:#424242;font-family:\"LucidaGrande\",\"LucidaSansUnicode\",\"LucidaSans\",\"DejaVuSans\",Verdana,\"sans-serif\";font-size:36px;color:white;}h1{display:block;font-size:2em;margin-block-start:0.67em;margin-block-end:0.67em;margin-inline-start:0px;margin-inline-end:0px;font-weight:bold;}.gpio_row{display:flex;width:320px;}.gpios{display:inline-block;color:black;}.gpio{background:#C4C4C4;width:150px;height:150px;margin:5px;padding-left:10px;text-align:left;border-radius:20px;}.ON{background:#00C816;}.OFF{background:#CC0003;}.ON:hover{background:#00DC04;cursor:pointer;}.OFF:hover{background:#FF0105;cursor:pointer;}.gpio_title{padding-top:15px;font-size:32px;font-family:\"LucidaGrande\",\"LucidaSansUnicode\",\"LucidaSans\",\"DejaVuSans\",Verdana,\"sans-serif\";}.state{padding-top:20px;font-size:42px;}.content_wrapper{margin:10pxauto;text-align:center;}input,button{margin-top:10px;border:0;background-color:#313131;font-size:24px;text-align:center;color:white;height:50px;width:450px;border-radius:50px;box-shadow:5px6px2px0px#0202021a;}textarea:focus,input:focus,button:focus{outline:none;}button:hover{cursor:pointer;color:#B5B5B5;}</style>";
        const String script = "<script>functiONsetState(_gpio,_state){varreq=newXMLHttpRequest();req.open(\"GET\",\"/cmd?cmd=set&gpio=\"+_gpio+\"state=\"+_state);req.send();alert(req.respONseText);}</script>";
        const String header = "<!doctype html><html><head>" + script + css + "<meta charset=\"utf-8\"><title>ecESP8266</title></head>";
        const String body = "</body></html>";    
        const String WiFiConfigPage = "<div class=\"content_wrapper\"><h1>Welcome!</h1><form action=\"/cmd\" method=\"get\">	<input type=\"hidden\" value=\"setwificonf\" name=\"cmd\" />	<input name=\"ssid\" type=\"text\" placeholder=\"SSID\" /></br>	<input name=\"password\" type=\"password\" placeholder=\"PASSWORD\" /></br>	<button type=\"submit\">Save and reboot</button></form></div>";

    public:
        String GetWiFiConfigPage();
        String GetGPIOHtml(ECGPIO* _gpio);
};

#endif