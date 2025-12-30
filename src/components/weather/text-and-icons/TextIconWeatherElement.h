#pragma once

#include "../text/TextWeatherElement.h"
#include "../../../input/custom_buttons/IconButton.h"
#include "../../../output/icons/weatherIcons.h"

namespace ui
{
    class TextIconWeatherElement: public TextWeatherElement
    {
        
    public:
        TextIconWeatherElement(
            const Weather&,
            int16_t x,
            int16_t y,
            IconProps* icon = nullptr,
            TextProps* Props = nullptr
        );

        virtual void
        init();

        virtual void
        draw();

        std::unique_ptr<IconButton> _icon;
    };
    
}