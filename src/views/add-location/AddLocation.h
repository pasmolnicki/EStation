#pragma once

#include "../base/DataBaseScreen.h"

#include "../../components/buttons/keyboard/Keyboard.h"
#include "../../components/forms/InputFieldElement.h"
#include "../../components/buttons/TextIconElement.h"
#include "../../components/state/LoadingElement.h"
#include "../../components/buttons/CardElement.h"
#include "../../components/utils.h"

#include "../../providers/MemoryProvider.h"

namespace ui
{
    /// @brief Merges 2 screens: query and display locations
    class AddLocation : public DataBaseScreen<TextIconElement>
    {
        public:
        AddLocation();

        void 
        draw();

        void 
        focusInput();

        void 
        focusLocation();

        void 
        iterateLoc(std::function<void(CardElement*, int)>);

        void 
        loop();

        bool _loaded;
        int _locSize;
        CardElement** _locations;
        std::unique_ptr<LoadingElement> _loading;
        std::unique_ptr<InputFieldElement> _input;
        std::unique_ptr<Keyboard> _keyboard;
        bool _keyboardOnFocus;
    };
}