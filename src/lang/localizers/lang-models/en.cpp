#include "en.h"

// Forward declaration
void localize_en();
String date_format_en(struct tm* info, date_format format);

// Localizer function for English
LocaleData locale_en(){
    return {
        "EN",
        locales::en,
        date_format_en,
        localize_en
    };
}


// Localizer function for English & date formatter
void localize_en(){

    auto locale = getLocale();

    locale->CHOOSE_WIFI_TITLE = "Choose network";
    locale->MANAGE_NETWORKS = "Manage networks";

    locale->SETTINGS_TITLE = "Settings";
    locale->SYSTEM = "Unit system";
    locale->PICK_LANG = "Choose language";
    locale->CURRENT_LANG = "Current language";

    locale->CONNECTING = "Connecting";
    locale->FETCHING_TIME_DATA = "Fetching time data";
    locale->FETCHING_WEATHER_DATA = "Fetching weather data";

    locale->NO_DATA_FOUND = "No data found";
    locale->SEARCH = "Search";
    locale->ADD_NEW_LOCATION = "Add new location";
    locale->NO_SAVED_DATA = "No saved data";
    locale->SAVED_LOCATIONS = "Saved locations";

    locale->INPUT_LOCATION_HERE = "Search location here";
    locale->CLICK_AT_THE_SEARCH_BAR = "Click at the search bar";

    locale->CURRENT_SYSTEM = "Current system";
    locale->SPEED = "Speed";
    locale->FEELS_LIKE = "Feels like";
    locale->TEMP = "Temp.";
    locale->HUMIDITY = "Humidity";
    locale->POP = "Pop";

    locale->METRIC = "Metric";
    locale->IMPERIAL = "Imperial";
    locale->STANDARD = "Standard";

    locale->TODAY = "Today";
    locale->NEXT_3_DAYS = "Next 3 days";
}

String date_format_en(struct tm* info, date_format format){
    constexpr int size = 64;
    char buffer[size];
    switch (format)
    {
    case date_format::full_date:
        // Full date format: Monday 01 Jan 2021
        return strftime(buffer, size, "%A %d %b %Y", info) ? String(buffer) : String("Err");
    case date_format::weekday_short:
        // Short weekday format: Mon
        return strftime(buffer, size, "%a", info) ? String(buffer) : String("Err");
    case date_format::hour_minute:
        // Hour and minute format: 12:00
        return strftime(buffer, size, "%H:%M", info) ? String(buffer) : String("Err");
    }    
}
