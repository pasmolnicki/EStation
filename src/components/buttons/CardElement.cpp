#include "CardElement.h"

namespace ui
{
    CardElement::CardElement(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t color,
        uint16_t bg,
        TextProps* header,
        TextProps* content
    ): _x(x), _y(y), _w(w), _h(h), _bg(bg), _color(color), _field(new TouchButton(x, y, w, h)) {

        header = createDefaultIfNull(header);
        content = createDefaultIfNull(content);

        prepareProps(header);
        prepareProps(content);

        _header.reset(new TextButton(header->x, header->y, header));
        _content.reset(new TextButton(content->x, content->y, content));

        setHeaderTextProps(header);
        setContentTextProps(content);
    }


    void CardElement::
    prepareProps(Props* props){
        switch (props->location)
        {
        case placement::start:
            props->x = _x + 5;
            break;
        case placement::middle:
            props->x = _x + _w / 2;
            break;

        default:
            props->x = _x - 5 + _w;
            break;
        }
        props->bg = _color;
    }


    void CardElement::
    setHeaderTextProps(TextProps* props){
        if (!props){
            return;
        }

        prepareProps(props);
        
        if (_header->_props.get() != props){
            _header->_props.reset(props);
        }

        int fhh = 0;           
        uint16_t ax = _x;
        FontLoader fl(ax, props);
        fhh = tft.fontHeight();            
        _header->y = _y + (_h / 2 - fhh) / 2 + 2;
        setHeaderText(String(props->text));
    }

    void CardElement::
    setContentTextProps(TextProps* props ){
        if (!props){
            return;
        }

        prepareProps(props);
        
        if (_content->_props.get() != props){
            _content->_props.reset(props);
        }
        
        int fhc = 0;
        uint16_t ax = _x;
        FontLoader fl(ax, props);
        fhc = tft.fontHeight();            
        _content->y = _y +  0.75f*_h - 0.5f*fhc;
        setContentText(String(props->text));
    }

    void CardElement::addIcon(IconProps* props, std::function<void(void)> onClickHandler){
        if (!props){
            return;
        }

        prepareProps(props);
        if (props->location == placement::end){
            props->x -= props->size;
        }        
        props->y = _y + (_h/2 - props->size) / 2 + 5;
        props->bg = _color;
        props->color = _color;

        _icon.reset(new IconButton(props->x, props->y, props));
        _icon->addOnClickListener(onClickHandler);
    }

    void CardElement::
    setHeaderText(const String& str){
        _header->_props->text = str;
        _header->_props->text = truncateText(_header->_props.get(), _icon.get() ? _w - 20 - _icon->_props->size : _w - 20);
        _redraw = true;
    }

    void CardElement::
    setContentText(const String& str){
        _content->_props->text = str;
        _content->_props->text = truncateText(_content->_props.get(), _w - 20);
        _redraw = true;
    }

    void CardElement::draw(){
        drawCard(_x, _y, _w, _h, _color, _bg);
        _content->draw();
        _header->draw();
        if (_icon){
            _icon->draw();
        }
    }

    void CardElement::clear(){
        tft.fillRect(_x, _y, _w, _h, _bg);
    }

    void CardElement::
    addOnClickEvent(std::function<void(void)> event){
        _field->addOnClickListener(event);
    }

    bool CardElement::
    eventListener(Point* touch){
        if (!_icon){
            return _field->check(touch->x, touch->y);
        }
        return _icon->check(touch->x, touch->y) || _field->check(touch->x, touch->y);
    }
}