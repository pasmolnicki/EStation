#pragma once

#include <TFT_eSPI.h>

void drawCard(
    uint16_t x, uint16_t y,
    uint16_t w, uint16_t h,
    uint16_t color, uint16_t bg
);

void drawInputField(
    uint16_t x, uint16_t y,
    uint16_t w, uint16_t h,
    uint16_t color, uint16_t outline,
    uint16_t bg
);

void drawWiFi(
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint8_t strength, 
    uint16_t bg
);

void drawLoadingState(
    uint16_t x, uint16_t y,
    uint16_t bg, uint16_t size,
    int16_t angle
);

void clearLoadingState(
    uint16_t x, uint16_t y,
    uint16_t bg, uint16_t size,
    int16_t angle
);

void drawLocker(
    int16_t x, int16_t y,
    int16_t size, uint16_t bg, 
    bool unLocked = false
);