#pragma once

#include "../DataElement.h"
#include "../../data_structures/Props.h"
#include "../../data_structures/weather/Weather.h"

namespace ui
{
    /// @brief Abstracion over DataElement, allows for adding items of given T type
    /// @tparam T child of `TouchButton` 
    template <class T>
    class WeatherElement : public DataElement<Weather>
    {
    public:
        WeatherElement(const Weather&);

        virtual
        ~WeatherElement();

        virtual void
        iterate(std::function<void(T*)>);

        virtual void
        draw();

        T** _items;
    };

    template <class T>
    WeatherElement<T>::WeatherElement(const Weather& props) :
    DataElement<Weather>(props), _items(nullptr) {}

    template <class T>
    WeatherElement<T>::~WeatherElement(){
        ScreenElement::_deleteItems(_items, _size);
    }

    template <class T>
    void WeatherElement<T>::iterate(std::function<void(T*)> call){
        ScreenElement::_iterateItems(_items, _size, call);
    }

    template <class T>
    void WeatherElement<T>::draw(){
        iterate(_drawItem<T>);
    }
}