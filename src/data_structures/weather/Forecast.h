#pragma once


#include "Weather.h"
#include <vector>

constexpr auto NUMBER_OF_HOURS_TO_FORECAST = 40;

class Forecast
{
    public:
    Forecast() {
        this->forecast.assign(NUMBER_OF_HOURS_TO_FORECAST, Weather());
    }
    std::vector<Weather> forecast;
};
