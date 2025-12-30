#include "PassInputScreen.h"

extern WifiProps wifiProps;
extern WiFiProvider wifiProvider;
extern MemoryProvider memoryProvider;


namespace ui
{
    PassInputScreen::PassInputScreen():  
    _keyboard(new Keyboard(BASE_SCREEN_BG)), 
    _input(new InputFieldElement(70, 5, 180, 40, BASE_SCREEN_BG, new TextProps(wifiProps.ssid))),
    _popup(new ConnectPopup(160 - 170 / 2, 120 - 100 / 2, 170, 100, BASE_SCREEN_BG)) {

        // Keyboard essential callbacks
        _keyboard->addOnClickEvent([&](const String& clicked){
            this->_input->addChar(clicked);
            this->_input->draw();
        });
        _keyboard->addOnDeleteEvent([&](){
            this->_input->deleteChar();
            this->_input->draw();
        });

        // navigation buttons
        _size = 2;
        _items = new TextIconElement*[_size]{
            new TextIconElement(320 - 70 + 6, 2, 50, height, BASE_SCREEN_BG, 
                new TextProps("OK", placement::middle)),
            new TextIconElement(2, 2, height, height, BASE_SCREEN_BG, nullptr, 
                new IconProps(new GoBackIcon(), 40, BASE_SCREEN_BG, DEFAULT_BTN_COLOR, placement::middle)),
        };

        _items[0]->addOnClickEvent([&](){
            
            // Prepare the wifi provider to connect
            wifiProps.pass = _input->getValue();
            wifiProvider.begin(wifiProps.ssid, wifiProps.pass);
            
            // Create a new task to connect to the wifi
            AsyncTask<>([](){
                Lock lock(getSemaphore(tasks::wifiConn));
                wifiProvider.connect();
            }).setParams(TaskParams().setUsePinnedCore(true)).run();

            // Show the connection status
            _popup->loop();
            auto connected = wifiProvider.connected();

            if (connected){
                // save the network
                memoryProvider.writeNetwork(wifiProps.ssid, wifiProps.pass);
                route(path::LOCALIZATION);
                return;
            }
            _keyboard->draw();
        });
        _items[1]->addOnClickEvent([&](){
            route(path::CHOOSE_WIFI);
        });

        wifiProvider.reset();
    }

    PassInputScreen::~PassInputScreen(){}

    void PassInputScreen::draw(){
        DataBaseScreen<TextIconElement>::draw();
        _keyboard->draw();
        _input->draw();
    }

    void PassInputScreen::loop(){
        while(!_exited){
            std::unique_ptr<Point> touch(ts.read_touch());

            _input->blink();

            if (!touch.get()){
                continue;
            }

            _keyboard->eventListener(touch.get());
            iterate([&touch](TextIconElement* elem){elem->eventListener(touch.get());});
        }
    }
}