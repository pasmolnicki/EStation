#pragma once

#include "../DataElement.h"
#include "../../input/custom_buttons/TextIconButton.h"
#include "../../font-loader/textUtlis.h"
#include "../IconGroup.h"
#include "../../data_structures/WifiInfo.h"

namespace ui
{
    class WiFiBtnElement: public DataElement<WifiInfo>
    {
        String _text;
        Icon* iconMatcher();
        uint16_t bg;
        IconGroup _iconGroup;
    public:
        WiFiBtnElement(
            const WifiInfo& init,
            uint16_t x,
            uint16_t y,
            uint16_t w,
            uint16_t h,
            uint16_t bg,
            TextProps* props = nullptr
        );

        WiFiBtnElement(
            const WiFiBtnElement& other
        );

        WiFiBtnElement& operator=(const WiFiBtnElement& other);

        virtual void
        onUpdate();

        virtual void
        draw();

        void 
        addOnClickEvent(std::function<void(void)>);

        bool
        check(Point* touch);

        std::unique_ptr<TouchButton> _touchArea;
        std::unique_ptr<TextProps> _textProps;
    };
}