#pragma once

// Components
#include "../ScreenElement.h"
#include "../PosContainer.h"
#include "../state/LoadingElement.h"
#include "../popup/ConnectPopup.h"
#include "../lists/WiFiListElement.h"

// Data structures & providers
#include "../../data_structures/Props.h"
#include "../../providers/WiFiProvider.h"
#include "../../providers/MemoryProvider.h"

// Mutexes & AsyncTask
#include "../../tasks/includes.h"

namespace ui
{
    // Abstraction over the WiFiListElement, handles the scanning and connecting to networks,
    // and provides a loading element to show the user that the scan is in progress
    class NetworkListManager: public ScreenElement, public PosContainer
    {
    public:
        typedef std::function<void(void)> onBasicEvent;
        typedef std::function<void(bool)> onBoolEvent;

        static constexpr int LOADING_ICON_SIZE = 40;
        static void scanTask();
        static void connectTask();
        static void defaultOnClick(const WifiInfo&);

        NetworkListManager(
            uint16_t x,
            uint16_t y,
            uint16_t w,
            uint16_t h,
            uint16_t bg
        );

        
        void draw() override;
        bool eventListener(Point* touch) override;
        void updateState() override;

        void runScan();
        void setLoading(bool loading);
        void preload();
        bool isScanning() const;
       
        void setOnNotSavedEvent(onBasicEvent);
        void setOnConnectEvent(onBoolEvent);

    private:
        WiFiListElement m_list;
        LoadingElement m_loading;
        AsyncTask<> m_task;

        onBasicEvent m_onNotSavedEvent;
        onBoolEvent m_onConnectEvent;
    };
}