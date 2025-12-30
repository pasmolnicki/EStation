#pragma once

#include "TextIconWeatherElement.h"

namespace ui
{
    class DropletElement: public TextIconWeatherElement
    {
        Icon* matchIcon();

        int8_t _prevPop;
        int8_t _prevIcon;
    public:
        DropletElement(
            const Weather&, int16_t x, int16_t y,
            uint16_t bg, TextProps* textProps = nullptr
        );
    };
}