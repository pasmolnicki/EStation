#include "IconGroup.h"


namespace ui
{
    IconGroup::IconGroup(): _width(0) {}

    IconGroup::IconGroup(int16_t x, int16_t y, std::initializer_list<IconProps*> _list): IconGroup() {
        addIcons(x, y, _list);
    }

    IconGroup::IconGroup(const IconGroup& other){
        (void)(*this = other);
    }

    void IconGroup::
    addIcons(int16_t x, int16_t y, std::initializer_list<IconProps*> _list){
        int i = _icons.size();
        // It works somehow, I don't know why tho
        _icons.insert(_icons.end(), _list.begin(), _list.end());
        int16_t _x = x, _y = y;
        for (auto it = _icons.begin(); it != _icons.end(); it++){
            it->get()->x = _x;
            it->get()->y = _y;
            _x += it->get()->size + 5;
            _width += it->get()->size + 5;
        }
    }

    void IconGroup::setRenderProps(const RenderProps& props){
        _renderProps = props;
    }

    void IconGroup::forEach(std::function<void(IconProps*, int i)> callb){
        int i = 0;
        for (auto it = _icons.begin(); it != _icons.end(); it++, i++){
            callb(it->get(), i);
        }
    }

    void IconGroup::draw(){
        forEach([](IconProps* elem, int ){drawIconProps(elem);});        
    }

    int16_t IconGroup::width(){
        return _width;
    }

    IconProps* IconGroup::
    getIcon(int index){
        IconProps* ret = nullptr;
        forEach([&](IconProps* elem, int i){
            if (i == index){
                ret = elem;
            }
        });
        return ret;
    }

    IconGroup& IconGroup::
    operator=(const IconGroup& other){
        _width = other._width;
        _renderProps = other._renderProps;
        _icons = other._icons;
        return *this;
    }
}