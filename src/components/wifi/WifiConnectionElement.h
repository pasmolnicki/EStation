#pragma once

#include "../ScreenElement.h"
#include "../../data_structures/Props.h"
#include "../../providers/WiFiProvider.h"

namespace ui
{
    class WifiConnectionElement: public ScreenElement
    {
        int64_t _lastCheck;
        int _strenght;
        std::unique_ptr<IconProps> _icon;
    public:
        enum ConnectionStrength
        {
            STRONG = 0,
            GREAT = 1,
            MEDIUM = 2,
            WEAK = 3,
            NO_CONNECTION = 4
        };

        WifiConnectionElement(
            int16_t x,
            int16_t y,
            int16_t size,
            uint16_t bg
        );

        void 
        draw();

        void 
        onUpdate();

        virtual void
        updateState();

        Icon* iconMatcher();
    };
    
}