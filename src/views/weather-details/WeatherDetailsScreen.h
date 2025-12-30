#pragma once

#include "../base/WeatherBaseScreen.h"

#include "../../components/chart/Chart.h"

namespace ui
{
  class WeatherDetailsScreen: public WeatherBaseScreen{
      Chart _chart;
    public:
      WeatherDetailsScreen();

      virtual void
      updateWeatherStates();

      virtual void
      draw();

      virtual void
      handleTouch(Point*);
  };
}