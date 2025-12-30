#pragma once

#include "../base/DataBaseScreen.h"
#include "../../components/buttons/TextIconElement.h"
#include "../../components/buttons/CardElement.h"
#include "../../components/wifi/WifiConnectionElement.h"

#include "../../providers/MemoryProvider.h"

namespace ui
{
    class LocationScreen: public DataBaseScreen<CardElement>
    {
        std::unique_ptr<TextElement> _networkName;
        std::unique_ptr<WifiConnectionElement> _wifiConnection;
        
    public:
        static bool _handleDelete;
        static int _indexOffset;

        LocationScreen();

        void 
        loop();

        void 
        setLocationText(const LocationInfo& location, int i);

        void 
        handleDelete(int i);

        void 
        initLocations();
    };
}