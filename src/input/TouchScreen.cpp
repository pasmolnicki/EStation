#include "TouchScreen.h"

extern TFT_eSPI tft;

uint16_t calData[5] = { 387, 3491, 258, 3495, 1 };
TouchScreen ts = TouchScreen(&tft, calData);

void do_nothing(){
    return;
}


TouchScreen::TouchScreen(
    TFT_eSPI* tft, 
    uint16_t* data
)
{
    this->tft = tft;
    tft->setTouch(data);
    max_interval = 20;
    _state = false;
    _lastState = false;
    _lastDebounceTime = 0;
    isAsleep = false;


    this->on_down(do_nothing);
    this->on_left(do_nothing);
    this->on_right(do_nothing);
    this->on_up(do_nothing);
    this->on_sleep(do_nothing);
    this->on_wakeup(do_nothing);
}

TouchPoint TouchScreen::toArea(Point* point){
    TouchPoint touch = TouchPoint::null;
    // dividing screen to 4 triangles
    if (point->y > 0.75f*point->x){
        if ( point->y < -0.75f*point->x + 240){
            touch = TouchPoint::left;
        }
        else{
            touch = TouchPoint::down;
        }
    }
    else{
        if ( point->y < -0.75f*point->x + 240){
            touch = TouchPoint::up;
        }
        else{
            touch = TouchPoint::right;
        }
    }
    return touch;
}

TouchPoint 
TouchScreen::read()
{
    uint16_t x=0,y=0;
    bool state = tft->getTouch(&x,&y);
    TouchPoint touch = TouchPoint::null;

    if (_state!=state){
        _state=state;

        // if this is an realse, then igonre
        if (!state){
            _lastState = state;
            return touch;
        }

        Point p(x, y);
        void (*area_functions[4])() = {
            // Do not change 
            _on_left,
            _on_right,
            _on_up,
            _on_down
        };

        int area = (int)toArea(&p) - 1;
        touch = (TouchPoint)(area + 1);
        if (area >= 0 && area < 4){
            area_functions[area]();
        }
    }
    _lastState = state;

    return touch;
}

Point* 
TouchScreen::read_touch()
{
    uint16_t x=0,y=0;
    bool state = tft->getTouch(&x,&y);
    

    if (_state!=state){
        _state=state;

        // if this is an realse, then igonre
        if (!state){
            _lastState = state;
            return 0;
        }

        return new Point(x,y);
    }
    _lastState = state;
    return nullptr;
}

TouchScreen* 
TouchScreen::on_left(
    void(*left)(void)
)
{
    this->_on_left = left;
    return this;
}

TouchScreen* 
TouchScreen::on_right(
    void(*right)(void)
)
{
    this->_on_right = right;
    return this;
}

TouchScreen* 
TouchScreen::on_down(
    void(*down)(void)
)
{
    this->_on_down = down;
    return this;
}

TouchScreen* 
TouchScreen::on_up(
    void(*up)(void)
)
{
    this->_on_up = up;
    return this;
}

TouchScreen* 
TouchScreen::on_sleep(
    void(*sleep)()
)
{
    this->_on_sleep = sleep;
    return this;
}

TouchScreen* 
TouchScreen::on_wakeup(
    void(*wake_up)()
)
{
    this->_on_wakeup = wake_up;
    return this;
}