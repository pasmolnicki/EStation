#pragma once

#include "../weather/text/TextWeatherElement.h"
#include "../../providers/DateTimeProvider.h"

namespace ui
{
    class ClockSectionElement: public TextWeatherElement
    {
    public:
        ClockSectionElement(
            const Weather&, 
            int16_t x,
            int16_t y,
            TextProps* props = nullptr
        );

        virtual void
        updateState();

        virtual bool
        eventListener(Point* touch);

        // Forced by stack
        int16_t x, y, width, height;
    };
    
    
}