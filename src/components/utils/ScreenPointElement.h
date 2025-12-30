#pragma once

#include <vector>

#include "../ScreenElement.h"
#include "../../router/paths.h"
#include "../../data_structures/Hsv_to_rgb.h"

namespace ui
{
    class ScreenPointElement: public ScreenElement
    {
        std::vector<uint16_t> _colors;
        uint16_t size, bg;
        int16_t x, y;
    public:
        ScreenPointElement(
            int16_t x, int16_t y, 
            uint16_t size, uint16_t bg
        );

        void 
        draw(const path&);
    };
}