#pragma once

#include "../ScreenElement.h"
#include "../PosContainer.h"
#include "../../output/components.h"

namespace ui
{
    class LoadingElement: public ScreenElement, public PosContainer
    {
        public:
        LoadingElement(
            int16_t x,
            int16_t y,
            int16_t size,
            uint16_t bg
        );

        virtual void 
        draw();

        virtual void
        clear();

        void
        updateState();

        void 
        setLoading(bool);

        int16_t _angle;
        uint16_t _bg;

        uint64_t _lastUpdateTime;
        bool _isLoading;
    };
}