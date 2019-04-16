#include "ECHtmlBuilder.h"

String ECHtmlBuilder::GetWiFiConfigPage()
{
    return header + WiFiConfigPage + body;
}

String ECHtmlBuilder::GetGPIOHtml(ECGPIO* _gpio)
{    
    String clickFunction;

    if (_gpio->GetPinMode() == OUTPUT && _gpio->GetPinType() == DIGITAL)
    {
        clickFunction = "toggleState("+String(_gpio->GetPinNumber())+")";
    }

    return "<div class=\"gpio "+_gpio->GetValueText()+"\"><div class=\"state\">"+ _gpio->GetValueText() +"</div><div class=\"gpio_title\">"+ _gpio->GetCaption() +"</div></div>";
}