#include "TimeElement.h"

extern Localizer localizer;

namespace ui
{
    TimeElement::TimeElement(
        const Weather& init,
        int16_t x,
        int16_t y,
        TextProps* Props,
        const date_format& format
    ): TextWeatherElement(init, x, y, Props), _format(format) {

        setter([this](const Weather& data){
            time_t t = data._dt;
            return (localizer.getDateFormatter()(localtime(&t), _format)); 
        });
        onUpdate();
    }
}