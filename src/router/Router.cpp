#include "Router.h"

extern ErrorProvider errorProvider;

Router::Router() {
    _preloaded = false;
}

void Router::preload(){
    _preloaded = true;
    _screen.reset(getRoute());
    _screen->preload();
}

void Router::loop(){
    if (!_preloaded){
        _screen.reset(getRoute());
    } else {
        _preloaded = false;
    }
    
    try{
        _screen->draw();
        _screen->loop();
    }
    catch(const std::exception& e){
        Lock l(getSemaphore(tasks::error));
        changeRoute(ui::path::ERROR);
        errorProvider.reason(e.what());
        errorProvider.code(__FILE__);
        errorProvider.log();
    }
}

ui::BaseScreen* Router::getRoute(){
    using namespace ui;
    switch (currentRoute())
    {
    case path::INPUT_PASS:
        return new PassInputScreen();
    case path::CHOOSE_WIFI:
        return new ChooseWifiScreen();
    case path::SETTINGS:
        return new SettingsScreen();
    case path::LOADING:
        return new LoadingScreen();
    case path::LOCALE:
        return new LocalizerScreen();
    case path::LOCALIZATION:
        return new LocationScreen();
    case path::ADD_LOCATION:
        return new AddLocation();
    case path::SET_UNIT_SYTEM:
        return new UnitSystemScreen();
    case path::SLEEP:
        return new SleepScreen();
    case path::ERROR:
        return new ErrorScreen();
    case path::TODAY_FORECAST:
        return new TodayForecastScreen();
    case path::NEXT_FORECAST:
        return new NextForecastScreen();
    case path::WEATHER_DETAILS:
        return new WeatherDetailsScreen();
    // case path::MANAGE_NETWORKS:
    //     return new WifiManagerScreen();
    default:
        return new HomeScreen();
    }
}