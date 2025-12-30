#pragma once

#include "../ScreenElement.h"
#include "../../input/custom_buttons/TextIconButton.h"

namespace ui
{
    class TextIconElement: public ScreenElement
    {
        std::unique_ptr<TextIconButton> _btn;
    public:
        TextIconElement(
            uint16_t x, uint16_t y,
            uint16_t w, uint16_t h,
            uint16_t bg,  
            TextProps* text = nullptr,
            IconProps* icon = nullptr
        );

        void
        draw();

        void 
        addOnClickEvent(std::function<void(void)>);
        
        bool 
        eventListener(Point* touch);

        TextIconElement*
        setTextProps(TextProps* props = nullptr);

        TextIconElement*
        setIconProps(
            IconProps* props = nullptr
        );

        void 
        setIcon(Icon* icon);

        void 
        setText(const String&);

        void
        clear();
    };
}