#pragma once

#include "../base/WeatherBaseScreen.h"

namespace ui
{
    class TodayForecastScreen: public WeatherBaseScreen
    {
    public:
        TodayForecastScreen();
        
        void handleTouch(Point*);

        virtual void 
        updateWeatherStates();
    };
}