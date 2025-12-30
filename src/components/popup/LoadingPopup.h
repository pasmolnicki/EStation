#pragma once

#include "../PosContainer.h"
#include "../state/LoadingElement.h"
#include "../../input/custom_buttons/IconButton.h"

namespace ui
{
    constexpr auto popupColor = 0x18E4;

    class LoadingPopup: public ScreenElement, public PosContainer
    {
    public:
        typedef std::function<bool(uint32_t elapsed)> loop_condition_t;

        LoadingPopup(
            int16_t x,
            int16_t y,
            int16_t w,
            int16_t h,
            uint16_t bg
        );

        void 
        draw();

        void 
        clear();

        /// @brief Updates loading animation, should be called as frequently as possible
        void 
        updateState();

        /// @brief Set the condition for the loop function, 
        /// if the condition returns false, the loop will stop.
        /// @param condition The argument is elapsed time in milliseconds
        void 
        setLoopConidition(loop_condition_t);

        /// @brief Main loop function, it will wait for the condition to be true,
        /// pausing this thread
        void 
        loop();

        
        /// @brief Adds button to this popup, coordinates shouldn't be normalized to screen coordinates, but to 
        /// this popup's coordinates, (Popup ( x = 100, y = 100, w = 100, h = 50) -> Button (0,0) is valid, but Button(101, 51) is out of bound)
        /// @param  button
        /// @return this pointer
        LoadingPopup*
        addButton(TouchButton*);

        std::unique_ptr<LoadingElement> _loading;
        uint16_t _bg;
        loop_condition_t _condition;
    };
}