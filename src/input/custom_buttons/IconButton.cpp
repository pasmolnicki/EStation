#include "IconButton.h"


namespace ui
{
    IconButton::IconButton(
        uint16_t x, uint16_t y,
        IconProps* props
    ):  TouchButton(x, y, 0, 0), _props(createDefaultIfNull(props)) {
        this->height = _props->size;
        this->width = _props->size;
    }

    void IconButton::draw(){
        if(_props.get() && _props->icon){
            _props->icon->draw(
                x, y, _props->size, _props->color, _props->bg
            );
        }
    }

    void IconButton::setIcon(Icon* icon){
        if(!icon){
            return;
        }
        delete _props->icon;
        _props->icon = icon;
    }

    void IconButton::clear(){
        if (_props.get()){
            tft.fillRect(x, y, _props->size, _props->size, _props->bg);
        }
    }
}