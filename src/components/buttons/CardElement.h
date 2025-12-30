#pragma once

#include "TextElement.h"
#include "../../input/custom_buttons/IconButton.h"

namespace ui
{
    class CardElement: public ScreenElement
    {
        int16_t _x;
        int16_t _y;
        int16_t _w;
        int16_t _h;
        uint16_t _bg;
        uint16_t _color;
    public:
        CardElement(
            int16_t x,
            int16_t y,
            int16_t w,
            int16_t h,
            uint16_t color,
            uint16_t bg,
            TextProps* header = nullptr,
            TextProps* content = nullptr
        );

        void 
        setHeaderTextProps(TextProps* props = nullptr);

        void 
        setContentTextProps(TextProps* props = nullptr);

        void 
        prepareProps(Props* props);

        void 
        setHeaderText(const String&);

        void 
        setContentText(const String&);

        void 
        addIcon(IconProps*, std::function<void(void)> onClickHandler);

        void 
        draw();

        void 
        clear();

        void 
        addOnClickEvent(std::function<void(void)>);

        virtual bool
        eventListener(Point* touch);
        
        std::unique_ptr<TextButton> _header;
        std::unique_ptr<TextButton> _content;
        std::unique_ptr<IconButton> _icon;
        std::unique_ptr<TouchButton> _field;
    };

}