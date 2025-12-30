#include "TextIconButton.h"

namespace ui
{
    TextIconButton::TextIconButton(
        uint16_t x, uint16_t y,
        uint16_t w, uint16_t h,
        uint16_t bg,  
        TextProps* text,
        IconProps* icon
    ): TouchButton(x, y, w, h), 
    _text_props(createDefaultIfNull(text)), 
    _icon_props(createDefaultIfNull(icon)) {
        this->bg = bg;
        setIconProps(_icon_props.get());
        _text_props->bg = color;
        _icon_props->bg = color;
    }

    TextIconButton* TextIconButton::setIconProps(
        IconProps* props
    ){
        if (!props){
            return this;
        }
        if (props != _icon_props.get()){
            _icon_props.reset(props);
        }
        prepareButtonIconProps(x, y, width, height, _icon_props.get());
        return this;
    } 

    TextIconButton* TextIconButton::
        setTextProps(TextProps* props){
            if (props && props != _text_props.get()){
                _text_props.reset(props);
            }
            return this;
        }

    void TextIconButton::setIcon(Icon* icon){
        if (!(icon && _icon_props.get() && _icon_props->icon)){
            return;
        }
        delete _icon_props->icon;
        _icon_props->icon = icon;
    }

    void TextIconButton::setText(const String& str){
        if(!_text_props.get()){
            return;
        }
        _text_props->text = str;
    }
    
    void TextIconButton::draw(){
        if (!_text_props->text.isEmpty()){
            drawMenuButton(x, y, width, height, color, bg, _text_props.get());
        }
        else{
            drawCard(x, y, width, height, color, bg);
        }        
        if(_icon_props->icon){
            _icon_props->icon->draw(
                _icon_props->x, _icon_props->y, _icon_props->size, _icon_props->color, color
            );
        }
    }

    void TextIconButton::clear(){
        tft.fillRect(x, y, width, height, bg);
    }
}