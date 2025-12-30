#include "Localizer.h"

String TEMP_UNIT = "C";
String VELOCITY_UNIT = "m/s";


/*

=========================================================
#           THIS IS WHERE YOU CAN ADD NEW LOCALES       #
=========================================================

Follow instructions in `Localizer.h` to add new locale support.

To add new locale, after implementing the locale in the `lang-models` folder,
simply add new line to the `localesData` array with the locale initializer function.
for example:

    const LocaleData Localizer::localesData[NUMBER_OF_LOCALIZERS] = {
        locale_en(), // English
        locale_pl(), // Polish
        locale_fr(), // French
    };

This will add support for the new locale (If other parts of the code are properly implemented)
*/
const LocaleData Localizer::localesData[NUMBER_OF_LOCALIZERS] = {
    locale_en(), // English
    locale_pl(), // Polish
};


Localizer localizer = Localizer();

Localizer::Localizer()
{
    setLocalizer(locales::en);
    setUnitSystem(unitSystem::metric);
    _names = new String [NUMBER_OF_LOCALIZERS];
    _locales = new locales [NUMBER_OF_LOCALIZERS];

    for (int i = 0; i < NUMBER_OF_LOCALIZERS; i++){
        _names[i] = localesData[i].name;
        _locales[i] = localesData[i].locale;
    }
}

void Localizer::
setLocalizer(const locales& locale){
    for (int i = 0; i < NUMBER_OF_LOCALIZERS; i++){
        if (localesData[i].locale == locale){
            localesData[i].localizer();
            _locale_index = i;
            break;
        }
    }
    setUnitSystem(_sysCurrent); // Update verbose system name
}

void Localizer::
setUnitSystem(const unitSystem& unitsys){
    _sysCurrent = unitsys;
    switch (unitsys)
    {
    case unitSystem::metric:
        TEMP_UNIT = "`C";
        VELOCITY_UNIT = "m/s";
        _unitSysName = "metric";
        _verboseSysName = getLocale()->METRIC;
        break;
    
    case unitSystem::imperial:
        TEMP_UNIT = "`F";
        VELOCITY_UNIT = "mil/h";
        _unitSysName = "imperial";
        _verboseSysName = getLocale()->IMPERIAL;
        break;
    default:
        TEMP_UNIT = "K";
        VELOCITY_UNIT = "m/s";
        _unitSysName = "standard";
        _verboseSysName = getLocale()->STANDARD;
    }
}

const unitSystem& Localizer::getUnitSystem(){
    return _sysCurrent;
}

String Localizer::getUnitSystemVerboseName(){
    return _verboseSysName;
}

String Localizer::getUnitSytemName(){
    return _unitSysName;
}

String Localizer::getUnit(const unit& uni){
    switch (uni)
    {
    case unit::temperature:
        return TEMP_UNIT;
    default:
        return VELOCITY_UNIT;
    }
}

const locales& Localizer::current(){
    return _locales[_locale_index];
}

const String& Localizer::localizerName(){
    return _names[_locale_index];
}

String*
Localizer::getLocalizerNames(){
    return _names;
}

locales*
Localizer::getLocales(){
    return _locales;
}

date_formatter
Localizer::getDateFormatter() {
    return localesData[_locale_index].formatter;
}
