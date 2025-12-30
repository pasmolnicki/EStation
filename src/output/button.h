#pragma once

#include "../font-loader/FontLoader.h"
#include "../font-loader/textUtlis.h"
#include "../data_structures/Props.h"
#include "components.h"

extern char* NORMAL_FONT;

void drawMenuButton(
    uint16_t x, uint16_t y,
    uint16_t w, uint16_t h,
    uint16_t color, uint16_t bg,
    TextProps* props
);

void drawTextButton(
    int16_t x, int16_t y,
    TextProps* props,
    TFT_eSprite* sprite = nullptr
);

void drawIconProps(
    IconProps* __props
);
