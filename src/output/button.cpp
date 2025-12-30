#include "button.h"

extern TFT_eSPI tft;


void drawMenuButton(
    uint16_t x, uint16_t y,
    uint16_t w, uint16_t h,
    uint16_t color, uint16_t bg,
    TextProps* props
){
    drawCard(x, y, w, h, color, bg);

    if (props->location == placement::middle){
        x += w/2;
    }
    FontLoader fl(x, props);
    tft.drawString(props->text, x, y + (h - tft.fontHeight())/2);
}

void drawIconProps(
    IconProps* p
){
    if (!(p && p->icon)){
        return;
    }
    p->icon->draw(
        p->x, p->y, p->size, p->color, p->bg
    );
}

void drawTextButton(
    int16_t x, int16_t y,
    TextProps* props,
    TFT_eSprite* sprite
){
    uint16_t _x = x;
    FontLoader fl(_x, props, sprite);
    uint16_t h = tft.fontHeight();

    x = _x;

    

    // Support for default text render (which doesn't detect new lines in text '\n')
    const String _txt = props->text;
    std::vector<String> _lines;
    int prev = 0;
    for (int i = 1; i < _txt.length(); i++){
        if (_txt[i] == '\n'){
            _lines.push_back(_txt.substring(prev, i));
            prev = i + 1;
        }
    }
    _lines.push_back(_txt.substring(prev, _txt.length()));
    const int _size = _lines.size();
    int16_t _y = y;
    for (int i = 0; i < _size; i++){
        if (!sprite){
            tft.drawString(_lines[i], x, _y);
        }
        else{
            sprite->drawString(_lines[i], x, _y);
        }        
        _y += h;
    }
    if (sprite && sprite->fontLoaded){
        sprite->unloadFont();
    }
}