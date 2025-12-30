#pragma once

#include <TFT_eSPI.h>

void drawCloud(
    uint16_t x, uint16_t y, uint16_t size, 
    uint16_t color,uint16_t depth_color, 
    uint16_t topLeftColorBg, 
    uint16_t topRightColorBg, 
    uint16_t background_color
);

void drawSun(
    uint16_t x, uint16_t y, uint16_t size, 
    uint16_t color, uint16_t background_color
);

void drawMoon(
    uint16_t x, uint16_t y, uint16_t size, 
    uint16_t color, uint16_t background_color
);

void drawDroplet(
    uint16_t x, uint16_t y, uint16_t size, 
    uint16_t color, uint16_t background_color
);

void  
drawSnowflake(
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t filler_circle_color, 
    uint16_t color, 
    uint16_t background_color
);

void  
drawMist (
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color, 
    uint16_t background_color
);

void
drawSunset(
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t bg_c
);

void
drawSunrise(
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t bg_c
);

void drawDropletIcon(
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t bg,
    uint8_t fill = 4
);