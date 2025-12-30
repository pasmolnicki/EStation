#include "weather.h"

extern TFT_eSPI tft;

void drawCloud(
    uint16_t x, uint16_t y, uint16_t size, 
    uint16_t color,uint16_t depth_color, 
    uint16_t topLeftColorBg, 
    uint16_t topRightColorBg, 
    uint16_t background_color
){
        //Cloud drawing
    // circles on the right and left
    tft.fillSmoothCircle(x+0.2f*size, y + size*0.24f, 0.14f*size, color, background_color);
    tft.fillSmoothCircle(x+0.8f*size, y + size*0.24f, 0.14f*size, color, background_color);

    // circle on the middle left
    tft.fillSmoothCircle(x+0.4f*size, y+0.2f*size, 0.18f*size, color, topLeftColorBg);

    // circle on the middle right
    tft.fillSmoothCircle(x+0.65f*size, y+0.15f*size, 0.15f*size, color, topRightColorBg);

    // rect, the filler
    tft.fillRoundRect(x+0.2f*size, y+size*0.1f, 0.6f * size + 1, 0.3f * size, 0.05f*size, color);

    // earase smoothing effect
    // tft.fillRect(x + 0.22f*size - 1, y + 10.76f*size + 1, 0.12f*size + 1, size*(10.76f  - 34.47f - 1), color);

    // 
    tft.fillSmoothCircle(x+0.4f*size, y+0.4f*size, 0.2f*size, depth_color, color);
    tft.fillSmoothCircle(x+0.65f*size, y+0.5f*size, 0.23f*size, depth_color, color);

    tft.fillRect(x + 0.45379f*size - 1, y + 0.28643f*size + 1, 0.145f*size + 2, 0.1f*size, depth_color);

    tft.fillRect(x, y + 0.38f*size, size, 0.4f * size, background_color);
}

void drawSun(
    uint16_t x, uint16_t y, uint16_t size, 
    uint16_t color, uint16_t background_color
){
    tft.fillSmoothCircle(x+size/2, y+size/2, size/2 * 0.50f, color, background_color);

    // ray drawing
    uint16_t 
        xc = x + size/2,
        yc = y + size/2,
        Ax = 0.85f * size + x,
        Ay = y + size/2,
        Bx = 0.95f*size + x,
        By = Ay; 

    for (uint8_t i=0; i<9; i++)
    {
        float angle = i * PI/4;
        uint16_t
            ax = (Ax - xc) * cosf(angle) - (Ay - yc) * sinf(angle) + xc,
            ay = (Ax - xc) * sinf(angle) + (Ay - yc) * cosf(angle) + yc,
            bx = (Bx - xc) * cosf(angle) - (By - yc) * sinf(angle) + xc,
            by = (Bx - xc) * sinf(angle) + (By - yc) * cosf(angle) + yc;

        tft.drawWideLine(ax, ay,bx , by, 0.05f * size, color, background_color);
    }
}

void drawMoon(
    uint16_t x, uint16_t y, uint16_t size, 
    uint16_t color, uint16_t background_color
){
    tft.fillSmoothCircle(x+0.45f*size, y + 0.5f*size, 0.45f*size, color, background_color);
    tft.fillSmoothCircle(x+0.65f*size, y + 0.42f*size, 0.4f*size, background_color, color);

    tft.fillRect(x + 0.49308f*size, y,size*(1.00f - 0.49308f) + 1, 0.2f*size + 1, background_color);
    tft.fillRect(x + 0.79011f*size, y + 0.2f*size, size*(1.06f - 0.79011f) + 1, size*0.59466f + 2, background_color);
}

void drawDroplet(
    uint16_t x, uint16_t y, uint16_t size, 
    uint16_t color, uint16_t background_color
){
    tft.fillCircle(x+size/2, y + size*0.7f, size*0.3f, color);
    tft.fillTriangle(x+0.2f*size, y + 0.7f*size, x + 0.8f*size, y + 0.7f*size, x + 0.5f*size, y, color);
}

void  
drawMist (
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color, 
    uint16_t background_color
)
{
    // lines going from down to up
    uint16_t ax = 0.3f*size + x,
            ay = 0.9f*size + y,
            bx = ax + 0.4f*size,
            by = ay;
    tft.drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);

    ay -= 0.1f*size;
    by = ay;

    ax -= 0.1f*size;
    bx += 0.1f*size;
    tft.drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);


    ay -= 0.1f*size;
    by = ay;

    ax = 0.05f*size + x;
    bx = 0.65f*size + x;
    tft.drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);


    ay -= 0.1f*size;
    by = ay;

    ax = 0.25f*size + x;
    bx = 0.85f*size + x;
    tft.drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);


    ay -= 0.1f*size;
    by = ay;

    ax = 0.07f*size + x;
    bx = 0.61f*size + x;
    tft.drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);


    ay -= 0.1f*size;
    by = ay;

    ax = 0.4f*size + x;
    bx = 0.6f*size + x;
    tft.drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);
}

