#include "flags.h"

extern TFT_eSPI tft;

namespace ui
{


  /*
  ========================================
  #       HERE YOU CAN ADD NEW FLAGS      #
  ========================================
  
  Follow the instructions in flags.h to add new flags.

  In `iconFlagMatcher` function add a new case for the flag you want to add.
  The same way as the examples below.

  If everything is done correctly, the new flag will be displayed in the
  `Choose language` screen.
  */
  Icon* iconFlagMatcher(const locales& locale){
    switch (locale)
    {
    case locales::pl:
        return new FlagIconPL();
    default:
        return new FlagIconEN();
    }
  }

  // Argument `color` is not used flag icons
  void
  FlagIconPL::draw(
    int16_t x, int16_t y,
    int16_t size, uint16_t color,
    uint16_t bg
  ){
    y += size*0.1;
    uint16_t height = 0.8*size;
    tft.fillSmoothRoundRect(x, y, size, height, 3, TFT_WHITE, bg);
    tft.fillSmoothRoundRect(x, y + height/2 + 1, size, height/2, 3, TFT_RED, bg);
    tft.fillRect(x, y + height/2, size, height*0.3, TFT_RED);
  }

  void FlagIconEN::draw(
    int16_t x, int16_t y,
    int16_t size, uint16_t color,
    uint16_t bg
  ){
    y += size*0.1;
    uint16_t height = 4*size/5, width = size/2;
    
    TFT_eSprite sprite(&tft);
    sprite.createSprite(size, height);
    
    uint8_t line_width = height/8 - 1;
    uint8_t diff = size/20;
    sprite.fillSprite(0x00CC);

    sprite.drawWideLine(0, 0, size, height, line_width, TFT_WHITE, 0x00CC);
    sprite.drawWideLine(0, 0, size, height, line_width - diff, TFT_WHITE, TFT_RED);

    sprite.drawWideLine(size, 0, 0, height, line_width, TFT_WHITE, 0x00CC);
    sprite.drawWideLine(size, 0, 0, height, line_width - diff, TFT_WHITE, TFT_RED);

    sprite.fillRect(0, height/2 - line_width - diff, size, 2*(line_width + diff), TFT_WHITE);
    sprite.fillRect(width - line_width - diff, 0, 2*(line_width + diff), height, TFT_WHITE);

    sprite.fillRect(0, height/2 - line_width, size, 2*(line_width), TFT_RED);
    sprite.fillRect(width - line_width, 0, 2*(line_width), height, TFT_RED);

    sprite.pushSprite(x, y);
  }
}