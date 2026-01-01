#include "LocationScreen.h"

extern Localizer localizer;
extern WeatherProvider wProvider;
extern MemoryProvider memoryProvider;
extern ErrorProvider errorProvider;
extern LocationProps locProps;
extern WifiProps wifiProps;


namespace ui
{
    constexpr auto w = 250, h = 60;

    void catchFnTask(){
        wProvider.fetchSpecLocation();
    }

    // Fetch locations task, used to fetch locations from the memory
    void fetchLocationsTask(LocationScreen* src)
    {
        Lock lock(getSemaphore(tasks::weather));
        Lock err(getSemaphore(tasks::error));

        // User may not have specified the APPID token, so catch the error
        errorProvider.catchFn(catchFnTask);
        if (!errorProvider.caught()){
            auto fetched = wProvider.getSpecLocations();
            auto saved = memoryProvider.getLocations();
            for (int i = 0; i < saved->size(); i++){
                src->setLocationText(fetched->at(i), i);
            }
        } else {
            errorProvider.code(__FILE__);
        }
    }

    bool LocationScreen::_handleDelete = false;
    int LocationScreen::_indexOffset = 1;

    LocationScreen::LocationScreen():  
    _wifiConnection(new WifiConnectionElement(2, 2, 20, BASE_SCREEN_BG)),
    _networkName(new TextElement(25, 2, new TextProps(
        wifiProps.ssid, placement::start, BASE_SCREEN_BG, useFont(fonts::detail)))
    ) {       

        // Save current language & system to memory
        memoryProvider.setIfDifferent(LANGUAGE_ADDR, (uint8_t)localizer.current());
        memoryProvider.setIfDifferent(SYSTEM_ADDR, (uint8_t)localizer.getUnitSystem());

        initLocations();
    }

    void LocationScreen::initLocations(){

        memoryProvider.readLocations();
        auto locations = memoryProvider.getLocations();

        _indexOffset = locations->empty() ? 2 : 1;

        _size = _indexOffset + locations->size();

        _items = new CardElement*[_size] {
            new CardElement(0, 240 - h - 5, 320, h, BASE_SCREEN_BG, BASE_SCREEN_BG, 
                new TextProps(getLocale()->ADD_NEW_LOCATION, placement::middle), 
                new TextProps(getLocale()->SAVED_LOCATIONS + " (" + String(locations->size()) + "/" + String(maxCitiesCount) + F(")"),
                    placement::middle, 0, useFont(fonts::detail))
            ),
        };

        _items[0]->addOnClickEvent([&](){
            route(path::ADD_LOCATION);
        });

        if (locations->empty()){
            _items[1] = new CardElement(160 - w / 2, 25, w, h, BASE_SCREEN_BG, BASE_SCREEN_BG,
                    new TextProps(getLocale()->NO_SAVED_DATA, placement::start, _base_bg, useFont(fonts::normal), TFT_DARKGREY)
            );
            return;
        }
        // #############################
        // Loading locations from memory 

        for (int i = 0; i < locations->size(); i++){
            _items[i + _indexOffset] = new CardElement(160 - w / 2, 25 + i * (10 + h), w, h, DEFAULT_BTN_COLOR, BASE_SCREEN_BG,
                new TextProps(locations->operator[](i).first), 
                new TextProps("", placement::start, 0, useFont(fonts::detail)));
            _items[i + _indexOffset]->addIcon(new IconProps(new TrashIcon(), 40), [](){
                LocationScreen::_handleDelete = true;
            });
            _items[i + _indexOffset]->addOnClickEvent([](){
                LocationScreen::_handleDelete = false;
            });

            // If locations are already fetched
            if(!wProvider.getSpecLocations()->empty()){
                // find the same location
                auto find = locations->operator[](i).first;
                for (int j = 0; j < wProvider.getSpecLocations()->size(); j++){
                    if (wProvider.getSpecLocations()->at(j).search != find){
                        continue;
                    }
                    setLocationText(wProvider.getSpecLocations()->at(j), i);
                    break;
                }
            } else {
                // Prepare fetch
                wProvider.prepareSpecificLocation(
                    locations->operator[](i).first, locations->operator[](i).second);
            }
        }

        if(wProvider.getSpecLocations()->empty()){
            // Fetch locations
            AsyncTask<>(
                TaskParams().setUsePinnedCore(true), 
                [this]() {
                    fetchLocationsTask(this);
                }
            ).run();
        }
    }

    void LocationScreen::
    setLocationText(const LocationInfo& location, int i){
        _items[i + _indexOffset]->setHeaderText(location.name);
        _items[i + _indexOffset]->setContentText(
            !location.state.isEmpty() ? 
            location.state + ", " + location.country 
            : location.country);
    }

    void LocationScreen::handleDelete(int i){

        // To fix, it causes panic abort, if there are 2 locations, and the first one is deleted

        memoryProvider.eraseLocation(
            memoryProvider.getLocations()->at(i - _indexOffset).first);        
        
        iterate([](CardElement* elem){
            elem->clear();
            delete elem;
        });
        delete [] _items;
        initLocations();
        BaseScreen::_drawItems(_items, _size);
    }

    void LocationScreen::loop(){

        _wifiConnection->draw();
        _networkName->draw();

        while(!_exited){
            std::unique_ptr<Point> touch(ts.read_touch());

            handleError();

            _wifiConnection->updateState();
            TryLock lock(getSemaphore(tasks::weather), 2);
            if(lock){
                BaseScreen::_updateItemsState(_items, _size);
            }

            if (!(touch && lock)){
                continue;
            }

            // handle by hand on click event
            for(int i = 0; i < _size; i++){
                auto elem = _items[i];
                if (!elem->eventListener(touch.get()) || i < _indexOffset){
                    continue;
                }
                // That means the location button is clicked, check if it is delete
                if (_handleDelete){
                    handleDelete(i);
                    break;
                }
                auto loc = memoryProvider.getLocations()->at(i - _indexOffset);
                locProps.location = loc.first;
                locProps.index = loc.second;

                for (int j = 0; j < wProvider.getSpecLocations()->size(); j++){
                    if ((*wProvider.getSpecLocations())[j].search != loc.first){
                        continue;
                    }
                    locProps.country = (*wProvider.getSpecLocations())[j].country;
                    break;
                }
                route(path::LOADING);
                return;
            }
        }
    }
}