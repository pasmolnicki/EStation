#include "IconWeatherElement.h"


namespace ui
{
    IconWeatherElement::IconWeatherElement(
        const Weather& weather,
        int16_t x, 
        int16_t y, 
        IconProps* props
    ): WeatherElement(weather) {
        _size = 1;
        _items = new IconButton* [_size] {new IconButton(x, y, props)};
    }

    void IconWeatherElement::updateState(){
        if(!_redraw){
            return;
        }
        iterate([&](IconButton* item){item->clear();});
        draw();
    }

}