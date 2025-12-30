#pragma once

#include "../base/DataBaseScreen.h"
#include "../../components/buttons/TextElement.h"
#include "../../components/state/LoadingElement.h"
#include "../../tasks/includes.h"

namespace ui
{

    class LoadingScreen: public DataBaseScreen<TextElement>
    {
        bool _weatherLoaded;
        std::unique_ptr<LoadingElement> _spinner;

    public:
        LoadingScreen();
        ~LoadingScreen();

        void 
        draw();

        void 
        loop();
    };
}