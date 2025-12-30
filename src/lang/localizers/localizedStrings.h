#pragma once

#include <Arduino.h>

struct LocalizedStrings{
  // Choose wifi title - "Choose network"
  String CHOOSE_WIFI_TITLE;
  // Settings title (in settings screen)
  String SETTINGS_TITLE;
  // Manage networks (used as title in manager screen)
  String MANAGE_NETWORKS;
  // Choose language (used in settings screen)
  String PICK_LANG;
  // System (used in settings screen, as a button to get into unit system screen)
  String SYSTEM;
  // Current language
  String CURRENT_LANG;
  // Feels like (temperature)
  String FEELS_LIKE;
  // Connecting (to network)
  String CONNECTING;
  // Fetching time data (as a loading message)
  String FETCHING_TIME_DATA;
  // Fetching weather data (as a loading message)
  String FETCHING_WEATHER_DATA;
  // No data found (used in AddLocationScreen when no data is found)
  String NO_DATA_FOUND;
  // Search (used in search bar placeholder)
  String SEARCH;
  // Add new location (used in location screen)
  String ADD_NEW_LOCATION;
  // No saved data (used in location screen)
  String NO_SAVED_DATA;
  // Saved locations (use in location screen, as subtitle, 
  // showing number of saved locations)
  String SAVED_LOCATIONS;
  // Search location here (used in AddLocationScreen)
  String INPUT_LOCATION_HERE;
  // Click at the search bar (used in AddLocationScreen as a subtitle)
  String CLICK_AT_THE_SEARCH_BAR;
  // Current system (used in UnitSystemScreen as a title, indicating current system - "Current system: Metric")
  String CURRENT_SYSTEM;
  // Used for wind speed
  String SPEED;
  // Temperature - use a short name; temp
  String TEMP;
  // Humidity (used in legend, as a short name for humidity)
  String HUMIDITY;
  // Probability of precipitation (pop) (used in legend, as a short name for precipitation)
  String POP;
  // Unit system names
  String METRIC, IMPERIAL, STANDARD;
  // Date strings
  String TODAY, NEXT_3_DAYS;
};

extern LocalizedStrings locale;

/**
 * @brief Get the locale object, it has current locale translations
 * @return LocalizedStrings* - pointer to the locale object, do not delete it
 */
constexpr LocalizedStrings* getLocale(){
  return (&locale);
}