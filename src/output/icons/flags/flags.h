#pragma once

#include "../icon.h"

/*

======================================================
#         FOLLOW THE INSTRUCTIONS BELOW            #
#             TO ADD THE FLAGS ICONS               #
======================================================

!!!!!!!!!! DISCLAIMER: !!!!!!!!!!!
First, you need to add a new locale before adding a new flag icon.
If you haven't already, follow the instructions in the `lang-models` folder,
Localizer.h file. Only then you can add a new flag icon.


1. Create a new class for each flag icon you want to add,
in the same way as the examples below.

2. Implement the draw method for each class you created, in
.cpp file. 

3. Add the flag icon matcher function to the icons.cpp file.

That's it! You have successfully added a new flag icon.

*/


namespace ui
{
  // Icon matcher
  Icon* iconFlagMatcher(const locales&);

  // flags
  class FlagIconPL : public Icon
  {
    public:
      void
      draw(
          int16_t x, int16_t y,
          int16_t size, uint16_t color,
          uint16_t bg
      );
  };

  class FlagIconEN : public Icon
  {
    public:
      void
      draw(
          int16_t x, int16_t y,
          int16_t size, uint16_t color,
          uint16_t bg
      );
  };
}