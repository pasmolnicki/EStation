#pragma once

#include "buttons/CardElement.h"
#include "buttons/TextElement.h"
#include "buttons/IconButtonElement.h"

namespace ui
{
    void makePopup(
        String header, String content,
        uint16_t width, uint16_t height, 
        uint16_t bg = 0x0042, uint16_t color = 0x1041,
        uint16_t header_color = 0xDD13
    );

    void makeErrorPage(
        String reason, String content
    );
}

