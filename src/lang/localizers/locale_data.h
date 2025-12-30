#pragma once

#include <Arduino.h>
#include <functional>
#include <time.h>

#include "localizedStrings.h"

enum class date_format{
    full_date,
    weekday_short,
    hour_minute,
};

typedef std::function<String(struct tm*, date_format)> date_formatter;


/*
=============================================================================
#                   USER CUSTOM LOCALE SETUP STARTS HERE                    #
=============================================================================

This is where you can define the localizers for the different languages
If you want to add a new language, follow instructions in Localizer.h.


Here you can change the number of localizers `NUMBER_OF_LOCALIZERS`
And also add new locales to the `locales` enum.

*/

// Number of localizers
#define NUMBER_OF_LOCALIZERS 2

// Available locales
enum class locales {
    pl = 0,
    en
};


// Locale initializer struct
struct LocaleData{
    const char* name;
    locales locale;
    date_formatter formatter;
    void(*localizer)();
};