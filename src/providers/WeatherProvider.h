#pragma once

#include "../client/WeatherClient.h"
#include "../data_structures/Props.h"

#include <queue>
#include <numeric>

/// @brief WeatherProvider is a class that provides weather data for given location, it
/// fetches data from OpenWeatherMap API, and provides it to the user
class WeatherProvider
{
    bool _initialized;
    bool _updated;
    WeatherClient _wclient;
    std::vector<LocationInfo> _locations;
    std::vector<LocationInfo> _specLocations;

    bool _fetchLocation;
    String _locationToFetch;

    std::queue<std::pair<String, int>> _qLocations;
    std::function<void(std::vector<LocationInfo>*)> _fetchCall;

public:
    WeatherProvider();

    /// @brief Finds next day in forecast data and stores it in `it`
    /// @param it iterator to start from
    /// @param end end of forecast data
    /// @param data forecast data
    static void _findNextDay(int& it, int end, std::vector<Weather>* data);

    /// @brief Prepares given location to fetch weather data from
    /// @param location 
    void
    setCity(const String&);

    /// @brief Adds callback on successful location data fetch 
    /// @param callback executes both on `fetchLocation()` and `fetchSpecLocation()`, as param this callback
    /// gets either: in `fetchLocation()` vector of searched locations (input based on `prepareLocation(...)`)
    /// or in `fetchSpecLocation()` vector of specific locations (input based on `prepareSpecificLocation(...)`)
    void 
    addFetchCallback(std::function<void(std::vector<LocationInfo>*)>);

    /// @brief Prepares location search, after doing so call `fetchLocation()`
    /// @param location search input
    void 
    prepareLocation(const String& location);

    /// @brief Prepares location fetch
    /// @param location 
    /// @param index 
    void 
    prepareSpecificLocation(const String& location, int index);

    /// @brief Fetches location data, based on given `location` in `prepareLocation(...)`
    void 
    fetchLocation();

    /// @brief Fetches all given specific locations by `prepareSpecificLocation(...)`
    void 
    fetchSpecLocation();

    /// @return Searched locations by `fetchLocation()`
    std::vector<LocationInfo>*
    getLocations();

    /// @return All fetched locations by `fetchSpecLocation()`
    std::vector<LocationInfo>*
    getSpecLocations();

    /// @brief Updates both weather and forecast data
    void 
    update();

    /// @brief Wheter data was successfuly update on last fetch
    bool 
    synced();

    /// @brief Updates weather data
    /// @return wheter was successful
    bool
    weatherUpdate();

    /// @brief Updates forecast data
    /// @return wheater was successful
    bool
    forecastUpdate();

    Weather* 
    weather();

    Forecast*
    forecast();

    void 
    analizeWeatherData();

    void analizeForecast();

    std::vector<Weather>*
    getAnalizedForecast();

    std::vector<Weather>*
    getTodayForecast();
};