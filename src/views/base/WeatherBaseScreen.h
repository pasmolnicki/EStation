#pragma once

#include "DataBaseScreen.h"

#include "../../providers/WeatherProvider.h"

#include "../../components/weather/icons/WeatherDisplayElement.h"
#include "../../components/clock/ClockElement.h"
#include "../../components/clock/DateElement.h"
#include "../../components/weather/text-and-icons/SunriseElement.h"
#include "../../components/weather/text-and-icons/SunsetElement.h"
#include "../../components/wifi/WifiConnectionElement.h"
#include "../../components/buttons/IconButtonElement.h"
#include "../../components/buttons/TextElement.h"
#include "../../components/weather/text/TimeElement.h"
#include "../../components/weather/text-and-icons/DropletElement.h"
#include "../../components/utils/ScreenPointElement.h"

extern WeatherProvider wProvider;
extern DateTimeProvider dateProvider;

namespace ui
{
    class WeatherBaseScreen: public DataBaseScreen<DataElement<Weather>>
    {

        uint64_t _lastTouch;
        public:
        WeatherBaseScreen();

        virtual 
        ~WeatherBaseScreen();

        virtual void 
        updateWeatherStates();

        virtual void
        updateStates();

        virtual void 
        handleTouch(Point*);

        virtual void
        loop();

        virtual void
        draw();

        void 
        drawBase();

        void 
        setTitle(const String&);

        ScreenPointElement _screenPoint;
        TextElement _ver;
        TextElement _title;
        std::unique_ptr<WifiConnectionElement> _wifiConnection;
        std::unique_ptr<TextElement> _location;

        int _startY;
    };

    // Custom setters for displaying weather data
    String maxTemperatureSetter(const Weather& data);
    String minTemperatureSetter(const Weather& data);
    String temperatureSetter(const Weather& data);
    String feelsLikeSetter(const Weather& data);
}