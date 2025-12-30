#include "SleepElement.h"

extern DateTimeProvider dateProvider;
extern WeatherProvider wProvider;
extern Localizer localizer;

namespace ui
{
    constexpr int xOffset = 80, yOffset = 40;

    void _clockUpdate(SleepElement* object){
        TryLock lock(getSemaphore(tasks::clock), 1);
        if (lock){
            object->setText(dateProvider.formatTime("%R"));
            if (object->_redraw){
                object->updateSprite();
            }
        }
    }

    SleepElement::SleepElement(uint16_t bg): 
        TextWeatherElement(
            Weather(), 160 - 123 / 2, 60, 
            new TextProps("", placement::start, bg, useFont(fonts::clock))
        ), 
        _tickCount(0), _freqUpdate(true), _text_index(_TextIndex::CLOCK),
        _lastUpdate(millis()), _sprite(&tft), _bg(bg), _spriteUpdater(_clockUpdate)
    {
        _pos.x = this->_items[0]->x;
        _pos.y = this->_items[0]->y;

        _pos.Vx = 6;
        _pos.Vy = 6;

        _pos.prevX = _pos.x;
        _pos.prevY = _pos.y;
        
        uint16_t x;
        FontLoader fl(x, this->_items[0]->_props.get());
        _setClock();
        _pos.h = tft.fontHeight();

        _sprite.createSprite(_pos.w, _pos.h);
        updateSprite();
        // Serial.printf("w: %d h: %d \n", _pos.w, _pos.h);
    }

    SleepElement::~SleepElement(){
        tft.fillRect(_pos.x, _pos.y, _pos.w, _pos.h, _bg);
    }

    void SleepElement::_setClock(){
        // Simple current time clock, showing current hour:minutes
        Lock lock(getSemaphore(tasks::clock));
        String text = dateProvider.formatTime("%R");
        _pos.w = tft.textWidth(text) + 8;
        _items[0]->setText(text);
    }

    void SleepElement::_setTemperature(){
        // Temperature 
        TryLock lock(getSemaphore(tasks::weather), 5);
        if (lock){
            _data = *wProvider.weather();
        }
        String text((int)_data._temp);
        text += " " + localizer.getUnit(unit::temperature);
        _pos.w = tft.textWidth(text) + 8;
        _items[0]->setText(text);
    }

    void SleepElement::_updateIndex(){
        int index = static_cast<int>(_text_index);
        index++;
        index = index % 2;
        _text_index = _TextIndex(index);

        // clear previous sprite and delete it
        tft.fillRect(_pos.x, _pos.y, _pos.w, _pos.h, _bg);

        _sprite.deleteSprite();

        _freqUpdate = false;

        uint16_t x;
        switch(_text_index){
            case _TextIndex::CLOCK: {
                _items[0]->_props->font = useFont(fonts::clock);
                FontLoader fl(x, _items[0]->_props.get());
                _setClock();
                _freqUpdate = true;
            }
                break;
            default: {
                _items[0]->_props->font = useFont(fonts::title);
                FontLoader fl(x, _items[0]->_props.get());
                _setTemperature();
            }
        }
        _sprite.createSprite(_pos.w, _pos.h);
        updateSprite();

        if (_pos.x + _pos.w >= 320){
            _pos.x = 320 - _pos.w;
        }
        if (_pos.y + _pos.h >= 240){
            _pos.y = 240 - _pos.h;
        }
    }

    void SleepElement::move(){
        _pos.prevX = _pos.x;
        _pos.prevY = _pos.y;

        // Serial.printf("x: %d y: %d \n", _pos.x, _pos.y);

        _pos.x += _pos.Vx;
        _pos.y += _pos.Vy;

        if (_pos.x + _pos.w  >= 320 || _pos.x  <= 0){
            _pos.Vx = -_pos.Vx;
        }
        if (_pos.y + _pos.h  >= 240 || _pos.y  <= 0){
            _pos.Vy = -_pos.Vy;
        }
    }

    void SleepElement::draw(){
        _sprite.pushSprite(_pos.x, _pos.y);
    }


    void SleepElement::updateSprite(){
        _sprite.fillSprite(_bg);
        drawToSprite(0, 0, &_sprite);
    }

    void SleepElement::updateState(){
        // All in ms
        constexpr int updatePeriod = 30, changeTime = 10*1000, changeTicks = changeTime / updatePeriod;

        // 33 FPS
        if (millis() - _lastUpdate < updatePeriod){
            return;
        }
        _tickCount++;

        if (_tickCount > changeTicks){
            _tickCount = 0;
            _updateIndex();
        } else{
            if (_freqUpdate){
                _spriteUpdater(this);
            }
        }

        move();

        // Check if the position has changed unpredictably
        if (_pos.prevX + _pos.Vx != _pos.x || _pos.prevY + _pos.Vy != _pos.y){
            tft.fillRect(_pos.prevX, _pos.prevY, _pos.w, _pos.h, _bg);
        } else{
            /*
            The position of the sprite is:
            x = x + Vx
            y = y + Vy

            prevX = x - Vx, where x is the current x
            prevY = y - Vy

            So then, the delta recangles are:

                 X < 0      X > 0
                ####    |     ####
                ####//  |   //####
                ####//  |   //####  Y < 0
                ####//  |   //####
                 /////  |   /////
                ------------------> x
                 /////  |   /////
                ####//  |   //####
                ####//  |   //####  Y > 0
                ####//  |   //####
                ####    |     ####
                        Y
            The delta rectangles are the `/`.
            We can just earase them instead of clearing whole spirte
            at the previous position


            The `upper` rectangle is the `/////`,
            while `lower` is:
                //
                //
                //

            */
            // All we have to do is erase the delta rectangles

            int upperX, upperY, lowerX, lowerY,
                upperW, upperH, lowerW, lowerH;

            
            upperW = _pos.w;
            upperH = abs(_pos.Vy);

            lowerW = abs(_pos.Vx);
            lowerH = _pos.h - abs(_pos.Vy);

            upperX = _pos.prevX;
            upperY = _pos.prevY;

            lowerX = _pos.prevX;
            lowerY = _pos.prevY;

            if (_pos.Vy > 0){
                lowerY = _pos.prevY + _pos.Vy;
            }
            else{
                upperY = _pos.prevY + lowerH;
            }

            if (_pos.Vx > 0){
                lowerX = _pos.prevX;
            }
            else{
                lowerX = _pos.prevX + _pos.w + _pos.Vx;
            }

            tft.fillRect(upperX, upperY, upperW, upperH, _bg);
            tft.fillRect(lowerX, lowerY, lowerW, lowerH, _bg);

        }
        draw();
        _lastUpdate = millis();
    }
}