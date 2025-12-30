#pragma once

#include "../ScreenElement.h"
#include "../../input/custom_buttons/TextButton.h"
#include "../../font-loader/textUtlis.h"

namespace ui
{
    class TextElement: public ScreenElement
    {
    public:
        TextElement(
            int16_t x,
            int16_t y,
            TextProps* props = nullptr
        );

        TextElement(
            const TextElement& other
        );

        TextElement& operator=(const TextElement& other);

        virtual void 
        draw();

        void 
        clear();

        void 
        setProps(TextProps*);

        void 
        setText(const String&);

        virtual void 
        updateState();

        String _prev;
        std::unique_ptr<TextButton> _text;
    };

    
}