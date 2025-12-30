#pragma once

#include "../base/DataBaseScreen.h"
#include "../../components/buttons/TextIconElement.h"
#include "../../components/buttons/TextElement.h"
#include "../../lang/localizers/Localizer.h"

namespace ui
{
    class LocalizerScreen: public DataBaseScreen<TextIconElement>
    {
        TextElement _title;
    public:
        LocalizerScreen();

        void 
        draw();
    
        void 
        loop();
    };
}