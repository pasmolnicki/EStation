#include "DateTimeProvider.h"

extern Localizer localizer;
auto dateProvider = DateTimeProvider();

DateTimeProvider::DateTimeProvider(): _update(true), _lastTimeUpdate(0), _initialized(false) {}

void DateTimeProvider::init(uint32_t timezone){
    configTime(timezone, 0, "pool.ntp.org");
    fetchTime();
    _initialized = !_update;
}

struct tm* DateTimeProvider::getTimeinfo(){
    return &_timeinfo;
}

bool DateTimeProvider::synced(){
    return !_update;
}

bool DateTimeProvider::inited(){
    return _initialized;
}

void DateTimeProvider::fetchTime(){
    if (!_update){
        return;
    }
    _update = !getLocalTime(&_timeinfo);
}

String DateTimeProvider::formatDate(const date_format& format){
    return localizer.getDateFormatter()(&_timeinfo, format);
}

String DateTimeProvider::formatTime(const char* format){
    char buffer[32];
    auto size = strftime(buffer, 32, format, &_timeinfo);
    return size != 0 ? String(buffer) : String("Err");
}


bool DateTimeProvider::loop(){
    return millis() - _lastTimeUpdate < 1000 ? false : addSecond();
}

bool DateTimeProvider::addSecond(){
    _lastTimeUpdate = millis();

    int prev_day = _timeinfo.tm_mday;
    int prev_month = _timeinfo.tm_mon;
    int prev_year = _timeinfo.tm_year;

    auto time = mktime(&_timeinfo);
    time += 1;
    _timeinfo = *localtime(&time);

    if (_timeinfo.tm_min % CACHE_UPDATE_TIME == 0){
        _update = true;
        fetchTime();
        return false;
    }

    return 
        (prev_day != _timeinfo.tm_mday) || 
        (prev_month != _timeinfo.tm_mon) || 
        (prev_year != _timeinfo.tm_year);
}

