#pragma once

#include <Arduino.h>
#include <HTTPClient.h>
#include "../lazyjson/lazyjson.h"
#include <exception>

#include "../data_structures/weather/Weather.h"
#include "../data_structures/weather/Forecast.h"
#include "../lang/localizers/Localizer.h"


typedef struct  {
    String name;
    String country;
    String state;
    int index;

    String search;
    double lat;
    double lon;
} LocationInfo;

class WeatherClient
{
    double  _lat,
            _lon;

public:
    WeatherClient() = default;
    bool init(String city_name, int index = 0);
    std::vector<LocationInfo> getLocations(const String& location);
    LocationInfo getLocation(const String& loc, int index);

    /**
     * @brief Get the current weather
     * @param weather Pointer to the weather object
     * @return true if the request was successful
    */
    bool current(Weather *weather);

    /**
     * @brief Get the forecast for the next 5 days
     * @param forecast Pointer to the forecast object
     * @param timezone Timezone of the location in seconds
     * @return true if the request was successful
    */
    bool forecast(Forecast *forecast, int timezone);
};
