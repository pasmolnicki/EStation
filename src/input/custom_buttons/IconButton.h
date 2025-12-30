#pragma once

#include "../TouchButton.h"
#include "../../output/icons/icons.h"

#include "../../data_structures/Props.h"

extern TFT_eSPI tft;

namespace ui
{

    class IconButton: public TouchButton
    {
        public:
        IconButton(
            uint16_t x, uint16_t y,
            IconProps* props = nullptr
        );

        void
        draw();

        void
        setIcon(Icon* icon = nullptr);

        void
        clear();

        std::unique_ptr<IconProps> _props;
    };
}