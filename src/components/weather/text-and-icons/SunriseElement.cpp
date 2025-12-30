#include "SunriseElement.h"

extern Localizer localizer;

namespace ui
{
    SunriseElement::SunriseElement(
        const Weather& init,
        int16_t x, 
        int16_t y,
        uint16_t bg,
        TextProps* props
    ): TextIconWeatherElement(
        init, x, y, new IconProps(new SunriseIcon(), 25, bg), props
    ) {
        (void)setter([](const Weather& _data){
            time_t t = _data._sunrise + _data._timezone;
            return localizer.getDateFormatter()(localtime(&t), date_format::hour_minute);
        });
    }
}