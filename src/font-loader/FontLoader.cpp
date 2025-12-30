#include "FontLoader.h"

extern TFT_eSPI tft;

FontLoader::FontLoader(uint16_t& x, TextProps* props, TFT_eSprite* sprite){
    if (sprite == nullptr){
        build<TFT_eSPI>(x, &tft, props);
        return;
    }
    build<TFT_eSprite>(x, sprite, props);
}

FontLoader::~FontLoader(){
    if (USE_CUSTOM_FONT && tft.fontLoaded){
        tft.unloadFont();
    }
}