#include "UnitSystemScreen.h"

extern Localizer localizer;


namespace ui
{
    UnitSystemScreen::UnitSystemScreen():
    _title(160, 10, new TextProps(
        getLocale()->CURRENT_SYSTEM + ": " + localizer.getUnitSystemVerboseName(),
        placement::middle, BASE_SCREEN_BG, useFont(fonts::detail)
    )),
    _return(new IconButtonElement(5, 5, new IconProps(new GoBackIcon(), 34, BASE_SCREEN_BG, DEFAULT_BTN_COLOR))) {

        _size = 3;
        _items = new CardElement*[_size];

        constexpr auto w = 250, h = 60, x = 160 - w / 2, y = 45, spacing = (240 - 3*h - y) / 3;

        unitSystem unitSys[] = {unitSystem::metric, unitSystem::imperial, unitSystem::standard};

        auto locale = getLocale();

        for (int i = 0; i < _size; i++){
            localizer.setUnitSystem(unitSys[i]);
            _items[i] = new CardElement(x, y + i*(h + spacing), w, h, DEFAULT_BTN_COLOR, BASE_SCREEN_BG,
                new TextProps(localizer.getUnitSystemVerboseName()),
                new TextProps(locale->TEMP + ": " + localizer.getUnit(unit::temperature) + ", " + 
                            locale->SPEED + ": " + localizer.getUnit(unit::velocity), 
                    placement::start, 0, useFont(fonts::detail))
            );
        }

        _return->addOnClickEvent([&](){
            route(path::SETTINGS);
        });

        localizer.setUnitSystem(unitSys[0]);
    }

    void UnitSystemScreen::draw(){
        DataBaseScreen<CardElement>::draw();
        _return->draw();
        _title.draw();
    }

    void UnitSystemScreen::loop(){
        
        std::unique_ptr<Point> touch;
        while (!_exited){
            touch.reset(ts.read_touch());

            if (!touch){
                continue;
            }
            _return->eventListener(touch.get());

            forEach([&](CardElement* elem, int i){
                if (elem->eventListener(touch.get())){
                    localizer.setUnitSystem(unitSystem(i));
                    _title.setText(getLocale()->CURRENT_SYSTEM + ": " + localizer.getUnitSystemVerboseName());
                    _title.updateState();
                }
            });
        }
    }
}