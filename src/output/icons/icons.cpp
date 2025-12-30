#include "icons.h"

extern TFT_eSPI tft;

namespace ui
{

    constexpr uint16_t pseudoWhite = TFT_LIGHTGREY;

    // drawing 
    void SettingsIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
    drawCard(x, y, size, size, color, bg);

    constexpr uint16_t gear_color = pseudoWhite;

    tft.fillSmoothCircle(x+0.5f*size, y+0.5f*size, 0.3f*size, gear_color, color);

    uint16_t 
    xc = x + size/2,
    yc = y + size/2,
    Ax = 0.75f * size + x,
    Ay = y + size/2,
    Bx = 0.9f*size + x,
    By = Ay; 

    for (uint8_t i=0; i<9; i++)
    {
        float angle = i * PI/4;
        uint16_t
            ax = (Ax - xc) * cosf(angle) - (Ay - yc) * sinf(angle) + xc,
            ay = (Ax - xc) * sinf(angle) + (Ay - yc) * cosf(angle) + yc,
            bx = (Bx - xc) * cosf(angle) - (By - yc) * sinf(angle) + xc,
            by = (Bx - xc) * sinf(angle) + (By - yc) * cosf(angle) + yc;

        tft.drawWideLine(ax, ay,bx , by, 0.15f * size, gear_color, color);
    }

