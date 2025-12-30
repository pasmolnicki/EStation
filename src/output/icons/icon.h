#pragma once 

#include <TFT_eSPI.h>

#include "../../lang/localizers/Localizer.h"
#include "../components.h"

#include "../weather.h"


namespace ui
{
  class Icon
  {
  public:
      Icon() = default;
      
      virtual void
      draw(
          int16_t x, int16_t y,
          int16_t size, uint16_t color,
          uint16_t bg
      ) {}
  };
}