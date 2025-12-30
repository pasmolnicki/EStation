#pragma once

#include "../../../input/keyboard/KeyboardButton.h"
#include "../../../input/custom_buttons/IconButton.h"
#include "../../../input/custom_buttons/TextIconButton.h"
#include "../../DataElement.h"
#include "../../../lang/keyboard/qwerty-en.h"

namespace ui
{
    class Keyboard: public DataElement<String>
    {
        KeyboardButton*** _keypad;
        std::unique_ptr<IconButton> _delete;
        std::unique_ptr<TextIconButton> _capsLock;
        std::unique_ptr<KeyboardButton> _changeMode;
        int _currentLayout;
        uint16_t _bg;

        std::function<void(const String&)> _onClick;
    public:
        Keyboard(
            uint16_t bg,
            const String& init = ""
        );
        ~Keyboard();

        virtual void
        draw();

        void 
        clear();

        virtual bool
        eventListener(Point* touch);

        void
        addOnDeleteEvent(std::function<void(void)>);

        void
        addOnClickEvent(std::function<void(const String&)>);

        virtual void
        iterate(std::function<void(KeyboardButton*)>);
    };
    
}
