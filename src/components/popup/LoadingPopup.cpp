#include "LoadingPopup.h"

namespace ui
{
    bool doNothing(uint32_t){
        return false;
    }

    LoadingPopup::LoadingPopup(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t bg
    ): PosContainer(x, y, w, h), _bg(bg), 
    _loading(new LoadingElement(x + w / 2 - 15, y + h / 2 - 15, 30, popupColor)),
    _condition(doNothing) {
        _loading->setLoading(true);
    }

    void LoadingPopup::draw(){
        drawCard(_x, _y, _width, _height, popupColor, _bg);
        _loading->draw();
        ScreenElement::draw();
    }

    void LoadingPopup::clear(){
        tft.fillRect(_x, _y, _width, _height, _bg);
    }

    void LoadingPopup::updateState(){
        _loading->updateState();
    }

    LoadingPopup* LoadingPopup::addButton(TouchButton* btn){
        TouchButton** ptr = new TouchButton*[_size + 1];
        ptr[_size] = btn;
        
        btn->x = btn->x % _width + _x;
        btn->y = btn->y % _height + _y;

        if (!_size){
            _buttons = ptr;
            _size ++;
            return this;
        }

        int i = 0;
        for (int i = 0; i < _size; i++){
            ptr[i] = _buttons[i];
        }
        delete [] _buttons;
        _buttons = ptr;
        _size++;
        return this;
    }

    void LoadingPopup::
    setLoopConidition(loop_condition_t condition){
        _condition = condition;
    }

    void LoadingPopup::loop(){
        draw();
        uint32_t start = millis();
        while (_condition(millis() - start)){
            _loading->updateState();
        }
        clear();
    }
}