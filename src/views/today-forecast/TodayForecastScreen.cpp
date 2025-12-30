#include "TodayForecastScreen.h"

namespace ui
{
    constexpr int weatherItems = 4;

    void stateUpdaterTodayForecastScreen(DataElement<Weather>* e, int i){
        e->setData(wProvider.getTodayForecast()->at(i / weatherItems));
        e->updateState();
    }

    TodayForecastScreen::TodayForecastScreen()
    {
        Lock lock(getSemaphore(tasks::weather));
        constexpr int iconSize = 90, offset = (320 - 3 * iconSize) / 4,
                      startX = offset;

        setTitle(getLocale()->TODAY);

        _size = 3 * weatherItems;
        _items = new DataElement<Weather>*[_size];

        for (int r = 0; r < 3; r++){

            int xOffset = r*(iconSize + offset);

            auto weather = wProvider.getTodayForecast()->at(r);

            _items [r*weatherItems] = new WeatherDisplayElement(weather,
                startX + xOffset, _startY, 
                    new IconProps(nullptr, iconSize, BASE_SCREEN_BG)
            );

            _items[r*weatherItems + 1] = new TimeElement(weather,
                startX + iconSize / 2 + xOffset, _startY + iconSize, 
                    new TextProps("", placement::middle, BASE_SCREEN_BG)
            );

            _items[r*weatherItems + 2] = (new TextWeatherElement(weather,
                startX + iconSize / 2 + xOffset, _startY + iconSize + 30, 
                    new TextProps("", placement::middle, BASE_SCREEN_BG)
            ))->setter(temperatureSetter);

            _items[r*weatherItems + 3] = new DropletElement(weather,
                startX + iconSize / 2 + xOffset, _startY + iconSize + 65, BASE_SCREEN_BG,
                    new TextProps("100 %", placement::middle, BASE_SCREEN_BG)
            );
        }
        updateWeatherStates();
    }

    void TodayForecastScreen::updateWeatherStates() {
        forEach(stateUpdaterTodayForecastScreen);
    }

    void TodayForecastScreen::handleTouch(Point* p) {
        auto area = TouchScreen::toArea(p);
        switch (area){
            case TouchPoint::left:
                route(path::HOME);
                return;        
            case TouchPoint::right:
                route(path::NEXT_FORECAST);
                return;    
            default:
                break;
        }
    }
}