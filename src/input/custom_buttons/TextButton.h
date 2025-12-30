#pragma once

#include "../../data_structures/Props.h"
#include "../../output/button.h"
#include "../TouchButton.h"

extern TFT_eSPI tft;

extern char* NORMAL_FONT;

namespace ui
{

    class TextButton: public TouchButton
    {
        
        public:
        TextButton(
            uint16_t x, uint16_t y,
            TextProps* _props = nullptr
        );

        TextButton(
            const TextButton& other
        );

        TextButton& operator=(const TextButton& other);

        virtual void
        draw();

        /**
         * @brief Set the Props object, resets the current props
         */
        TextButton*
        setProps(TextProps* props);

        /**
         * @brief Erase the text from the screen
         */
        void
        eraseText();

        /**
         * @brief Set the text of the button
         * @param text The text to set
         */
        void setText(const String&);

        /**
         * @brief Set the width and height of the button (based on the text and font size)
         */
        void setWidthHeight();

        std::unique_ptr<TextProps> _props;
    };
}