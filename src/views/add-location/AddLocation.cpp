#include "AddLocation.h"

extern WeatherProvider wProvider;
extern MemoryProvider memoryProvider;
extern LocationProps locProps;

namespace ui
{
    // Draw location buttons
    void drawLocations(CardElement* elem, int){
        elem->draw();
    }

    // Fetch locations callback
    void fetchCallback(AddLocation* src, std::vector<LocationInfo>* fetched){
        constexpr auto maxLocHeight = 60, locWidth = 190;

        // Clear previous locations
        if(src->_locations){
            for (int i = 0; i < src->_locSize; i++){
                delete src->_locations[i];
            }
            delete[] src->_locations;
        }

        // Flag that data is loaded
        src->_loaded = true;

        // If no data found, display message
        if (fetched->empty()){
            src->_locSize = 1;
            src->_locations = new CardElement*[1] {
                new CardElement(160 - 160 / 2, 80, 160, 40, BASE_SCREEN_BG, BASE_SCREEN_BG, 
                    new TextProps(getLocale()->NO_DATA_FOUND + "...", placement::middle, 0, useFont(fonts::detail)))
            };
            return;
        }

        // Display fetched locations
        src->_locSize = std::min((int)fetched->size(), 4);
        auto spacing = 5;
        auto height = src->_locSize > 2 ? (240 - 60 - src->_locSize*spacing) / src->_locSize : maxLocHeight;

        src->_locations = new CardElement*[src->_locSize];
        for (int i = 0; i < src->_locSize; i++){
            auto location = fetched->at(i);

            // Create card element for each location
            src->_locations[i] = new CardElement(
                160 - locWidth / 2, 60 + i * (spacing + height), locWidth, height,
                DEFAULT_BTN_COLOR, BASE_SCREEN_BG, 
                new TextProps(
                    location.name + " " + location.country, 
                    placement::start, 0, useFont(fonts::detail)),

                new TextProps(
                    location.state.isEmpty() ? 
                    String(location.lat) + " " + String(location.lon) :
                    location.state, placement::start, 0, useFont(fonts::detail))
            );
        }
    }

    AddLocation::AddLocation():
    _loaded(false), _locSize(0),  _locations(nullptr),
    _loading(new LoadingElement(160 - 80 / 2, 120 - 80 / 2, 80, BASE_SCREEN_BG)), 
    _input(new InputFieldElement(160 - 180 / 2, 4, 180, 40, BASE_SCREEN_BG, new TextProps(getLocale()->SEARCH))),
    _keyboard(new Keyboard(BASE_SCREEN_BG)), _keyboardOnFocus(false) 
    {
        using namespace async_tasks;

        _loading->setLoading(false);

        // Keyboard essential callbacks
        _keyboard->addOnClickEvent([&](const String& clicked){
            this->_input->addChar(clicked);
            this->_input->draw();
        });
        _keyboard->addOnDeleteEvent([&](){
            this->_input->deleteChar();
            this->_input->draw();
        });

        _input->addOnClickEvent([&](){
            if (_keyboardOnFocus){
                return;
            }
            focusInput();
        });

        // navigation buttons
        _size = 3;
        _items = new TextIconElement*[_size]{
            // OK button
            new TextIconElement(320 - 70 + 6, 2, 50, height, BASE_SCREEN_BG, 
                new TextProps("OK", placement::middle)),
            // Cancel button
            new TextIconElement(2, 2, height, height, BASE_SCREEN_BG, nullptr, 
                new IconProps(new GoBackIcon(), 40, BASE_SCREEN_BG, DEFAULT_BTN_COLOR, placement::middle)),
            // Quit button (only visible when keyboard is not focused)
            new TextIconElement(2, 2, height, height, BASE_SCREEN_BG, nullptr, 
                new IconProps(new GoBackIcon(), 40, BASE_SCREEN_BG, DEFAULT_BTN_COLOR, placement::middle)),
        };
        
        // OK button
        _items[0]->addOnClickEvent([&](){
            Serial.println("Searching for: " + _input->getValue());

            focusLocation();
            // Prepare fetch
            Lock lock(getSemaphore(tasks::weather));
            wProvider.prepareLocation(_input->getValue());

            // Fetching task
            AsyncTask<>(
                TaskParams().setUsePinnedCore(true),
                [this](){
                    Lock lock(getSemaphore(tasks::weather));
                    wProvider.fetchLocation();
                    fetchCallback(this, wProvider.getLocations());
                }
            ).run();

            _loading->setLoading(true);
            _loading->updateState();

            Serial.println("Fetching location...");
        });
        // Cancel button
        _items[1]->addOnClickEvent([&](){
            focusLocation();
            Lock lock(getSemaphore(tasks::weather));
            iterateLoc(drawLocations);
        });
        // Quit button
        _items[2]->addOnClickEvent([&](){
            route(path::LOCALIZATION);
        });

        auto locale = getLocale();

        _locSize = 1;
        _locations = new CardElement*[_locSize] {
            new CardElement(160 - 320 / 2, 80, 320, 80, BASE_SCREEN_BG, BASE_SCREEN_BG, 
                new TextProps(locale->INPUT_LOCATION_HERE, placement::middle),
                new TextProps(locale->CLICK_AT_THE_SEARCH_BAR, placement::middle, 0, useFont(fonts::detail))
            ),
        };
    }


