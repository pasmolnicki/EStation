#include "ChooseWifi.h"

extern MemoryProvider memoryProvider;
extern WiFiProvider wifiProvider;
extern WifiProps wifiProps;
extern Localizer localizer;

extern String CURRENT_VER;

namespace ui
{

    // void linearScanTask(){
    //     Lock lock(getSemaphore(tasks::wifiScan));
    //     wifiProvider.scan();
    // }

    // void connectTask(){
    //     Lock lock(getSemaphore(tasks::wifiConn));
    //     wifiProvider.connect();
    // }

    constexpr auto loadingSize = 40;

    ChooseWifiScreen::ChooseWifiScreen(): 
        _title(160, 4, new TextProps(getLocale()->CHOOSE_WIFI_TITLE, placement::middle, BASE_SCREEN_BG, useFont(fonts::detail))),
        _ver(0, 0, new TextProps("v."+CURRENT_VER+" "+localizer.localizerName(),
            placement::start, BASE_SCREEN_BG, useFont(fonts::detail))),
        _network_manager(new NetworkListManager(10, 24, 230, 190, BASE_SCREEN_BG))
        // _elem(new WiFiListElement(nullptr, 10, 24, 230, 190, BASE_SCREEN_BG, new TextProps(""))),
        // _loading(new LoadingElement(110 - loadingSize/2, 40, loadingSize, BASE_SCREEN_BG))
    {
        _network_manager->setOnNotSavedEvent([&](){
            route(path::INPUT_PASS);
        });
        _network_manager->setOnConnectEvent([&](bool connected){
            route(connected ? path::LOCALIZATION : path::INPUT_PASS);
        });

        _size = 2;

        _items = new IconButtonElement*[_size] {
            new IconButtonElement(275, 10, new IconProps(
                new RefreshIcon(), 40, BASE_SCREEN_BG, DEFAULT_BTN_COLOR)
            ),
            new IconButtonElement(275, 60, new IconProps(
                new SettingsIcon(), 40, BASE_SCREEN_BG, DEFAULT_BTN_COLOR)
            ),
        };
        
        // Both of these are protected by mutex, so this is valid
        _items[0]->addOnClickEvent(
            [this](){
                _network_manager->runScan();
            }
        );

        _items[1]->addOnClickEvent(
            [this](){
                route(path::SETTINGS);
            }
        );

        wifiProvider.reset();
        _network_manager->runScan();
    }

    ChooseWifiScreen::~ChooseWifiScreen(){}

    void ChooseWifiScreen::preload(){
        _network_manager->preload();
        // _network_manager->setLoading(false);
    }

    void ChooseWifiScreen::draw(){
        DataBaseScreen<IconButtonElement>::draw();
        _network_manager->draw();
        _ver.draw();
        _title.draw();
    }

    void ChooseWifiScreen::eventListener(Point* point){
        if (_network_manager->isScanning())
            return;

        _network_manager->eventListener(point);
        BaseScreen::_eventHandler(_items, _size, point);
    }

    void ChooseWifiScreen::loop(){
        while (!_exited){
            std::unique_ptr<Point> touch(ts.read_touch());

            _network_manager->updateState();

            if (!touch){
                continue;
            }

            eventListener(touch.get());
        }
    }

}