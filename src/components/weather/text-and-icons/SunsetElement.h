#include "TextIconWeatherElement.h"

namespace ui
{
    class SunsetElement: public TextIconWeatherElement
    {
        public:
        SunsetElement(
            const Weather& init,
            int16_t x, 
            int16_t y,
            uint16_t bg,
            TextProps* props = nullptr
        );
    };
}