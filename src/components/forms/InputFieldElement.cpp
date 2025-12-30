#include "InputFieldElement.h"

namespace ui
{
    InputFieldElement::InputFieldElement(
        int16_t x,
        int16_t y,
        uint16_t w,
        uint16_t h,
        uint16_t bg,
        TextProps* props
    ): DataElement<String>(""), _button(new InputFieldButton(x, y, w, h, bg, props)){
        
        constexpr auto offset_x = 5;
        _button->_props->x = x + offset_x;
        uint16_t _x = x + offset_x;
        FontLoader fl(_x, _button->_props.get());
        _button->_props->y = y + ( h - tft.fontHeight() ) * 0.5f;
    }

    void InputFieldElement::draw(){
        _button->draw();
    }

    bool InputFieldElement::eventListener(Point* touch){
        return _button->check(touch->x, touch->y);
    }

    void InputFieldElement::addOnClickEvent(std::function<void(void)> callb){
        _button->addOnClickListener(callb);
    }

    void InputFieldElement::addChar(const String& c){
        _button->addText(c);
    }

    const String& InputFieldElement::getValue(){
        return _button->_props->text;
    }

    void InputFieldElement::deleteChar(){
        _button->delChar();
    }

    void InputFieldElement::blink(){
        _button->blink();
    }
}