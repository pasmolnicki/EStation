#include "WiFiBtnElement.h"

namespace ui
{
    WiFiBtnElement::WiFiBtnElement(
        const WifiInfo& init,
        uint16_t x,
        uint16_t y,
        uint16_t w,
        uint16_t h,
        uint16_t bg,
        TextProps* props
    ): 
    DataElement<WifiInfo>(init),
    _touchArea(new TouchButton(x, y, w, h)), 
    _textProps(createDefaultIfNull(props)), bg(bg) {
        _textProps->text = init.ssid;
        _textProps->bg = _touchArea->color;

        int16_t size = w > h ? h*0.8f : w*0.8f;
        size = size > 40 ? 40 : size;

        _iconGroup.addIcons(x + w - 2 * (size + 5), y + (h - size) / 2, {
            new IconProps(new WiFiLostIcon(), size, _touchArea->color),
            new IconProps(init.isSaved ? (Icon*) new LockerUnlocked() : (Icon*) new LockerLocked(), size, _touchArea->color),
        });
        onUpdate();
    }

    WiFiBtnElement::WiFiBtnElement(
        const WiFiBtnElement& other
    ): DataElement<WifiInfo>(other._data) {
        (void)(*this = other);
    }

    void WiFiBtnElement::addOnClickEvent(std::function<void(void)> event){
        _touchArea->addOnClickListener(event);
    }

    bool WiFiBtnElement::check(Point* touch){
        return _touchArea->check(touch->x, touch->y);
    }

    void WiFiBtnElement::onUpdate(){
        this->_redraw = _prev_data != _data;

        // Probably this should be turned into Truncation class

        // check if text truncation is needed
        if (_redraw){
            // Serial.println("Redraw " + _data.first);

            _textProps->text = truncateText(_textProps.get(), _touchArea->width - _iconGroup.width() - 5);
            delete _iconGroup.getIcon(0)->icon;
            _iconGroup.getIcon(0)->icon = iconMatcher();
        }
    }

    void WiFiBtnElement::draw(){
        drawMenuButton(
            _touchArea->x, 
            _touchArea->y, 
            _touchArea->width, 
            _touchArea->height,
            _touchArea->color, 
            bg, _textProps.get() 
        );
        _iconGroup.draw();
    }   

    Icon* WiFiBtnElement::iconMatcher(){
        // -1 -> -24 super strong (0)
        // -25 -> -49 great (1)
        // -50 -> -74 medium (2)
        // -75 -> -128 weak (3)
        auto normalized = _data.strenght / -25;

        switch (std::min<int>(normalized, 3))
        {
        case 0: // strong
            return new WiFiStrongIcon();
        case 1:
            return new WiFiGreatIcon();
        case 2:
            return new WiFiMediumIcon();
        case 3:
            return new WiFiWeakIcon();
        default:
            return new WiFiLostIcon();
        }
    }

    WiFiBtnElement& WiFiBtnElement::operator=(const WiFiBtnElement& other){
        _data = other._data;
        _text = other._text;
        _iconGroup = other._iconGroup;
        _touchArea.reset(new TouchButton(*other._touchArea));
        _textProps.reset(new TextProps(*other._textProps));
        bg = other.bg;
        _data = other._data;
        return *this;
    }
}