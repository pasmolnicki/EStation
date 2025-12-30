#include "ClockSectionElement.h"

namespace ui
{
    ClockSectionElement::ClockSectionElement(
        const Weather& weather, 
        int16_t x,
        int16_t y,
        TextProps* props
    ): TextWeatherElement(Weather(), x, y, props) {}    

    void ClockSectionElement::updateState(){
        if (!_redraw){
            return;
        }
        draw();
    }

    bool ClockSectionElement::eventListener(Point* touch){
        return false;
    }
}