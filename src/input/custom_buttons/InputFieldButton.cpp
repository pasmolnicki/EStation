#include "InputFieldButton.h"

extern TFT_eSPI tft;

namespace ui
{
    constexpr auto offset = 5;

    InputFieldButton::InputFieldButton(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t bg,
        TextProps* props
    ): TouchButton(x, y, w, h), 
    _props(createDefaultIfNull(props)),
    _blinkOn(true) {
        this->bg = bg;
        _props->bg = color;
        _placeholder = truncateText(_props.get(), width - 4*offset);
        _props->text = "";
        _blinkX = _props->x;
        _lastBlinkTime = millis();
    }

    void InputFieldButton::draw(){
        constexpr uint16_t placeholderColor = TFT_DARKGREY;

        uint16_t x_ = _props->x;
        FontLoader fl(x_, _props.get());

        drawInputField(x, y, width, height, color, TFT_WHITE, bg);
        auto wrapped = textWrapper(_props.get(), width - 4*offset, true);

        if (wrapped.isEmpty()){
            wrapped = _placeholder;
            tft.setTextColor(placeholderColor);
            _blinkX = _props->x;
            tft.drawString(wrapped, _props->x, _props->y);
            return;
        }

        _blinkX = _props->x + tft.drawString(wrapped, _props->x, _props->y);
    }

    void InputFieldButton::setText(const String& str){
        _props->text = str;
    }

    void InputFieldButton::addText(const String& str){
        _props->text += str;
        _forceUpdate = true;
    }

    void InputFieldButton::delChar(){
        _props->text.remove(_props->text.length() - 1);
        _forceUpdate = true;
    }

    void InputFieldButton::blink(){
        constexpr auto BLINK_CACHE_TIME_MS = 400;

        if(!_forceUpdate && millis() - _lastBlinkTime < BLINK_CACHE_TIME_MS){
            return;
        }

        tft.drawFastVLine(_blinkX + 3, _props->y, height - 8, _blinkOn ? TFT_WHITE : _props->bg);
        _blinkOn = !_blinkOn;
        _forceUpdate = false;
        _lastBlinkTime = millis();
    }
}