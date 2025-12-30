#pragma once

#include "IconWeatherElement.h"
#include "../../../output/icons/weatherIcons.h"

namespace ui
{
    class WeatherDisplayElement: public IconWeatherElement
    {
        bool _day;
        int _icon;

        Icon* weatherIconMatcher();
        public:

        WeatherDisplayElement(  
            const Weather&,
            int16_t x,
            int16_t y,
            IconProps* Props = nullptr
        );

        virtual void
        onUpdate();
    };
}