#include "TextElement.h"

namespace ui
{
    TextElement::TextElement(
        int16_t x,
        int16_t y,
        TextProps* props
    ): _text(new TextButton(x, y, props)) {
        _prev = _text->_props->text;
    }

    TextElement::TextElement(
        const TextElement& other
    ): _text(new TextButton(*other._text)) {
        _prev = _text->_props->text;
    }

    TextElement& TextElement::operator=(const TextElement& other){
        _text.reset(new TextButton(*other._text));
        _prev = _text->_props->text;
        return *this;
    }

    void TextElement::draw(){
        _text->draw();
    }
    
    void TextElement::
    setProps(TextProps* props){
        _text->setProps(props);
        _redraw = true;
    }

    void TextElement::
    setText(const String& text){
        _prev = _text->_props->text;
        _text->setText(text);
        _redraw = true;
    }

    void TextElement::updateState(){
        if (!_redraw){
            return;
        }
        clear();
        draw();
        _redraw = false;
    }

    void TextElement::clear(){
        uint16_t x = _text->x;
        FontLoader fl(x, _text->_props.get());
        auto width = tft.textWidth(_prev);
        if (_text->_props->location == placement::middle){
            x -= width / 2;
        }
        tft.fillRect(x, _text->y, width, tft.fontHeight(), _text->_props->bg);
    }
}