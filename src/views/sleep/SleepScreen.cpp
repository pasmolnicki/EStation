#include "SleepScreen.h"

namespace ui
{
    SleepScreen::SleepScreen() {
        _size = 1;
        _items = new SleepElement* [_size] {
            new SleepElement(BASE_SCREEN_BG)
        };
    }

    void SleepScreen::loop(){
        auto area = TouchPoint::null;

        while(!_exited){
            area = ts.read();
            // Update state of floating text
            BaseScreen::_updateItemsState(_items, _size);

            if (!(int)area){
                continue;
            }
            // If screen get's touched, then break sleep
            route(previousRoute());
        }
    }
}