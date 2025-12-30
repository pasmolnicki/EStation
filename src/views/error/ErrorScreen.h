#pragma once

#include "../base/DataBaseScreen.h"
#include "../../components/buttons/TextElement.h"

namespace ui
{
    class ErrorScreen: public DataBaseScreen<TextElement>
    {
    public:
        const static auto errorBg = 0x1041;

        ErrorScreen();
    };
}