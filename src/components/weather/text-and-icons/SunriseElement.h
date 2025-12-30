#pragma once

#include "TextIconWeatherElement.h"

namespace ui
{
    class SunriseElement: public TextIconWeatherElement
    {
        public:
        SunriseElement(
            const Weather&, 
            int16_t x, 
            int16_t y, 
            uint16_t bg, 
            TextProps* props = nullptr
        );
    };
}