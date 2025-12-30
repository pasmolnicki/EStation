#pragma once

#include "../PosContainer.h"
#include "../buttons/WiFiBtnElement.h"

namespace ui
{
    class WiFiListElement: public DataElement<std::vector<WifiInfo>*>, public PosContainer
    {
        int _btnHeight;
        uint16_t _bg;

        std::list<WiFiBtnElement> _btns;
        TextProps* _props;
        std::function<void(const WifiInfo&)> _onClickEvent;

        void 
        iterate(std::function<void(WiFiBtnElement*)>);

        public:
        WiFiListElement(
            std::vector<WifiInfo>* init,
            uint16_t x,
            uint16_t y,
            uint16_t w,
            uint16_t h,
            uint16_t bg,
            TextProps* props = nullptr
        );

        void 
        draw();

        virtual bool
        eventListener(Point* touch);

        void
        setOnClickEvent(std::function<void(const WifiInfo&)>);

        bool
        isUpdated();

        virtual void
        updateState();

        virtual void
        onUpdate();
    };
}