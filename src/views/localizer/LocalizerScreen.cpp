#include "LocalizerScreen.h"

extern Localizer localizer;

namespace ui
{
    constexpr auto offsetIndex = 1;

    LocalizerScreen::LocalizerScreen(): 
    _title(160, MENU_SPACING, new TextProps(
            getLocale()->CURRENT_LANG + ": " + localizer.localizerName(), placement::middle, BASE_SCREEN_BG, useFont(fonts::detail))){

        _size = offsetIndex + NUMBER_OF_LOCALIZERS;

        _items = new TextIconElement* [_size] {
            new TextIconElement(5, 5, 40, 40, BASE_SCREEN_BG, nullptr, 
                new IconProps(new GoBackIcon(), 32, DEFAULT_BTN_COLOR, DEFAULT_BTN_COLOR, placement::middle) ),
        }; 

        // create buttons to corresponding localizers
        uint16_t y = MENU_SPACING + 30, h = 40;
        for (uint8_t i=0; i < NUMBER_OF_LOCALIZERS; i++){
            _items[i + offsetIndex] = new TextIconElement(
                110, y + i*(h + 10), 100, h, BASE_SCREEN_BG, 
                    new TextProps(localizer.getLocalizerNames()[i]),
                    new IconProps(iconFlagMatcher(localizer.getLocales()[i]))
                );
        }
        _items[0]->addOnClickEvent([&](){
            route(path::SETTINGS);
        });
    }

    void LocalizerScreen::draw(){
        this->DataBaseScreen<TextIconElement>::draw();
        _title.draw();
    }

    void LocalizerScreen::loop(){
        while(!_exited){
            std::unique_ptr<Point> touch(ts.read_touch());

            if (!touch){
                continue;
            }

            // simply iterate, but we need index, i starts at 0,
            // considering the fact, that there are _size = offsetIndex + NUMBER_OF_LOCALES
            // items, by substracting offsetIndex, from i (for i >= offsetIndex), 
            // index of locale is evaulated
            forEach([&](TextIconElement* elem, int i){
                if (elem->eventListener(touch.get()) && i >= offsetIndex){
                    localizer.setLocalizer(localizer.getLocales()[i - offsetIndex]); // set locale
                    _title.setText(getLocale()->CURRENT_LANG + ": " + localizer.localizerName());
                    _title.updateState();
                }             
            });
        }
    }
}