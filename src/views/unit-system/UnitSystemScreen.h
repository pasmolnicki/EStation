#pragma once

#include "../base/DataBaseScreen.h"

#include "../../components/buttons/CardElement.h"
#include "../../components/buttons/IconButtonElement.h"

namespace ui
{
    class UnitSystemScreen: public DataBaseScreen<CardElement>
    {
        TextElement _title;
        std::unique_ptr<IconButtonElement> _return;
    public:
        UnitSystemScreen();

        void 
        draw();

        void 
        loop();
    };

    
}