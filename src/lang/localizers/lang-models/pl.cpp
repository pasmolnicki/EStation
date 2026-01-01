#include "pl.h"

// extern bool USE_CUSTOM_FONT;

// Forward declarations
void localize_pl();
String date_format_pl(struct tm* info, date_format format);

// Localizer function for Polish
LocaleData locale_pl(){
    return {
        "PL",
        locales::pl,
        date_format_pl,
        localize_pl
    };
}

// Actual implementation of the localizer & date formatter
void localize_pl(){

    auto locale = getLocale();

    // Default ascii characters
    locale->CHOOSE_WIFI_TITLE = "Wybierz siec";
    locale->PICK_LANG = "Wybierz jezyk";
    locale->CURRENT_LANG = "Aktualny jezyk";
    locale->NEXT_3_DAYS = "Nastepne 3 dni";
    locale->HUMIDITY = "Wilgotnosc";
    locale->MANAGE_NETWORKS = "Zarzadzaj sieciami";

    // If custom font is used, add special characters
    // if (USE_CUSTOM_FONT){
    //     locale->CHOOSE_WIFI_TITLE = "Wybierz sieć";
    //     locale->PICK_LANG = "Wybierz język";
    //     locale->CURRENT_LANG = "Aktualny język";
    //     locale->NEXT_3_DAYS = "Następne 3 dni";
    //     locale->HUMIDITY = "Wilgotność";
    // }

    locale->SETTINGS_TITLE = "Ustawienia";
    locale->SYSTEM = "Jednostki";

    locale->FEELS_LIKE = "Odczuwalna";

    locale->CONNECTING = "Podpinanie do sieci";
    locale->FETCHING_TIME_DATA = "Pobieranie danych o czasie";
    locale->FETCHING_WEATHER_DATA = "Pobieranie danych o pogodzie";

    locale->NO_DATA_FOUND = "Brak danych";
    locale->SEARCH = "Wyszukaj";
    locale->ADD_NEW_LOCATION = "Dodaj nowe miejsce";
    locale->NO_SAVED_DATA = "Brak danych";
    locale->SAVED_LOCATIONS = "Zapisane miejsca";

    locale->INPUT_LOCATION_HERE = "Wyszukaj tutaj miejsca";
    locale->CLICK_AT_THE_SEARCH_BAR = "Kliknij pasek wyszukiwania";

    locale->CURRENT_SYSTEM = "Aktualny system";
    locale->SPEED = "Szyb.";
    locale->TEMP = "Temp.";
    locale->POP = "Prawd. opadu";

    locale->METRIC = "Metryczny";
    locale->IMPERIAL = "Imperialny";
    locale->STANDARD = "Standardowy";

    locale->TODAY = "Dzisiaj";
}

String date_format_pl(struct tm* info, date_format format){
    const String weekdays [] = {
        "nd", "pon", "wt", "sr", "czw", "pt", "sob"
    };

    const String months[] = {
        "Sty", "Lut", "Mar", "Kwi", "Maj", "Cze", "Lip", "Sie", "Wrz", "Paz", "Lis", "Gru"
    };

    String ret;

    switch(format){
        case date_format::full_date:
            ret = weekdays[info->tm_wday] + " ";
            ret += info->tm_mday > 9 ? String(info->tm_mday) : "0" + String(info->tm_mday);
            ret += " " + months[info->tm_mon];
            return ret + " " + String(1900 + info->tm_year);
        case date_format::weekday_short:
            return weekdays[info->tm_wday];
        case date_format::hour_minute: {
            char buffer[64];
            return strftime(buffer, 64, "%H:%M", info) ? String(buffer) : String("Err");
        }
        default:
            return String("");
    }
}