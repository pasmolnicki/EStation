#pragma once

#include "../base/WeatherBaseScreen.h"

namespace ui
{

    class HomeScreen : public WeatherBaseScreen
    {
    public:
        HomeScreen();

        virtual void 
        updateStates();

        virtual void
        handleTouch(Point*);
    };

}