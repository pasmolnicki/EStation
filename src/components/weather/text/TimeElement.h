#pragma once

#include "TextWeatherElement.h"

namespace ui
{
    class TimeElement: public TextWeatherElement
    {
        date_format _format;
        public:
        TimeElement(
            const Weather&,
            int16_t x,
            int16_t y,
            TextProps* Props = nullptr,
            const date_format& format = date_format::hour_minute
        );
    };
}