#include "SunsetElement.h"

extern Localizer localizer;

namespace ui
{
    SunsetElement::SunsetElement(
        const Weather& init,
        int16_t x, 
        int16_t y,
        uint16_t bg,
        TextProps* props
    ): TextIconWeatherElement(
        init, x, y, new IconProps(new SunsetIcon(), 25, bg), props
    ) 
    {
        (void)setter([](const Weather& _data){
            time_t t = _data._sunset + _data._timezone;
            return localizer.getDateFormatter()(localtime(&t), date_format::hour_minute);
        });
    }
}