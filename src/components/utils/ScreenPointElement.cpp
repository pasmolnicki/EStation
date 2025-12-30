#include "ScreenPointElement.h"

namespace ui
{
    ScreenPointElement::ScreenPointElement(
        int16_t x, int16_t y, 
        uint16_t size, uint16_t bg
    ): x(x), y(y), size(size), bg(bg) {
        HSV hsv;
        hsv.hue = 0;
        hsv.satrutaion = 0;
        std::unique_ptr<uint16_t[]> colors(create_grayscale(size, hsv));
        _colors.assign(colors.get(), colors.get() + size);
    }

    void ScreenPointElement::draw(const path& p){
        int mainIndex = 0;

        constexpr int radius = 4, spacing = 4, itr = radius*2 + spacing;

        switch(p){
            case path::HOME:
                mainIndex = 0;
                break;
            case path::TODAY_FORECAST:
                mainIndex = 1;
                break;
            case path::NEXT_FORECAST:
                mainIndex = 2;
                break;
            default:
                // If the path is unknown, return
                return;
        }

        // Get the starting x position
        int startX = x - (size - 1) * itr / 2,
            _x = startX + mainIndex*itr;

        int i = mainIndex, colorIndex = 0;

        // Draw the points to the right
        while(i < size){
            tft.fillSmoothCircle(_x, y, radius, _colors.at(colorIndex), bg);
            _x += itr;
            i++;
            colorIndex++;
        }

        // Get the starting x position
        _x = startX + (mainIndex - 1)*itr;
        colorIndex = 1;
        i = mainIndex - 1;

        // Draw the points to the left
        while(i >= 0){
            tft.fillSmoothCircle(_x, y, radius, _colors.at(colorIndex), bg);
            _x -= itr;
            i--;
            colorIndex++;
        }
    }
}