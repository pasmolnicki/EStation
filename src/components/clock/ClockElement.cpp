#include "ClockElement.h"

// Defined in `src/providers/DateTimeProvider.cpp`
extern DateTimeProvider dateProvider;

namespace ui
{
    ClockElement::ClockElement(
        const Weather& init,
        int16_t y,
        uint16_t bg
    ): WeatherElement<ClockSectionElement>(init) {
        _size = 8;

        // Calculate x axis coordinates of each element
        uint16_t x = 160;
        std::unique_ptr<TextProps> props(
            new TextProps("00:00:00", placement::middle, 0, useFont(fonts::clock)));
        FontLoader fl(x, props.get());

        int16_t 
            total      = tft.textWidth("00:00:00"), 
            segment    = tft.textWidth("00:"),
            colonWidth = 3*segment - total, // 3 * "00:" = "00:00:00:", "00:00:00:" - "00:00:00" = ":"
            digitWidth = (total - 2*segment) / 2; // ("00:00:00" - "00:00:" ) / 2 = ("00") / 2 = "0"
        x -= total/2;

        _items = new ClockSectionElement*[_size];

        auto str = "00:00:00";
        int offset_x = 0;
        for (uint8_t i = 0; i < _size; i++){
            _items[i] = new ClockSectionElement(
                init, x + offset_x, y, new TextProps(
                    String(str[i]), placement::start, bg, useFont(fonts::clock))
            );
            offset_x += str[i] == '0' ? digitWidth : colonWidth;
        }
    }
    void ClockElement::updateState(){

        // Since clock element just visually represents the clock
        // then there is no need to restrict it by redraw condition
        // (look at TextWeatherElement implementation of this function)
        onUpdate();
        iterate([](ClockSectionElement* elem){elem->updateState();});
    }

    void ClockElement::onUpdate(){
        struct tm* date = dateProvider.getTimeinfo();

        // indexes
        // 0-1 -> hours
        // 3-4 -> minutes
        // 6-7 -> seconds
        // 2,5 -> colons
        _items[0]->setText(String(date->tm_hour/10));
        _items[1]->setText(String(date->tm_hour%10));

        _items[3]->setText(String(date->tm_min/10));
        _items[4]->setText(String(date->tm_min%10));

        _items[6]->setText(String(date->tm_sec/10));
        _items[7]->setText(String(date->tm_sec%10));
    }
}