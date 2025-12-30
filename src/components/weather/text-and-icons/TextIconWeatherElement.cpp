#include "TextIconWeatherElement.h"

namespace ui
{
    TextIconWeatherElement::TextIconWeatherElement(
        const Weather& init,
        int16_t x,
        int16_t y,
        IconProps* icon,
        TextProps* Props
    ): TextWeatherElement(init, x, y, Props) {
        icon = createDefaultIfNull(icon);
        _icon.reset(new IconButton(x, y, icon));
        this->init();
    }

    void TextIconWeatherElement::init(){
        
        int text_height, text_width, total_width;
        {
            uint16_t _x = 5;
            FontLoader fl(_x, _items[0]->_props.get());
            text_height = tft.fontHeight();
            text_width = tft.textWidth(_items[0]->_props->text);
            total_width = _icon->_props->size + 5 + text_width;
        }

        // The text placement is determining the position of the whole element
        if (placement::start == _items[0]->_props->location){
            // Just move the text to the right by icon's size + padding
            _items[0]->x = _icon->x + _icon->_props->size + 5;
        }
        else if (placement::middle == _items[0]->_props->location){
            _icon->x -= total_width * 0.5f;
            // The element is centered around the given x,y, plus the text has centered placement,
            // so we need to move the icon to the left by half of the element's width and
            // move the text to the right by icon's size + padding + half of the text's width (to center it)
            _items[0]->x = _icon->x + _icon->_props->size + 5 + text_width * 0.5f;
        }
        else if (placement::end == _items[0]->_props->location){
            // Just move the icon to the left, string will be drawn properly anyway
            _icon->x -= total_width;
        }
        _items[0]->y += (_icon->_props->size - text_height)/2;
    }   

    void TextIconWeatherElement::draw(){
        WeatherElement::draw();
        _icon->draw();
        _redraw = false;
    }
}