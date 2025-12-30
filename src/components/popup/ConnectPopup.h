#pragma once

#include "LoadingPopup.h"
#include "../../input/custom_buttons/TextButton.h"
#include "../../font-loader/textUtlis.h"
#include "../../providers/WiFiProvider.h"

#include "../../tasks/includes.h"

namespace ui
{
    class ConnectPopup: public LoadingPopup
    {
    public:
        ConnectPopup(
            int16_t x,
            int16_t y,
            int16_t w,
            int16_t h,
            uint16_t bg
        );
    };
}