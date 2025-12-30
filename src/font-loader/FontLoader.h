#pragma once

#include <TFT_eSPI.h>
#include "../lang/config.h"
#include "../data_structures/Props.h"

extern bool USE_CUSTOM_FONT;

/// @brief Loads desired font. If custom font is specified and located in SPIFFS 
/// then its used as a main font, else uses deafult font.
class FontLoader
{
public:
    FontLoader(uint16_t& x, TextProps* props = nullptr, TFT_eSprite* sprite = nullptr);

    template <class T>
    void build(uint16_t& x, T* elem, TextProps* props = nullptr);

    ~FontLoader();
};

template <class T>
void FontLoader::build(uint16_t& x, T* elem, TextProps* props) {
    char* font = useFont(fonts::normal);
    uint16_t color = TFT_WHITE;
    uint16_t bg = TFT_BLACK;
    String text = "Default";
    auto placement = placement::start;

    if (props){
        font = props->font;
        text = props->text;
        placement = props->location;
        color = props->color;
        bg = props->bg;
    }

    elem->setTextColor(color, bg);

    if (elem->fontLoaded){
        elem->unloadFont();
    }
     if (USE_CUSTOM_FONT){
        elem->loadFont(font);
    }
    else{
        // Set accordingly default fonts
        
        if(font == useFont(fonts::detail) ){
            elem->setTextSize(1);
            elem->setTextFont(2);
        }
        if (font == useFont(fonts::normal)){
            elem->setTextSize(2);
            elem->setTextFont(2);
        }
        if(font == useFont(fonts::title)){
            elem->setTextSize(2);
            elem->setTextFont(4);
        }
        if (font == useFont(fonts::clock)){
            elem->setTextFont(6);
            elem->setTextSize(1);
        }
    }
    // Set text placement
    switch(placement){
        case placement::middle:
            elem->setTextDatum(TC_DATUM);
            break;
        case placement::end:
            x -= 5;
            elem->setTextDatum(TR_DATUM);
            break;
        default:
            x += 5;
            elem->setTextDatum(TL_DATUM);
    }
}