#pragma once

#include "../TouchButton.h"
#include "../../output/icons/icons.h"
#include "../../output/button.h"
#include "../../data_structures/Props.h"

extern TFT_eSPI tft;


namespace ui
{

    class TextIconButton: public TouchButton
    {
        public:
        TextIconButton(
            uint16_t x, uint16_t y,
            uint16_t w, uint16_t h,
            uint16_t bg,  
            TextProps* text = nullptr,
            IconProps* icon = nullptr
        );

        void
        draw();

        TextIconButton*
        setTextProps(TextProps* props = nullptr);

        TextIconButton*
        setIconProps(
            IconProps* props = nullptr
        );

        void 
        setIcon(Icon* icon);

        void 
        setText(const String&);

        void
        clear();

        std::unique_ptr<TextProps> _text_props;
        std::unique_ptr<IconProps> _icon_props;
    };
}