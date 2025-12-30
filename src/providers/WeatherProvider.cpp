#include "WeatherProvider.h"

auto currentWeather = Weather();
auto forecastedWeather = Forecast();
auto analizedForecast = std::vector<Weather>();
auto todayForecast = std::vector<Weather>(3, Weather());

extern auto wProvider = WeatherProvider();

extern LocationProps locProps;

void doNothing(std::vector<LocationInfo>*){
    return;
}

WeatherProvider::WeatherProvider(): 
_updated(false), _initialized(false), 
_fetchCall(doNothing), _fetchLocation(false) {}

void WeatherProvider::setCity(const String& cityname){
    _initialized = _wclient.init(cityname);
}

void WeatherProvider::update(){
    if (!_initialized){
        setCity(locProps.location);
    }
    _updated = _wclient.current(&currentWeather) && _wclient.forecast(&forecastedWeather, currentWeather._timezone);
    if (!_updated){
        return;
    }
    analizeWeatherData();
}

void WeatherProvider::
addFetchCallback(std::function<void(std::vector<LocationInfo>*)> callback){
    _fetchCall = callback;
}

void WeatherProvider::
prepareLocation(const String& loc){
    _locationToFetch = loc;
    _fetchLocation = true;
}

void WeatherProvider::
prepareSpecificLocation(const String& location, int index){
    _qLocations.push(std::make_pair(location, index));
}

void WeatherProvider::
fetchLocation(){
    if (!_fetchLocation){
        return;
    }
    _locations = _wclient.getLocations(_locationToFetch);
    _fetchCall(getLocations());
    _fetchLocation = false;
}

void WeatherProvider::
fetchSpecLocation(){
    if (_qLocations.empty()){
        return;
    }
    _specLocations.clear();

    while(!_qLocations.empty()){
        _specLocations.push_back(
            _wclient.getLocation(_qLocations.front().first, _qLocations.front().second)
        );
        _qLocations.pop();
    }
    _fetchCall(&_specLocations);
}

std::vector<LocationInfo>* WeatherProvider::
getLocations(){
    return &_locations;
}

std::vector<LocationInfo>* WeatherProvider::
getSpecLocations(){
    return &_specLocations;
}

bool WeatherProvider::synced(){
    return _updated;
}

bool WeatherProvider::weatherUpdate(){
    return _wclient.current(&currentWeather);
}

bool WeatherProvider::forecastUpdate(){
    return _wclient.forecast(&forecastedWeather, currentWeather._timezone);
}

Weather* WeatherProvider::weather(){
    return &currentWeather;
}

Forecast* WeatherProvider::forecast(){
    return &forecastedWeather;
}

void WeatherProvider::
analizeWeatherData(){
    if (forecastedWeather.forecast.empty()){
        return;
    }

    todayForecast = std::vector<Weather>(forecastedWeather.forecast.begin(), forecastedWeather.forecast.begin() + 3);
}

void WeatherProvider::_findNextDay(int& it, int end, std::vector<Weather>* _forecast){
    auto day_now = localtime((time_t*)&(_forecast->at(it)._dt))->tm_mday;

    while(it < end){
        if (localtime((time_t*)&(_forecast->at(it)._dt))->tm_mday != day_now){
            break;
        }
        it++;
    }
}

void WeatherProvider::analizeForecast(){
    if (forecastedWeather.forecast.empty()){
        return;
    }

    constexpr int days = 3;

    analizedForecast.clear();
    analizedForecast.reserve(days);

    auto _forecast = &forecast()->forecast;
    int it = 0;
    int end = _forecast->size();
    int next = 0;

    // Find when the forecast starts (when next day starts)
    _findNextDay(it, end, _forecast);

    int i = 0;
    while(next < end && i < days){
        
        _findNextDay(next, end, _forecast);

        if (next - it == 0){
            continue;
        }

        if (next >= end){
            break;
        }

        auto avg = Weather();
        for (int j = it; j < next; j++){
            avg._temp += _forecast->at(j)._temp;
            avg._humidity += _forecast->at(j)._humidity;
            avg._pressure += _forecast->at(j)._pressure;
            avg._wind_speed += _forecast->at(j)._wind_speed;
            avg._pop += _forecast->at(j)._pop;
        }

        auto minmax = std::minmax_element(_forecast->begin() + it, _forecast->begin() + next, [](
            const Weather& a, const Weather& b
        ){
            return a._temp < b._temp;
        });

        auto diff = next - it;
        avg._temp /= diff;
        avg._humidity /= diff;
        avg._pressure /= diff;
        avg._wind_speed /= diff;
        avg._pop /= diff;
        avg._min_temp = minmax.first->_temp;
        avg._max_temp = minmax.second->_temp;
        
        avg._dt = _forecast->at(it + diff/2)._dt;
        avg._icon = _forecast->at(it + diff/2)._icon;
        analizedForecast.push_back(avg);
        it = next;
        i++;
    }
}

std::vector<Weather>* WeatherProvider::
getAnalizedForecast(){
    return &analizedForecast;
}

std::vector<Weather>* WeatherProvider::
getTodayForecast(){
    return &todayForecast;
}