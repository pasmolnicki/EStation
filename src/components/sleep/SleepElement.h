#pragma once

#include "../weather/text/TextWeatherElement.h"
#include "../../providers/DateTimeProvider.h"
#include "../../tasks/includes.h"

typedef struct{
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;
    int16_t Vx;
    int16_t Vy;
    int16_t prevX;
    int16_t prevY;
} position_t;

namespace ui
{
    enum _TextIndex{
        CLOCK,
        WEATHER,
    };

    class SleepElement: public TextWeatherElement
    {
        uint32_t _tickCount;
        bool _freqUpdate;
        _TextIndex _text_index;
        TFT_eSprite _sprite;
        position_t _pos;
        uint64_t _lastUpdate;
        uint16_t _bg;

        void (*_spriteUpdater)(SleepElement*);

        void _setSystemInfo();
        void _setTemperature();
        void _setClock();

        void _updateIndex();

        public:
        /// @brief Creates floating hour clock, must be in transaction for `tasks::clock` 
        /// @param bg 
        SleepElement(uint16_t bg);
        ~SleepElement();

        void updateSprite();

        void move();

        void draw();

        void updateState();
    };
}