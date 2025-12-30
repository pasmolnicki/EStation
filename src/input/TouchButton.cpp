#include "TouchButton.h"

extern TFT_eSPI tft;

void do_nothing_button(){
    return;
}

TouchButton::
TouchButton(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height
)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = DEFAULT_BTN_COLOR;
    this->bg = 0x0042;
    this->addOnClickListener(do_nothing_button);
}

TouchButton::
TouchButton(
    const TouchButton& other
){
    (void)(*this = other);
}

TouchButton* TouchButton::
addOnClickListener(std::function<void(void)> on_press){
    this->on_press = on_press;
    return this;
}

bool TouchButton::
check(
    int16_t x, 
    int16_t y
)
{
    if( (x >= this->x) && (x <= this->x + width)){
        if ((y >= this->y) && (y <= this->y + height)){
            on_touch();

            if (this->on_press){
                this->on_press();
            }
            return true;
        }
    }
    return false;
}

void TouchButton::on_touch(){
    return;
}

void TouchButton::draw(){
    return;
}

void TouchButton::clear(){
    tft.fillRect(x, y, width, height, bg);
}

TouchButton& TouchButton::
operator=(const TouchButton& other){
    this->x = other.x;
    this->y = other.y;
    this->width = other.width;
    this->height = other.height;
    this->color = other.color;
    this->bg = other.bg;
    return *this;
}