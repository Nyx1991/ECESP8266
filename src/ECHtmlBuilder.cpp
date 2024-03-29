#include "ECHtmlBuilder.h"

String ECHtmlBuilder::GetWiFiConfigHtml()
{ 
    return htmlhead + wiFiConfigPage + body;
}

String ECHtmlBuilder::GetIndexHtml()
{    
    return htmlhead + indexPage + body;
}

String ECHtmlBuilder::GetECGPIOHtml()
{
    String ret = "";   
    for (int i=0; i < ECGPIOManager::GetECGPIOCount(); i++)
    {    
        if (i % 2 == 0)
        {
            ret += "<div class='gpr'>";
        }
        ret += this->GetECGPIOHtmlForECGPIO(ECGPIOManager::GetGPIOArray()[i]);        
        if (i % 2 == 1)
        {
            ret += "</div>";
        }
    }
    return ret;
}

String ECHtmlBuilder::GetECGPIOHtmlForECGPIO(ECGPIO* _gpio)
{
    String pinNumber = String(_gpio->GetPinNumber());
    String ret = "";
    String divGst = "class='gpio " + _gpio->GetValueText() + "'><div class='gst'>" + _gpio->GetValueText() + "</div><div class='gpt'>" + _gpio->GetCaption() + "</div></div>";
    ret += "<div id='" + pinNumber + "' onclick='";

    if (_gpio->GetPinMode() == OUTPUT)
    {
        if (_gpio->GetPinType() == DIGITAL)
        {
            ret += "toggle(" + pinNumber + ")' " + divGst;
        }
        else if (_gpio->GetPinType() == ANALOG)
        {
            ret += "setValue(" + pinNumber + ")' " + divGst;
        }
        else
        {
            ret += "alert('undefined') ";
        }
    }
    else if (_gpio->GetPinMode() == INPUT)
    {
        ret += "' " + divGst;
    }
    else
    {
        ret += "alert('undefined') ";
    }    
    return ret;
}

String ECHtmlBuilder::GetSystemInfoHtml()
{
    long millisecs = millis();
    int systemUpTimeMn = int((millisecs / (1000 * 60)) % 60);
    int systemUpTimeHr = int((millisecs / (1000 * 60 * 60)) % 24);
    int systemUpTimeDy = int((millisecs / (1000 * 60 * 60 * 24)) % 365);

    String ret = htmlhead + SystemInfoPage;    
    ret += "<table>";

    ret += "<tr><td>Device Name</td><td>"+deviceNameStr+"</td></tr>";
    ret += "<tr><td>Uptime</td><td>"+String(systemUpTimeDy)+"d "+String(systemUpTimeHr)+"h "+String(systemUpTimeMn)+"m</td></tr>";
    ret += "<tr><td></td><td></td></tr>";
    ret += "<tr><td>SSID</td><td>"+WiFi.SSID()+" ("+ String(WiFi.RSSI())  +" dBm)</td></tr>";
    ret += "<tr><td>Hostname</td><td>"+WiFi.hostname()+"</td></tr>";
    ret += "<tr><td>IP-Address</td><td>"+WiFi.localIP().toString()+"</td></tr>";
    ret += "<tr><td>Gateway</td><td>"+WiFi.gatewayIP().toString()+"</td></tr>";
    ret += "<tr><td>Subnetmask</td><td>"+WiFi.subnetMask().toString()+"</td></tr>";
    ret += "<tr><td>DNS-Server</td><td>"+WiFi.dnsIP().toString()+"</td></tr>";
    ret += "<tr><td>MAC Address</td><td>"+WiFi.macAddress()+"</td></tr>";
    ret += "<tr><td></td><td></td></tr>";
    ret += "<tr><td>MQTT active</td><td>"+String(ecMQTTManager->isActive())+"</td></tr>";
    ret += "<tr><td>MQTT client id</td><td>"+String(settings.mqttClientid)+"</td></tr>";
    ret += "<tr><td>MQTT username</td><td>"+String(settings.mqttUsername)+"</td></tr>";
    ret += "<tr><td>MQTT topic</td><td>"+String(settings.mqttTopic)+"</td></tr>";
    ret += "<tr><td>MQTT fulltopic</td><td>"+String(settings.mqttFulltopic)+"</td></tr>";
    ret += "<tr><td>MQTT host</td><td>"+String(settings.mqttHost)+"</td></tr>";
    ret += "<tr><td>MQTT port</td><td>"+String(settings.mqttPort)+"</td></tr>";
    ret += "<tr><td></td><td></td></tr>";
    ret += "<tr><td>Core Version</td><td>"+ESP.getCoreVersion()+"</td></tr>";
    ret += "<tr><td>SDK Version</td><td>"+String(ESP.getSdkVersion())+"</td></tr>";
    ret += "<tr><td>ESP Chip ID</td><td>"+String(ESP.getChipId())+"</td></tr>";    
    ret += "<tr><td>Flash Chip ID</td><td>"+String(ESP.getFlashChipId())+"</td></tr>";
    ret += "<tr><td>Flash Size</td><td>"+String(ESP.getFlashChipRealSize() / 1024)+" kB</td></tr>";
    ret += "<tr><td>Program Flash Size</td><td>"+String(ESP.getFlashChipRealSize() / 1024)+" kB</td></tr>";
    ret += "<tr><td>Program Size</td><td>"+String(ESP.getSketchSize() / 1024)+" kB</td></tr>";
    ret += "<tr><td>Free Flash Size</td><td>"+String(ESP.getFreeSketchSpace() / 1024)+" kB</td></tr>";
    ret += "<tr><td>Free Memory (Stack)</td><td>"+String(ESP.getFreeContStack() / 1024)+" kB</td></tr>";
    ret += "<tr><td>Free Memory (Heap)</td><td>"+String(ESP.getFreeHeap() / 1024)+" kB</td></tr>";
    ret += "<tr><td>Memory Fragmentation</td><td>"+String(ESP.getHeapFragmentation())+" %</td></tr>";
    ret += "<tr><td>CPU Frequenzy</td><td>"+String(ESP.getCpuFreqMHz())+" MHz</td></tr>";
    ret += "</table></div>"+body;

    return ret;
}

String ECHtmlBuilder::GetMqttConfHtml()
{    
    String ret = htmlhead + MqttConfigurationPage;
    ret += "<h2>Active: "+String(ecMQTTManager->isActive())+"</h2>";
    ret += "<input type='hidden' value='setmqttconf' name='cmd' />";
    ret += "<input value='"+String(settings.mqttHost)+"' name='host' type='text' placeholder='HOST' /></br>";
    ret += "<input value='"+String(settings.mqttPort)+"' name='port' type='text' placeholder='PORT (1883)' /></br>";
    ret += "<input value='"+String(settings.mqttClientid)+"' name='clientid' type='text' placeholder='CLIENT ID ("+deviceNameStr+"_"+(ESP.getChipId())+")' /></br>";
    ret += "<input value='"+String(settings.mqttUsername)+"' name='username' type='text' placeholder='USERNAME' /></br>";
    ret += "<input value='"+String(settings.mqttPass)+"' name='pass' type='password' placeholder='PASSWORD' /></br>";
    ret += "<input value='"+String(settings.mqttTopic)+"' name='topic' type='text' placeholder='TOPIC ("+deviceNameStr+"_"+(ESP.getChipId())+")'/></br>";
    ret += "<input value='"+String(settings.mqttFulltopic)+"' name='fulltopic' type='text' placeholder='FULL TOPIC (%topic%/%prefix%)' /></br>";
    ret += "<button type='submit'>Save and reboot</button></form></div>"+body;

    return ret;
}