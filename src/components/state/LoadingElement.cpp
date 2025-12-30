#include "LoadingElement.h"

namespace ui
{
    constexpr auto updateTime = 33; // 1000/33 = 30 FPS
    constexpr auto deltaAngle = 360 / (1000 / updateTime); // In 1 sec does 360 deg. spin

    LoadingElement::LoadingElement(
        int16_t x,
        int16_t y,
        int16_t size,
        uint16_t bg
    ): PosContainer(x, y, size, size), _bg(bg), _angle(0),
    _lastUpdateTime(millis()), _isLoading(true) {}

    void LoadingElement::draw(){
        drawLoadingState(_x, _y, _bg, _width, 0);
    }

    void LoadingElement::clear(){
        tft.fillRect(_x, _y, _width, _height, _bg);
    }

    void LoadingElement::setLoading(bool loading){
        _isLoading = loading;
    }

    void LoadingElement::updateState(){
        if (!_isLoading || millis() - _lastUpdateTime < updateTime){
            return;
        }

        clearLoadingState(_x, _y, _bg, _width, _angle);
        _angle = (_angle + deltaAngle) % 360;
        drawLoadingState(_x, _y, _bg, _width, _angle);

        _lastUpdateTime = millis();
    }
}