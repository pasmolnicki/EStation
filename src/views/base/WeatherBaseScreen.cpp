#include "WeatherBaseScreen.h"

extern LocationProps locProps;
extern Localizer localizer;
extern String CURRENT_VER;

namespace ui
{
    // Custom setters for displaying weather data
    String maxTemperatureSetter(const Weather& data){
        return String((int)data._max_temp) + " " + localizer.getUnit(unit::temperature);
    }

    String minTemperatureSetter(const Weather& data){
        return String((int)data._min_temp) + " " + localizer.getUnit(unit::temperature);
    }

    String temperatureSetter(const Weather& data){
        return String((int)data._temp) + " " + localizer.getUnit(unit::temperature);
    }

    String feelsLikeSetter(const Weather& data){
        return getLocale()->FEELS_LIKE + " " + String((int)data._feels_like) + " " + localizer.getUnit(unit::temperature);
    }


    WeatherBaseScreen::WeatherBaseScreen():
    _lastTouch(millis()),

    _screenPoint(160, 230, 3, BASE_SCREEN_BG), 

    _ver(320, 0, new TextProps("v." + CURRENT_VER + " " + localizer.localizerName(), 
        placement::end, BASE_SCREEN_BG, useFont(fonts::detail))),

    _title(160, 4, new TextProps("", placement::middle, BASE_SCREEN_BG, useFont(fonts::detail))),

    _wifiConnection(new WifiConnectionElement(2, 4, 20, BASE_SCREEN_BG)),

    _location(new TextElement(25, 5, 
        new TextProps(locProps.location + " " + locProps.country, 
            placement::start,BASE_SCREEN_BG, useFont(fonts::detail)))),
            
    _startY(30) {}

    WeatherBaseScreen::~WeatherBaseScreen() {
        tft.fillRect(0, 25, 320, 240 - 25, _base_bg);
        _title.clear();
    }

    void WeatherBaseScreen::updateWeatherStates() {
        iterate([](DataElement<Weather>* elem){
            elem->setData(*wProvider.weather());
        });
    }

    void WeatherBaseScreen::updateStates() {
        TryLock tryLock(getSemaphore(tasks::weather), 2);
        if (tryLock){
            updateWeatherStates();
        }
        _wifiConnection->updateState();
    }

    void WeatherBaseScreen::handleTouch(Point*){
        return;
    }

    void WeatherBaseScreen::setTitle(const String& title){
        _title.setText(title);
        _title._prev = title;
    }

    void WeatherBaseScreen::draw() {
        if (previousRoute() == path::LOADING || previousRoute() == path::SLEEP){
            drawBase();
        }
        _drawItems(_items, _size);
        _screenPoint.draw(currentRoute());
        _title.draw();
    }

    void WeatherBaseScreen::drawBase() {
        _ver.draw();
        _wifiConnection->draw();
        _location->draw();
    }   

    void WeatherBaseScreen::loop() {
        TouchPoint area;
        _lastTouch = millis();

        while(!_exited) {

            std::unique_ptr<Point> touch(ts.read_touch());

            updateStates();

            if (millis() - _lastTouch > 1000 * 60 * 2 ) { 
                route(path::SLEEP);
            }

            if (!touch){
                continue;
            }

            _lastTouch = millis();

            handleTouch(touch.get());
        }
    }
}
