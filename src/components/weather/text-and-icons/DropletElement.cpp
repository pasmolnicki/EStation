#include "DropletElement.h"

namespace ui
{
    DropletElement::DropletElement(
        const Weather& weather, int16_t x, int16_t y,
        uint16_t bg, TextProps* textProps
    ): TextIconWeatherElement(weather, x, y, new IconProps(nullptr, 20, bg), textProps), _prevPop(-1) {
        (void)setter([this](const Weather& w) -> String {
            int8_t pop = int8_t(w._pop * 100);
            if (pop == this->_prevPop){
                return String(this->_prevPop) + " %";
            }
            this->_prevPop = pop;
            this->_icon->setIcon(matchIcon());
            return String(this->_prevPop) + " %";
        });
        _items[0]->_props->text = "";
    }

    Icon*  DropletElement::matchIcon(){
        _prevIcon = (_prevPop + 15) / 25;
        // 0 - 9    -> 0
        // 10 -> 34 -> 1
        // 35 -> 59 -> 2
        // 60 -> 84 -> 3
        // 85-100   -> 4
        switch(_prevIcon){
            case 0:
                return new DropletEmpty();
            case 1:
                return new DropletSmall();
            case 2:
                return new DropletMedium();
            case 3:
                return new DropletHigh();
            default:
                return new DropletFull();
        }
    }
}