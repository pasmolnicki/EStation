#pragma once

#include <Arduino.h>

namespace ui
{
    enum class path {
        HOME,
        CHOOSE_WIFI,
        INPUT_PASS,
        SETTINGS,
        MANAGE_NETWORKS,
        LOADING,
        LOCALE,
        LOCALIZATION,
        ADD_LOCATION,
        SET_UNIT_SYTEM,
        SLEEP,
        ERROR,
        TODAY_FORECAST,
        NEXT_FORECAST,
        WEATHER_DETAILS,
    };
}

void changeRoute(const ui::path& route);

const ui::path currentRoute();
const ui::path previousRoute();