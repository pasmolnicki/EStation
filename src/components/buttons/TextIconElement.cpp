#include "TextIconElement.h"

namespace ui
{
    TextIconElement::TextIconElement(
        uint16_t x, uint16_t y,
            uint16_t w, uint16_t h,
            uint16_t bg,  
            TextProps* text,
            IconProps* icon
    ): _btn(new TextIconButton(x, y, w, h, bg, text, icon)) {}

    void TextIconElement::
    addOnClickEvent(std::function<void(void)> event){
        _btn->addOnClickListener(event);
    }

    bool TextIconElement::
    eventListener(Point* touch){
        return _btn->check(touch->x, touch->y);
    }

    void TextIconElement::draw(){
        _btn->draw();
    }

    TextIconElement* TextIconElement::setIconProps(IconProps* props){
        _btn->setIconProps(props);
        return this;
    }

    TextIconElement* TextIconElement::setTextProps(TextProps* props){
        _btn->setTextProps(props);
        return this;
    }

    void TextIconElement::setIcon(Icon* icon){
        _btn->setIcon(icon);
    }

    void TextIconElement::setText(const String& text){
        _btn->setText(text);
    }

    void TextIconElement::clear(){
        _btn->clear();
    }
}