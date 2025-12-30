#pragma once

#include "../weather/text/TextWeatherElement.h"
#include "../../providers/DateTimeProvider.h"

namespace ui
{
    /// @brief Represents visually date, DateTimeProvider should be initialized before
    /// CONSTRUCTING this class
    class DateElement: public TextWeatherElement
    {
        date_format _format;
    public:
        DateElement(
            const Weather& init, 
            int16_t x, 
            int16_t y, 
            TextProps* props = nullptr,
            const date_format& format = date_format::full_date
        );
    };
    
}