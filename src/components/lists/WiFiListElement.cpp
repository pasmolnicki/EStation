#include "WiFiListElement.h"

namespace ui
{
    void doNothing(const WifiInfo&){
        return;
    }

    WiFiListElement::WiFiListElement(
        std::vector<WifiInfo>* init,
        uint16_t x,
        uint16_t y,
        uint16_t w,
        uint16_t h,
        uint16_t bg,
        TextProps* props
    ): DataElement<std::vector<WifiInfo>*>(init), 
    PosContainer(x, y, w, h),
    _bg(bg), _props(createDefaultIfNull(props)),
    _onClickEvent(doNothing) {
        
        _props->location = placement::start;
        uint16_t _y = y;
        FontLoader fl(_y, props);
        _btnHeight = tft.fontHeight() + 4;
        if (init){
            setData(init);
            onUpdate();
        }  
    }

    void WiFiListElement::iterate(std::function<void(WiFiBtnElement*)> callb){
        for (auto it = _btns.begin(); it != _btns.end(); it++){
            callb(&(*it));
        }
    }

    void WiFiListElement::onUpdate(){
        constexpr int PADDING_BOTTOM = 10;

        _btns.clear();
        _redraw = true;
        int _btnSize = (_y + _height) / (_btnHeight + PADDING_BOTTOM);

        _btnSize = std::min<int>(_btnSize, _data->size());

        if (!_btnSize){
            return;
        }

        uint16_t y = _y;
        for (int i=0; i < _btnSize; i++){
            _btns.emplace_back(
                _data->at(i), _x, y, _width, _btnHeight, _bg, new TextProps(*_props)
            );
            y += _btnHeight + PADDING_BOTTOM;
        }
        
    }

    bool WiFiListElement::isUpdated(){
        return _redraw;
    }


    void WiFiListElement::updateState(){
        if(!_redraw){
            return;
        }
        draw();
        _redraw = false;
    }

    void WiFiListElement::draw(){
        iterate([](WiFiBtnElement* elem){elem->draw();});
    }

    bool WiFiListElement::eventListener(Point* touch){
        auto ret = false;
        iterate([&](WiFiBtnElement* elem){
            if(elem->check(touch)){
                _onClickEvent(elem->getData());
                ret = true;
            }
        });
        return ret;
    }

    void WiFiListElement::setOnClickEvent(std::function<void(const WifiInfo&)> event){
        _onClickEvent = event;
    }
}