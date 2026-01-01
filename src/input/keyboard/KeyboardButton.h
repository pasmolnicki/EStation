#pragma once

#include <memory>

#include "../TouchButton.h"
#include "../../data_structures/Props.h"
#include "../../output/button.h"

namespace ui
{
    class KeyboardButton: public TouchButton
    {
    public:
        KeyboardButton(
            int16_t x, 
            int16_t y, 
            int16_t width, 
            int16_t height,
            uint16_t bg,
            TextProps* props = nullptr
        );
        
        void 
        draw();

        std::unique_ptr<TextProps> _props;
    };
    
}