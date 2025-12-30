#include "NextForecastScreen.h"

extern Localizer localizer;

namespace ui
{
  constexpr int weatherItems = 4;

  void stateUpdaterNextForecastScreen(DataElement<Weather>* e, int i){
    e->setData(wProvider.getAnalizedForecast()->at(i / weatherItems));
    e->updateState();
}

  NextForecastScreen::NextForecastScreen()
  {
    Lock lock(getSemaphore(tasks::weather));

    setTitle(getLocale()->NEXT_3_DAYS);

    wProvider.analizeForecast();

    constexpr int iconSize = 90, offset = (320 - 3 * iconSize) / 4, buttonSize = 40, startX = offset;

    _size = 3 * weatherItems;
    _items = new DataElement<Weather>*[_size];

    _base_size = 3;
    _base_items = new ScreenElement*[_base_size];

    for (int r = 0; r < 3; r++){

        int xOffset = r*(iconSize + offset);

        auto weather = wProvider.getAnalizedForecast()->at(r);

        _items [r*weatherItems] = new WeatherDisplayElement(weather,
            startX + xOffset, _startY, 
                new IconProps(nullptr, iconSize, _base_bg)
        );

        _items[r*weatherItems + 1] = new TimeElement(weather,
            startX + iconSize / 2 + xOffset, _startY + iconSize, 
                new TextProps("", placement::middle, _base_bg),
            date_format::weekday_short
        );

        // Max temperature, with custom setter
        _items[r*weatherItems + 2] = (new TextWeatherElement(weather,
            startX + iconSize / 2 + xOffset, _startY + iconSize + 30, 
                new TextProps("", placement::middle, _base_bg, useFont(fonts::detail))
        ))->setter(maxTemperatureSetter);

        // Min temperature, with custom setter
        _items[r*weatherItems + 3] = (new TextWeatherElement(weather,
            startX + iconSize / 2 + xOffset, _startY + iconSize + 44, 
                new TextProps("", placement::middle, _base_bg, useFont(fonts::detail))
        ))->setter(minTemperatureSetter);

        _base_items[r] = new IconButtonElement(
            startX + iconSize / 2 + xOffset - buttonSize / 2,
            _startY + iconSize + 62, 
            new IconProps(new ExpandIcon(), buttonSize, _base_bg, DEFAULT_BTN_COLOR)
        );
        }
    }

    void NextForecastScreen::draw() {
        WeatherBaseScreen::draw();
        BaseScreen::draw();
    }

    void NextForecastScreen::updateWeatherStates() {
        forEach(stateUpdaterNextForecastScreen);
    }

    void NextForecastScreen::handleTouch(Point* p) {
        
        bool expanded = false;
        // Check if expand button was pressed
        BaseScreen::forEach([p, &expanded](ScreenElement* e, int i){
            if(e->eventListener(p)){
                getScreenData().detailScreenWeatherIndex = i;
                expanded = true;
            }
        });

        if (expanded){
            route(path::WEATHER_DETAILS);
            return;
        }

        auto area = TouchScreen::toArea(p);

        switch (area){
            case TouchPoint::left:
                route(path::TODAY_FORECAST);
                return;        
            case TouchPoint::right:
                route(path::HOME);
                return;    
            default:
                break;
        }
    }
} // namespace ui