    tft.drawArc(x + 0.5f*size, y + 0.5f*size, 0.3f*size, 0.1f*size, 0, 360, gear_color, color, false);
    tft.fillSmoothCircle(x+0.5f*size, y+0.5f*size, 0.2f*size, color, gear_color);
    }

    void GoBackIcon::draw(
         int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawCard(x, y, size, size, color, bg);
        uint16_t _x = x, _y = y;

        _x += size*0.2f;
        _y += size*0.5f;
        tft.drawWideLine(_x, _y, x + 0.75f*size, y + 0.2f*size, 3, TFT_LIGHTGREY, color);
        tft.drawWideLine(_x, _y, x + 0.75f*size, y + 0.8f*size, 3, TFT_LIGHTGREY, color);
    }

    void GoForwardIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawCard(x, y, size, size, color, bg);
        uint16_t _x = x, _y = y;

        _x += size*0.8f;
        _y += size*0.5f;
        tft.drawWideLine(_x, _y, x + 0.25f*size, y + 0.2f*size, 3, TFT_LIGHTGREY, color);
        tft.drawWideLine(_x, _y, x + 0.25f*size, y + 0.8f*size, 3, TFT_LIGHTGREY, color);
    }
    

    void ExpandIcon::draw(
         int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawCard(x, y, size, size, color, bg);
        uint16_t _x = x, _y = y;

        _x += size*0.5f;
        _y += size*0.7f;
        tft.drawWideLine(_x, _y, x + 0.2f*size, y + 0.4f*size, 3, TFT_LIGHTGREY, color);
        tft.drawWideLine(_x, _y, x + 0.8f*size, y + 0.4f*size, 3, TFT_LIGHTGREY, color);

        // tft.drawWedgeLine(x + 0.4f*size + 1, y + 0.7f*size + 1, _x -1 , _y -1, 1, 1, TFT_LIGHTGREY, TFT_LIGHTGREY);
    }

    void CapsLockIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        constexpr auto thickness = 2;

        tft.drawWideLine(x + 0.5f*size, y, x, y + 0.5f*size, thickness, color, bg);
        tft.drawWideLine(x + 0.5f*size, y, x + size, y + 0.5f*size, thickness, color, bg);

        tft.fillRect(x, y + 0.5f*size, 0.25f*size, thickness, color);
        tft.fillRect(x + 0.75f*size, y + 0.5f*size, 0.25f*size, thickness, color);

        tft.fillRect(x + 0.25f*size, y + 0.5f*size, thickness, 0.5f*size, color);
        tft.fillRect(x + 0.75*size, y + 0.5f*size, thickness, 0.5f*size, color);

        tft.fillRect(x + 0.25f*size, y + size, 0.5f*size + thickness, thickness, color);
    }

    void DeleteIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        constexpr auto thickness = 2, redColor = 0x78E3;

        drawCard(x, y, size, size, redColor, bg);
        
        // < shape
        tft.drawWideLine(int(x + 0.1f*size), int(y + 0.5f*size), int(x + 0.4f*size), int(y + 0.25f*size), thickness, color, redColor);
        tft.drawWideLine(int(x + 0.1f*size), int(y + 0.5f*size), int(x + 0.4f*size), int(y + 0.75f*size), thickness, color, redColor);

        // rect shape
        tft.fillRect(x + 0.4f*size, y + 0.25f*size, 0.5f*size, thickness, color);
        tft.fillRect(x + 0.9f*size, y + 0.25f*size, thickness, 0.5f*size, color);
        tft.fillRect(x + 0.4f*size, y + 0.75f*size, 0.5f*size + thickness, thickness, color);

        // X
        tft.drawWideLine(int(x + 0.5f*size), int(y + 0.35f*size), int(x + 0.8f*size), int(y + 0.65f*size), thickness, color, redColor);
        tft.drawWideLine(int(x + 0.5f*size), int(y + 0.65f*size), int(x + 0.8f*size), int(y + 0.35f*size), thickness, color, redColor);

    }

    // X icon with base red fill color
    void ExitIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        constexpr auto redColor = 0x78E3;
        drawCard(x, y, size, size, redColor, bg);
        tft.drawWideLine(x + 0.2f*size, y + 0.2f*size, x + 0.8f*size, y + 0.8f*size, 2, color, redColor);
        tft.drawWideLine(x + 0.2f*size, y + 0.8f*size, x + 0.8f*size, y + 0.2f*size, 2, color, redColor);
    }

    void TrashIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        constexpr auto thickness = 2;

        if (color != bg){
            drawCard(x, y, size, size, color, bg);
        }

        int pos_y, h;
        
        // Main body
        tft.fillSmoothRoundRect(x + 0.275f*size, y + 0.25f*size, 0.45f*size, 0.5f*size, 4, pseudoWhite, color);

        // Top
        pos_y = y + 0.2f*size;
        h = 0.1f*size;
        tft.fillSmoothRoundRect(x + 0.2f*size, pos_y, 0.6f*size, 0.1f*size, 4, pseudoWhite, color);
        tft.drawFastHLine(x + 0.2f*size, pos_y + h, 0.6f*size, color);
        tft.fillSmoothRoundRect(x + 0.35f*size, pos_y - 0.08f*size + 1, 0.3f*size, 0.08f*size, 4, pseudoWhite, color);
    }

    void RefreshIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        constexpr auto lineColor = pseudoWhite;
        drawCard(x, y, size, size, color, bg);

        tft.drawSmoothArc(x + size*0.5f, y + size*0.5f, 0.4f*size, 0.4f*size - 2, 0, 330, lineColor, color, true);

        tft.drawWideLine(x + size*0.4f, y + 0.8f*size - 4, x + 0.5f*size + 1, y + 0.9f*size - 2, 2, lineColor, color);
        tft.drawWideLine(x + size*0.4f, y + size - 2, x + 0.5f*size + 1, y + 0.9f*size - 2, 2, lineColor, color);

        tft.drawWideLine(x + size*0.5f - 2, y + 0.9f*size - 2, x + 0.5f*size, y + 0.9f*size - 2, 1, lineColor, lineColor);
    }

    void WiFiStrongIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawWiFi(x, y, size, 4, bg);
    }

    void WiFiGreatIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawWiFi(x, y, size, 3, bg);
    }

    void WiFiMediumIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawWiFi(x, y, size, 2, bg);
    }

    void WiFiWeakIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawWiFi(x, y, size, 1, bg);
    }

    void WiFiLostIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawWiFi(x, y, size, 0, bg);
    }

    void LockerLocked::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawLocker(x, y, size, bg);
    }

    void LockerUnlocked::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawLocker(x, y, size, bg, true);
    }

    void DropletEmpty::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ) {
        drawDropletIcon(x, y, size, bg, 0);
    }

    void DropletSmall::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ) {
        drawDropletIcon(x, y, size, bg, 1);
    }

    void DropletMedium::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ) {
        drawDropletIcon(x, y, size, bg, 2);
    }

    void DropletHigh::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ) {
        drawDropletIcon(x, y, size, bg, 3);
    }

    void DropletFull::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ) {
        drawDropletIcon(x, y, size, bg, 4);
    }
}