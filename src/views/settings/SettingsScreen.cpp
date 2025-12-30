#include "SettingsScreen.h"

namespace ui
{
    SettingsScreen::SettingsScreen():
    _title(new TextElement(160, 5, new TextProps(getLocale()->SETTINGS_TITLE, placement::middle, BASE_SCREEN_BG))) {
        _size = 3;

        constexpr auto width = 220;
        constexpr auto heigth = 42;

        auto locale = getLocale();

        _items = new TextIconElement*[_size] {

            new TextIconElement(160 - width / 2, 50, width, heigth, BASE_SCREEN_BG, 
                new TextProps(locale->PICK_LANG, placement::middle)),

            new TextIconElement(160 - width / 2, 50 + heigth + 10, width, heigth, BASE_SCREEN_BG, 
                new TextProps(locale->SYSTEM, placement::middle)),

            // new TextIconElement(160 - width / 2, 50 + 2*(heigth + 10), width, heigth, _base_bg,
            //     new TextProps(locale->MANAGE_NETWORKS, placement::middle)),

            new TextIconElement(5, 5, 34, 34, BASE_SCREEN_BG, nullptr, 
                new IconProps(new GoBackIcon(), 30, BASE_SCREEN_BG, DEFAULT_BTN_COLOR, placement::middle))
        };

        _items[0]->addOnClickEvent([&](){
            route(path::LOCALE);
        });

        _items[1]->addOnClickEvent([&](){
            route(path::SET_UNIT_SYTEM);
        });

        // _items[2]->addOnClickEvent([&](){
        //     route(path::MANAGE_NETWORKS);
        // });

        _items[_size - 1]->addOnClickEvent([&](){
            route(path::CHOOSE_WIFI);
        });
    }

    void SettingsScreen::draw(){
        this->DataBaseScreen<TextIconElement>::draw();
        _title->draw();
    }
}