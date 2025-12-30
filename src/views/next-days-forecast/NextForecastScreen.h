#pragma once

#include "../base/WeatherBaseScreen.h"

namespace ui
{

    class NextForecastScreen: public WeatherBaseScreen
    {
    public:
        NextForecastScreen();
        
        void handleTouch(Point*);

        virtual void draw();

        virtual void 
        updateWeatherStates();
    };

}