void  
drawSnowflake(
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t filler_circle_color, 
    uint16_t color, 
    uint16_t background_color
)
{
    uint16_t Ax,Ay,Bx,By, xc = 0.5f*size + x, yc = 0.5f*size + y;

    // 1st 'right up' part
    Ax = x + 0.8f*size;
    Bx = Ax + 0.15f*size;

    Ay = y + 0.5f*size;
    By = Ay + 0.15f*size;
    for (uint8_t i=0; i<9; i++)
    {
        float angle = i * PI/4;
        uint16_t
            ax = (Ax - xc) * cosf(angle) - (Ay - yc) * sinf(angle) + xc,
            ay = (Ax - xc) * sinf(angle) + (Ay - yc) * cosf(angle) + yc,
            bx = (Bx - xc) * cosf(angle) - (By - yc) * sinf(angle) + xc,
            by = (Bx - xc) * sinf(angle) + (By - yc) * cosf(angle) + yc;

        tft.drawWideLine(ax, ay,bx , by, 0.03f * size, color, background_color);
    }

    // 2nd 'right down' part
    Ax = x + 0.8f*size;
    Bx = Ax + 0.15f*size;

    Ay = y + 0.5f*size;
    By = Ay - 0.15f*size;
    for (uint8_t i=0; i<9; i++)
    {
        float angle = i * PI/4;
        uint16_t
            ax = (Ax - xc) * cosf(angle) - (Ay - yc) * sinf(angle) + xc,
            ay = (Ax - xc) * sinf(angle) + (Ay - yc) * cosf(angle) + yc,
            bx = (Bx - xc) * cosf(angle) - (By - yc) * sinf(angle) + xc,
            by = (Bx - xc) * sinf(angle) + (By - yc) * cosf(angle) + yc;

        tft.drawWideLine(ax, ay,bx , by, 0.03f * size, color, background_color);
    }


    // main framework

    Ax = 0.61f * size + x;
    Ay = y + size/2;
    Bx = Ax + 0.35f*size;
    By = Ay; 

    for (uint8_t i=0; i<9; i++)
    {
        float angle = i * PI/4;
        uint16_t
            ax = (Ax - xc) * cosf(angle) - (Ay - yc) * sinf(angle) + xc,
            ay = (Ax - xc) * sinf(angle) + (Ay - yc) * cosf(angle) + yc,
            bx = (Bx - xc) * cosf(angle) - (By - yc) * sinf(angle) + xc,
            by = (Bx - xc) * sinf(angle) + (By - yc) * cosf(angle) + yc;

        tft.drawWideLine(ax, ay,bx , by, 0.03f * size, color, background_color);
    }
 
    // middle circle
    tft.fillSmoothCircle(x+0.5f*size, y+0.5f*size, 0.1f*size, color, background_color);
    tft.fillCircle(x+0.5f*size, y+0.5f*size, 0.06f*size, filler_circle_color);
}

void
drawSunGoingDown(
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t bg_c,
    uint16_t color
)
{
    drawSun(x, y, size, color, bg_c);
    tft.fillRect(x, y + size*0.6f, size, size*0.4f, bg_c);
    tft.fillSmoothRoundRect(x, y + size*0.6f, size, size*0.15f, size*0.1f + 1, color, bg_c);
}

void
drawSunset(
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t bg_c
)
{
    drawSunGoingDown(x, y, size, bg_c, 0xF240);
    tft.drawWideLine(
        float(x) + float(size)*0.5f, float(y) + float(size) * 0.75f,
        float(x) + float(size)*0.5f, float(y) + float(size),
        0.05f*size, 0xF240, bg_c);
    
    tft.drawWideLine(
        float(x) + float(size)*0.4f, float(y) + float(size) * 0.9f,
        float(x) + float(size)*0.5f, float(y) + float(size), 
        0.05f*size, 0xF240, bg_c);

    tft.drawWideLine(
        float(x) + float(size)*0.5f, float(y) + float(size),
        float(x) + float(size)*0.6f, float(y) + float(size)*0.9f,
        0.05f*size, 0xF240, bg_c);
}

void
drawSunrise(
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t bg_c
)
{
    drawSunGoingDown(x, y, size, bg_c, 0xF4E3);
    tft.drawWideLine(
        float(x) + float(size)*0.5f, float(y) + float(size) * 0.75f,
        float(x) + float(size)*0.5f, float(y) + float(size),
        0.05f*size, 0xF4E3, bg_c);

    tft.drawWideLine(
        float(x) + float(size)*0.4f, float(y) + float(size) * 0.85f,
        float(x) + float(size)*0.5f, float(y) + float(size) * 0.75f,
        0.05f*size, 0xF4E3, bg_c);

    tft.drawWideLine(
        float(x) + float(size)*0.5f, float(y) + float(size) * 0.75f,
        float(x) + float(size)*0.6f, float(y) + float(size) * 0.85f,
        0.05f*size, 0xF4E3, bg_c);
}

constexpr uint16_t 
    dropletColor = 0x1AF5,
    dropletFillColor = 0x341B;

void drawDropletSkeleton(
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t bg
) {
    tft.drawWideLine(x + size*0.1 + 1, y + 0.6f*size, x + 0.5f*size, y, 2, dropletColor, bg);
    tft.drawWideLine(x + size*0.9f - 1, y + 0.6f*size, x + 0.5f*size, y, 2, dropletColor, bg);
    tft.drawSmoothArc(x + size*0.5f, y + size*0.6f, size*0.4f, size*0.4f - 2, 270, 90, dropletColor, bg);
}

void drawDropletIcon(
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t bg,
    uint8_t fill
) {
    if (fill){
        tft.fillSmoothCircle(x + 0.5f*size, y + 0.6f*size, 0.4f*size - 4, dropletFillColor, bg);
    }
    
    switch(fill){
        case 1:
            tft.fillRect(x + 0.1f*size, y, 0.8f*size, 0.6f*size + 4, bg);
            break;
        case 2:
            tft.fillRect(x + 0.1f*size, y, 0.8f*size, 0.5f*size + 4, bg);
            break;
        case 3:
            tft.fillRect(x + 0.1f*size, y, 0.8f*size, 0.3f*size + 4, bg);
            break;
        default:
            break;
    }
    drawDropletSkeleton(x, y, size, bg);
}