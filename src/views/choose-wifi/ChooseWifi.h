#pragma once

#include "../base/DataBaseScreen.h"

#include "../../providers/WiFiProvider.h"
#include "../../providers/MemoryProvider.h"

#include "../../components/lists/WiFiListElement.h"
#include "../../components/buttons/IconButtonElement.h"
#include "../../components/state/LoadingElement.h"
#include "../../components/popup/ConnectPopup.h"
#include "../../components/buttons/TextElement.h"
#include "../../components/wifi/NetworkListManager.h"

namespace ui
{

    class ChooseWifiScreen : public DataBaseScreen<IconButtonElement>
    {
        TextElement _ver;
        TextElement _title;
        
        // std::unique_ptr<WiFiListElement> _elem;
        // std::unique_ptr<LoadingElement> _loading;
        std::unique_ptr<NetworkListManager> _network_manager;
        // AsyncTask<> _scanTask;
        
        // void updateNetworks();
        void eventListener(Point* point);

    public:
        ChooseWifiScreen();
        ~ChooseWifiScreen();

        virtual void
        draw();

        virtual void 
        loop();

        virtual void
        preload();
    };

}