#include "KeyboardButton.h"

namespace ui
{
    KeyboardButton::KeyboardButton(
        int16_t x, 
        int16_t y, 
        int16_t width, 
        int16_t height,
        uint16_t bg,
        TextProps* props
    ): TouchButton(x, y, width, height), _props(createDefaultIfNull(props)) {
        this->bg = bg;
        _props->bg = color;
    }

    void KeyboardButton::draw(){
        drawMenuButton(x, y, width, height, color, bg, _props.get());
    }
}