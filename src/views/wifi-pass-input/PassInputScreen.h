#pragma once

#include "../base/DataBaseScreen.h"

#include "../../providers/MemoryProvider.h"

#include "../../components/buttons/keyboard/Keyboard.h"
#include "../../components/buttons/TextIconElement.h"
#include "../../components/forms/InputFieldElement.h"
#include "../../components/popup/ConnectPopup.h"


namespace ui
{

    class PassInputScreen : public DataBaseScreen<TextIconElement>
    {
        std::unique_ptr<InputFieldElement> _input;
        std::unique_ptr<Keyboard> _keyboard;
        std::unique_ptr<ConnectPopup> _popup;
    public:
        PassInputScreen();

        virtual 
        ~PassInputScreen();

        virtual void
        draw();

        virtual void 
        loop();
    };

}