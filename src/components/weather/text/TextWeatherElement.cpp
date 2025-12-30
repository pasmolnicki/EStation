#include "TextWeatherElement.h"


namespace ui
{
    TextWeatherElement::TextWeatherElement(const Weather& weather,
    int16_t x, int16_t y, TextProps* props):
    WeatherElement(weather), _prev(""), _current(""), _lenght(0) {
        _size = 1;
        _items = new TextButton* [_size] {new TextButton(x, y, props)};
    }

    void TextWeatherElement::updateState(){
        if(!_redraw){
            return;
        }
        clear();
        draw();
        _redraw = false;
    }

    void TextWeatherElement::onUpdate(){
        if (_setter){
            setText(_setter(_data));
        }
    }

    void TextWeatherElement::clear(){
        uint16_t x = _items[0]->x;
        FontLoader fl(x, _items[0]->_props.get());
        auto width = tft.textWidth(_prev);
        if (_items[0]->_props->location == placement::middle){
            x -= width / 2;
        }
        else if (_items[0]->_props->location == placement::end){
            x -= width;
        }
        tft.fillRect(x, _items[0]->y, width, tft.fontHeight(), _items[0]->_props->bg);
    }

    TextWeatherElement* TextWeatherElement::setter(setter_type setter){
        _setter = setter;
        return this;
    }

    void TextWeatherElement::setText(const String& str){
        if (str == _current){
            return;
        }
        _prev = _current;
        _current = str;
        _redraw = true;

        _items[0]->setText(str);
    }

    void TextWeatherElement::drawToSprite(
        uint16_t x,
        uint16_t y, 
        TFT_eSprite* sprite
    ) {
        if (!sprite){
            return;
        }
        drawTextButton(x, y, _items[0]->_props.get(), sprite);
    }
}