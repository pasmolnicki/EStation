#pragma once

#include <Arduino.h>

class Weather
{
    public:

    String _main,
            _icon;
    double _temp,
            _feels_like,
            _wind_speed,
            _pop,
            _min_temp,
            _max_temp;      
    uint8_t _humidity;
    uint16_t _pressure;
    uint32_t _sunrise,
            _sunset,
            _dt,
            _timezone;

    
    Weather* main(String main);
    Weather* icon(String icon);
    Weather* temp(double temp);
    Weather* wind_speed(double wind_speed);
    Weather* feels_like(double feels_like);
    Weather* humidity(uint8_t humidity);
    Weather* pressure(uint16_t pressure);
    Weather* sunrise(uint32_t sunrise);
    Weather* sunset(uint32_t sunset);
    Weather* dt(uint32_t dt);
    Weather* pop(double pop);
    Weather* timezone(uint32_t timezone);

    // Additional
    Weather* min_temp(double min_temp);
    Weather* max_temp(double max_temp);

    const Weather& operator=(const Weather& other){
        return *main(other._main)
        ->icon(other._icon)
        ->temp(other._temp)
        ->wind_speed(other._wind_speed)
        ->feels_like(other._feels_like)
        ->humidity(other._humidity)
        ->pressure(other._pressure)
        ->sunrise(other._sunrise)
        ->sunset(other._sunset)
        ->dt(other._dt)
        ->pop(other._pop)
        ->timezone(other._timezone)
        ->min_temp(other._min_temp)
        ->max_temp(other._max_temp);
    }
};
