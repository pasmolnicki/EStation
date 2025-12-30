#pragma once

#include "icons.h"

#include "../weather.h"

#define SUNNY 0xF4E3
#define MOON 0xE64D
#define CLOUDY 0xB5B6
#define LIGHT_DARK_CLOUDS 0xA534
#define MIDDLE_DARK_CLOUDS 0x8C71
#define ALMOST_DARK_CLOUDS 0x7BEF
#define DARK_CLOUDS 0x632C
#define WATER 0x051D
#define SNOW_FLAKE 0x8E7F
#define MIST 0xDEFB
#define WIFI_BG 0x9790

namespace ui
{
    class SunIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class MoonIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class FewCloudsDayIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class FewCloudsNightIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class CloudsDayIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class CloudsNightIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class ManyCloudsIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class RainIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class BigRainIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class StormIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class SnowIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class MistDayIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class MistNightIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class SunriseIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class SunsetIcon : public Icon{
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };
}