    void AddLocation::
    focusInput(){
        _keyboard->clear();
        _keyboard->draw();

        _items[2]->clear();
        _items[0]->draw();
        _items[1]->draw();
        _keyboardOnFocus = true;
    }   

    void AddLocation::
    focusLocation(){
        _keyboardOnFocus = false;
        _keyboard->clear();
        _items[0]->clear();
        _items[1]->clear();
        _items[2]->draw();
        _input->draw();
    }

    void AddLocation::
    iterateLoc(std::function<void(CardElement*, int)> callb){
        if (!_locations){
            return;
        }
        for (int i = 0; i < _locSize; i++){
            callb(_locations[i], i);
        }
    }

    void AddLocation::draw(){
        tft.fillScreen(BASE_SCREEN_BG);
        _input->draw();
        if (_keyboardOnFocus){
            _keyboard->draw();
            _items[0]->draw();
            _items[1]->draw();
            return;
        }
        _items[2]->draw();
    }

    void AddLocation::loop(){
        iterateLoc(drawLocations);

        while(!_exited){
            std::unique_ptr<Point> touch(ts.read_touch());

            handleError();

            if (_keyboardOnFocus){
                _input->blink();
            }
            else {
                _loading->updateState();
                
                TryLock lock(getSemaphore(tasks::weather), 2);
                if (!lock){
                    continue;
                }
                // Data is loaded
                if (_loaded){
                    _loading->setLoading(false);
                    _loading->clear();
                    _loaded = false;

                    iterateLoc(drawLocations);     
                }                               
            }
            
            if (!touch){
                continue;
            }

            if (_keyboardOnFocus){
                _keyboard->eventListener(touch.get());
                _items[0]->eventListener(touch.get());
                _items[1]->eventListener(touch.get());
                continue;
            }
            _items[2]->eventListener(touch.get());
            _input->eventListener(touch.get());

            // Check if location is clicked
            TryLock lock(getSemaphore(tasks::weather));
            if (!lock){
                continue;
            }

            if (!wProvider.getLocations()->empty()){
                iterateLoc([&](CardElement* elem, int i){
                    if (elem->eventListener(touch.get())){
                        memoryProvider.writeLocation(_input->getValue(), i);
                        locProps.index = i;
                        locProps.location = _input->getValue();
                        locProps.country = wProvider.getLocations()->at(i).country;
                        route(path::LOADING);
                    }
                });
            }
        }
    }
}