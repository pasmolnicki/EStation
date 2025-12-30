#pragma once

#include "../DataElement.h"
#include "../../data_structures/Props.h"
#include "../../font-loader/textUtlis.h"
#include "../../input/custom_buttons/InputFieldButton.h"

namespace ui
{
    class InputFieldElement: DataElement<String>
    {
        std::unique_ptr<InputFieldButton> _button;
    public:
        InputFieldElement(
            int16_t x,
            int16_t y,
            uint16_t w,
            uint16_t h,
            uint16_t bg,
            TextProps* props = nullptr
        );
        
        void 
        draw();

        virtual bool
        eventListener(Point* touch);

        void 
        addOnClickEvent(std::function<void(void)>);

        void
        addChar(const String&);

        const String&
        getValue();

        void
        blink();

        void 
        deleteChar();
    };    
}