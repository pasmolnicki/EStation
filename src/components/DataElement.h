#pragma once

#include "ScreenElement.h"

namespace ui
{
    template <class T>
    class DataElement : public ScreenElement{
        public:
        DataElement(const T& props);

        void 
        setData(const T& data);

        const T&
        getData();

        T _data;
        T _prev_data;
    };


    template <class T>
    DataElement<T>::DataElement(const T& props): ScreenElement(), _data(props) {}

    template <class T>
    void DataElement<T>::setData(const T& data){
        _prev_data = _data;
        this->_data = data;
        onUpdate();
    }

    template<class T>
    const T& DataElement<T>::getData(){
        return _data;
    }
}