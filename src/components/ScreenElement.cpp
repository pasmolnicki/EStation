#include "ScreenElement.h"

namespace ui
{
    ScreenElement::ScreenElement() : 
    _exited(false), _size(0), 
    _buttons(nullptr), _redraw(true), _mounted(true) {}

    ScreenElement::~ScreenElement(){
        _deleteItems(_buttons, _size);
    }

    void ScreenElement::
    draw(){
        if (!_buttons){
            return;
        }
        iterate(_drawItem<TouchButton>);
        _redraw = false;
    }

    bool ScreenElement::
    eventListener(Point *touch){
        bool touched = false;
        if (_buttons){
            iterate([touch, &touched](TouchButton* btn){touched = touched || btn->check(touch->x, touch->y);});
        }
        return touched;
    }

    void ScreenElement::iterate(
        iterate_cb call
    ){
        _iterateItems(_buttons, _size, call);
    }

    void ScreenElement::onUpdate(){
        return;
    }

    void ScreenElement::updateState(){
        if (!_redraw){
            return;
        }
        draw();
        _redraw = false;
    }

    ScreenElement& ScreenElement::operator=(const ScreenElement& other){
        _exited = other._exited;
        _mounted = other._mounted;
        _redraw = other._redraw;
        return *this;
    }
} // namespace ui
