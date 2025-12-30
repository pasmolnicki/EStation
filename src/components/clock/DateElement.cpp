#include "DateElement.h"

// Defined in `src/providers/DateTimeProvider.cpp`
extern DateTimeProvider dateProvider;

namespace ui
{
    DateElement::DateElement(
        const Weather& init, 
        int16_t x, 
        int16_t y, 
        TextProps* props,
        const date_format& format 
    ): TextWeatherElement(init, x, y, props)
    {
        _format = format;
        setter([this](const Weather& _data){
            return dateProvider.formatDate(_format);
        });
    }
}