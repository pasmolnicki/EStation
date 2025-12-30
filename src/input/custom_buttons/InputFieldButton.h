#pragma once

#include "../TouchButton.h"
#include "../../data_structures/Props.h"    
#include "../../font-loader/textUtlis.h"

namespace ui
{
    class InputFieldButton: public TouchButton
    {
        String _placeholder;
        int16_t _blinkX;
        uint64_t _lastBlinkTime;
        bool _blinkOn;
        bool _forceUpdate;
    public:
        InputFieldButton(
            int16_t x,
            int16_t y,
            int16_t w,
            int16_t h,
            uint16_t bg,
            TextProps* props = nullptr
        );
        
        void 
        draw();

        void
        setText(const String&);

        void 
        addText(const String&);

        void 
        delChar();

        void
        blink();

        std::unique_ptr<TextProps> _props;
    };
    
    
}