#pragma once

#include <list>

#include "ScreenElement.h"
#include "../input/custom_buttons/IconButton.h"
#include "../output/button.h"


namespace ui
{
    /*
        ## IconGroup
        Helper component for Icon group rendering,
    */ 
    class IconGroup: public ScreenElement
    {
        int16_t _width;
        RenderProps _renderProps;
        std::list<std::shared_ptr<IconProps>> _icons;
    public:
        IconGroup(int16_t x, int16_t y, std::initializer_list<IconProps*> _list);
        IconGroup();
        IconGroup(const IconGroup& other);

        void 
        addIcons(int16_t x, int16_t y, std::initializer_list<IconProps*> _list);

        IconProps* 
        getIcon(int index);

        void 
        setRenderProps(const RenderProps&);

        int16_t width();

        void 
        draw();

        void 
        forEach(std::function<void(IconProps*, int _)>);

        IconGroup& operator=(const IconGroup& other);
    };
}