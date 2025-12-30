#pragma once

#include "../WeatherElement.h"
#include "../../../input/custom_buttons/IconButton.h"

namespace ui
{
    class IconWeatherElement : public WeatherElement<IconButton>
    {
        
    public:
        IconWeatherElement(
            const Weather&,
            int16_t x,
            int16_t y,
            IconProps* Props = nullptr
        );

        virtual void 
        updateState();
    };
}
