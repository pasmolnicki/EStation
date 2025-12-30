#pragma once

#include "../base/DataBaseScreen.h"
#include "../../components/buttons/TextIconElement.h"
#include "../../components/buttons/TextElement.h"

namespace ui
{
    class SettingsScreen: public DataBaseScreen<TextIconElement>
    {
        std::unique_ptr<TextElement> _title;
    public:
        SettingsScreen();

        void 
        draw();
    };
    
}