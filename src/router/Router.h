#pragma once

#include "../views/home/HomeScreen.h"
#include "../views/choose-wifi/ChooseWifi.h"
#include "../views/wifi-pass-input/PassInputScreen.h"
#include "../views/settings/SettingsScreen.h"
#include "../views/loading/LoadingScreen.h"
#include "../views/localizer/LocalizerScreen.h"
#include "../views/locations/LocationScreen.h"
#include "../views/add-location/AddLocation.h"
#include "../views/unit-system/UnitSystemScreen.h"
#include "../views/sleep/SleepScreen.h"
#include "../views/error/ErrorScreen.h"
#include "../views/today-forecast/TodayForecastScreen.h"
#include "../views/next-days-forecast/NextForecastScreen.h"
#include "../views/weather-details/WeatherDetailsScreen.h"
#include "../views/wifi-manger/WifiManagerScreen.h"

/// @brief Routes view through given path names.
/// Much like in a html page, inspired by React.
class Router
{
    bool _preloaded;
    std::unique_ptr<ui::BaseScreen> _screen;
    ui::BaseScreen* getRoute();

public:
    Router();

    /**
     * @brief Main loop for the router, wait's for the screen to finish it's job (That is to change the route).
     */
    void
    loop();

    /**
     * @brief Load current into memory screen, but does not draw it.
     */
    void 
    preload();
};