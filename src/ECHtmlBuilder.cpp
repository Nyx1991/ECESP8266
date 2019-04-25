#include "ECHtmlBuilder.h"

String ECHtmlBuilder::GetWiFiConfigPage()
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
    for (int i=0; i < ecGPIOManager.GetECGPIOCount(); i++)
    {      
        ret += this->GetECGPIOHtmlForECGPIO(&ecGPIOManager.GetGPIOArray()[i]);        
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