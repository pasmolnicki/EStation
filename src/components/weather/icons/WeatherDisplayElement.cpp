#include "WeatherDisplayElement.h"

namespace ui
{
    WeatherDisplayElement::WeatherDisplayElement(
        const Weather& weather,
            int16_t x,
            int16_t y,
            IconProps* Props
    ): IconWeatherElement(weather, x, y, Props), _day(true), _icon(69) {
        onUpdate();
    }

    void WeatherDisplayElement::onUpdate(){

        bool day = _data._icon[2] == 'd';
        uint8_t int_icon = (_data._icon[0] - '0')*10 + (_data._icon[1] - '0');

        this->_redraw = !(this->_icon == int_icon && this->_day == day);
        this->_day = day;
        this->_icon = int_icon;

        if (_redraw){
            _items[0]->setIcon(weatherIconMatcher());
        }        
    }

    Icon* WeatherDisplayElement::weatherIconMatcher(){
        switch (_icon)
        {
            case 1:
                if (this->_day){
                    return new SunIcon(); // 01d
                }
                return new MoonIcon(); // 01n
            case 2:
                if (this->_day){
                    return new FewCloudsDayIcon();  // 02d
                }
                return new FewCloudsNightIcon();  // 02n
            case 3:
                if(this->_day){
                    return new CloudsDayIcon();  // 03d
                }
                return new CloudsNightIcon();  // 03n
            case 4:
                return new ManyCloudsIcon();  // 4d/n
            case 9:
                return new RainIcon();  // 9 d/n
            case 10:
                return new BigRainIcon(); // 10 d/n 
            case 11:
                return new StormIcon(); // 11 d/n
            case 13:
                return new SnowIcon();  // 13 d/n
            default:
                if(this->_day)
                {
                    return new MistDayIcon(); 
                }
                return new MistNightIcon(); 
        }
    }
}