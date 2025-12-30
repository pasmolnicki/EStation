#pragma once

#include "BaseScreen.h"


namespace ui
{

/// @brief Template class of 'view' screens, abstraction over BaseScreen, adds of type T items
/// @tparam T must have parent class of `ScreenElement` (implemented: draw(), eventListener(Point*))
template <class T>
class DataBaseScreen : public BaseScreen
{
public:
    typedef std::function<void(T*)> iterate_cb;
    typedef std::function<void(T*, int)> foreach_cb;

    DataBaseScreen();

    virtual
    ~DataBaseScreen();

    virtual 
    void draw();

    /// @brief Calls the callback function on each item
    /// @param call Callback function with item as argument
    virtual
    void iterate(DataBaseScreen::iterate_cb);

    /// @brief Calls the callback function on each item
    /// @param call Callback function with item and index as arguments
    virtual
    void forEach(DataBaseScreen::foreach_cb);   

    virtual 
    void loop(); 

    T** _items;
    uint8_t _size;
};


template <class T> DataBaseScreen<T>::DataBaseScreen(): 
BaseScreen(), _items(nullptr), _size(0) {}

template <class T> DataBaseScreen<T>::~DataBaseScreen(){
    BaseScreen::_deleteItems(_items, _size);
}

template <class T>
void DataBaseScreen<T>::loop(){
    while(!_exited){
        std::unique_ptr<Point> touch(ts.read_touch());
        if(touch){
            _eventHandler(_items, _size, touch.get());
        }
    }
}

template <class T>
void DataBaseScreen<T>::draw(){
    tft.fillScreen(_base_bg);
    _drawItems(_items, _size);
}

template <class T> 
void DataBaseScreen<T>::forEach(foreach_cb call){
    _foreach(_items, _size, call);
}

template <class T> 
void DataBaseScreen<T>::iterate(iterate_cb call){
    _iterate(_items, _size, call);
}

}
