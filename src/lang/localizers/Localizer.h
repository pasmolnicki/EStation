#pragma once

#include "lang-models/pl.h"
#include "lang-models/en.h"

/*
======================================================================================
#                       HOW TO ADD NEW LANGUAGE SUPPORT                           # 
======================================================================================

To add new language:

    1. Go to locale_data.h (same directory as this file) and add new locale to the `locales` enum (ex. `fr`) 
    and update `NUMBER_OF_LOCALIZERS` macro (ex. `#define NUMBER_OF_LOCALIZERS 3`)

    2. Create new header & cpp files in lang-models/ with the language name (ex. `fr.h` and `fr.cpp`)

    3. In the header file, (ex. `fr.h`):
        - Guard the file with `#pragma once`
        - Include `locale_data.h` (#include "../locale_data.h")
        - Create a function that returns `LocaleData` struct (ex. `LocaleData locale_fr();`)

    4. In the cpp file (ex. `fr.cpp`):
        - Include the header file (ex. `#include "fr.h"`)
        - Implement the function that returns `LocaleData` struct 
            (ex. `LocaleData locale_fr(){
                return {
                    "FR"
                    locales::fr,
                    [](struct tm* time, date_format format){
                        // Implement the date formatter here
                    },
                    localize_fr // The localizer function
                };
            }`)
        - Implement other functionalities for the LocaleData struct (date_formatter, 
            localizer function (ex. `localize_fr`), see for example `lang-models/en.cpp`)
    
    5. In `Localizer.cpp`, update the `localesData` array with the new locale initializer function
        const LocaleData Localizer::localesData[NUMBER_OF_LOCALIZERS] = {
            ...,
            locale_fr(), // French
        };
        
That's it! You have added a new language support to the project.
You can see the new language in the `Choose language` screen.

If you want to add custom Icon, go to `src/output/icons/flags/flags.h` and follow the instructions there.
*/

enum class unitSystem {
    metric = 0,
    imperial,
    standard
};

enum class unit{
    velocity,
    temperature,
};

class Localizer
{
public:
    static const LocaleData localesData[NUMBER_OF_LOCALIZERS];

    Localizer();    
    
    /**
     * @brief Set given locale, updates the `locale` object accordingly
     */
    void setLocalizer(const locales&);

    /**
     * @brief Get the name of the current localizer
     * 
     * @return const String& 
     */
    const String& localizerName();

    /**
     * @brief Get the current locale enum
     * 
     * @return const locales& 
     */
    const locales& current();
    
    /**
     * @brief Get all available localizer names
     * 
     * @return String*, do not delete, size = NUMBER_OF_LOCALIZERS
     */
    String* getLocalizerNames();

    /**
     * @brief Get all available locales
     * 
     * @return locales*, do not delete, size = NUMBER_OF_LOCALIZERS
     */
    locales* getLocales();

    /**
     * @brief Get the date formatter function, based on the current locale
     * @return date_formatter
     */
    date_formatter
    getDateFormatter();

    /**
     * @brief Set the unit system
     * 
     * @param unitsys The unit system to set
     */
    void setUnitSystem(const unitSystem&);

    /**
     * @brief Get the current unit system
     * 
     * @return const unitSystem& 
     */
    const unitSystem& getUnitSystem();

    /**
     * @brief Get the verbose unit name
     * 
     * @return const String& 
     */
    String getUnit(const unit&);

    /**
     * @brief Get the unit system name (in English)
     * 
     * @return const String& 
     */
    String getUnitSytemName();

    /**
     * @brief Get the unit system verbose name, that is 
     * based on the current locale
     * 
     * @return String 
     */
    String getUnitSystemVerboseName();

private:
    int _locale_index;
    
    String* _names;
    locales* _locales;

    String _verboseSysName;
    String _unitSysName;
    unitSystem _sysCurrent;
};