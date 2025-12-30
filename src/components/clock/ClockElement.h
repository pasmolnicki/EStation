#pragma once

#include "ClockSectionElement.h"
#include "../../providers/DateTimeProvider.h"

namespace ui
{
    /// @brief Represents visually time, DateTimeProvider should be initialized before
    /// CONSTRUCTING this class
    class ClockElement: public WeatherElement<ClockSectionElement>
    {
    public:
        ClockElement(const Weather& init, int16_t y, uint16_t bg);

        /// @brief Updates internal clock (doesn't draw it)
        virtual void
        onUpdate();
        
        /// @brief Updates visual & internal clock (draws it if necessary), should be called at least every second
        virtual void
        updateState();
    };
    
}