#include "IconButtonElement.h"

namespace ui
{
    IconButtonElement::IconButtonElement(
        uint16_t x,
        uint16_t y,
        IconProps* props
    ): ScreenElement(), _icon(new IconButton(x, y, props)) {}

    void IconButtonElement::draw(){
        _icon->draw();
    }

    void IconButtonElement::addOnClickEvent(std::function<void(void)> event){
        _icon->addOnClickListener(event);
    }

    bool IconButtonElement::eventListener(Point* touch){
        return _icon->check(touch->x, touch->y);
    }
    
}