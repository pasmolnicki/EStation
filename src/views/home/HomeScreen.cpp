#include "HomeScreen.h"

extern ErrorProvider errorProvider;

extern LocationProps locProps;
extern Localizer localizer;
extern String CURRENT_VER;



namespace ui
{
    constexpr int CLOCK_INDEX = 0, DATE_INDEX = 1;

    HomeScreen::HomeScreen() {
        Lock lock(getSemaphore(tasks::weather));
        Lock clockLock(getSemaphore(tasks::clock));

        _size = 7;
        _items = new DataElement<Weather>* [_size] {
            new ClockElement(*wProvider.weather(), 60, BASE_SCREEN_BG),
            new DateElement(*wProvider.weather(), 160, 20, new TextProps("", placement::middle, BASE_SCREEN_BG, useFont(fonts::normal))),

            (new TextWeatherElement(*wProvider.weather(), 30, 107, new TextProps("", placement::start, BASE_SCREEN_BG, useFont(fonts::title))))
            ->setter(temperatureSetter),
            (new TextWeatherElement(*wProvider.weather(), 30, 158, new TextProps("", placement::start, BASE_SCREEN_BG, useFont(fonts::detail))))
            ->setter(feelsLikeSetter),
            new SunriseElement(*wProvider.weather(), 30, 180, BASE_SCREEN_BG, new TextProps("", placement::start, BASE_SCREEN_BG, useFont(fonts::detail))),
            new SunsetElement(*wProvider.weather(), 30, 210, BASE_SCREEN_BG, new TextProps("", placement::start, BASE_SCREEN_BG, useFont(fonts::detail))),

            new WeatherDisplayElement(*wProvider.weather(), 185, 110, new IconProps(nullptr, 125, BASE_SCREEN_BG)),
        };
        
        for(int i = 0; i < _size; i++){
            _items[i]->onUpdate();
        }
    }

    void updateItemState(DataElement<Weather>* elem) {
        elem->setData(*wProvider.weather());
        elem->updateState();
    }

    void HomeScreen::updateStates() {
        _wifiConnection->updateState();
        TryLock tryLock(getSemaphore(tasks::clock), 2);
        if (tryLock){
            _items[DATE_INDEX]->updateState();
            _items[CLOCK_INDEX]->updateState();
        }
        TryLock weather(getSemaphore(tasks::weather), 2);
        if (weather){
            iterate(updateItemState);
        }
    }

    void HomeScreen::handleTouch(Point* p) {
        auto area = TouchScreen::toArea(p);
        switch (area){
            case TouchPoint::right:
                route(path::TODAY_FORECAST);
                break;
            case TouchPoint::left:
                route(path::NEXT_FORECAST);
                break;
            default:
                break;
        }
    }
}