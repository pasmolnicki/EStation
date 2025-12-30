#include "TextButton.h"

namespace ui
{
    TextButton::TextButton(
        uint16_t x, uint16_t y,
        TextProps* props
    ): TouchButton(x, y, 0, 0),
    _props(createDefaultIfNull(props)) {}

    TextButton::TextButton(
        const TextButton& other
    ): TouchButton(other.x, other.y, other.width, other.height) {
        (void)(*this = other);
    }

    TextButton& TextButton::operator=(const TextButton& other){
        TouchButton::operator=(other);
        _props.reset(new TextProps(*other._props));
        return *this;
    }

    TextButton* TextButton::setProps(TextProps* props){
        _props.reset(props);
        return this;
    }

    void TextButton::eraseText(){
        uint16_t color = _props->color;
        _props->color = _props->bg;
        drawTextButton(x, y, _props.get());
        _props->color = color;
    }
    
    void TextButton::draw(){
        if (_props->text.isEmpty()) return;
        drawTextButton(x, y, _props.get());
    }

    void TextButton::setText(const String& text){
        _props->text = text;
    }

    void TextButton::setWidthHeight() {
        uint16_t x = this->x;
        FontLoader fl(x, _props.get());
        this->height = tft.fontHeight();
        this->width = tft.textWidth(_props->text);
    }
}