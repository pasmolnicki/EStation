#pragma once

#include "../DataElement.h"
#include "../../input/custom_buttons/IconButton.h"

namespace ui
{
    class IconButtonElement: public ScreenElement
    {
        public:
        IconButtonElement(
            uint16_t x,
            uint16_t y,
            IconProps* props = nullptr
        );

        virtual void
        draw();

        void 
        addOnClickEvent(std::function<void(void)>);

        virtual bool
        eventListener(Point* touch);

        std::unique_ptr<IconButton> _icon;
    };
}