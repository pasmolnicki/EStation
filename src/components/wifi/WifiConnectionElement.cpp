#include "WifiConnectionElement.h"

extern WiFiProvider wifiProvider;

namespace ui
{
    WifiConnectionElement::WifiConnectionElement(
        int16_t x,
        int16_t y,
        int16_t size,
        uint16_t bg
    ): _icon(new IconProps(new WiFiLostIcon(), size, bg)), _strenght(0), _lastCheck(millis()) {
        _icon->x = x;
        _icon->y = y;
    }

    void WifiConnectionElement::draw(){
        uint16_t 
            x = _icon->x,
            y = _icon->y,
            s = _icon->size,
            bg = _icon->bg;
        _icon->icon->draw(x, y, s, TFT_WHITE, bg);
    }

    void WifiConnectionElement::onUpdate(){
        // -1 -> -24 strong (0)
        // -25 -> -49 great (1)
        // -50 -> -74 medium (2)
        // -75 -> -128 weak (3)
        // no connection (4)
        auto normalized = WiFi.RSSI() / -25;
        auto strength = std::min(normalized, 3);
        strength = wifiProvider.connected() ? strength : 4;

        if (strength != _strenght){
            _strenght = strength;
            _redraw = true;
            delete _icon->icon;
            _icon->icon = iconMatcher();
        }
    }

    void WifiConnectionElement::updateState(){
        if (millis() - _lastCheck < 1000){
            return;
        }
        _lastCheck = millis();
        onUpdate();
        if (_redraw){
            draw();
        }
    }


    Icon* WifiConnectionElement::iconMatcher(){

        switch (_strenght)
        {
        case STRONG: // strong
            return new WiFiStrongIcon();
        
        case GREAT:
            return new WiFiGreatIcon();

        case MEDIUM:
            return new WiFiMediumIcon();

        case WEAK:
            return new WiFiWeakIcon();

        default:
            return new WiFiLostIcon();
        }
    }
}