#pragma once

#include "../WeatherElement.h"
#include "../../../input/custom_buttons/TextButton.h"

namespace ui
{
    class TextWeatherElement : public WeatherElement<TextButton>
    {
        uint16_t _lenght;
    public:
        
        typedef std::function<String(const Weather&)> setter_type;

        TextWeatherElement(
            const Weather&,
            int16_t x,
            int16_t y,
            TextProps* Props = nullptr
        );

        /**
         * @brief Update the state of the element, if the element's value was changed, it redraws the element
         */
        virtual void 
        updateState();

        /**
         * @brief Set the text of the element
         * 
         * @param str The text to set
         */
        virtual void
        setText(const String&);
        
        /**
         * @brief Update the element's state, this function is called to refresh the element's value
         */
        virtual void
        onUpdate();

        /**
         * @brief Set the setter function, this function is called to set the text of the element
         * 
         * @param setter The setter function
         * @return this
         */
        TextWeatherElement* setter(setter_type);

        /**
         * @brief Clear the element from the screen
         */
        void 
        clear();

        /**
         * @brief Draw the element to the sprite
         */
        void 
        drawToSprite(
            uint16_t x,
            uint16_t y, 
            TFT_eSprite* sprite
        );

    protected:
        String _prev;
        String _current;
        setter_type _setter;
    };
}
