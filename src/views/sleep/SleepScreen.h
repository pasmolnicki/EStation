#pragma once

#include "../base/DataBaseScreen.h"
#include "../../components/sleep/SleepElement.h"

namespace ui
{
    class SleepScreen: public DataBaseScreen<SleepElement>
    {
        public:
        SleepScreen();

        void loop();
    };
} // namespace ui
