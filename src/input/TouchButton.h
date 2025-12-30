#pragma once

#include <TFT_eSPI.h>

constexpr uint16_t DEFAULT_BTN_COLOR = 0x3166;

class
TouchButton
{

    public:
    /**
     * @brief Virtual class that helps with creating personalized touchscreen button
     * 
     * @param x 
     * @param y 
     * @param width 
     * @param height 
     */
    explicit 
    TouchButton(
        int16_t x, 
        int16_t y, 
        int16_t width, 
        int16_t height
    );

    TouchButton(
        const TouchButton&
    );

    virtual
    ~TouchButton() = default;

    /**
     * @brief This function will be called before on_touch(), after the button area gets touched
     * 
     */
    TouchButton* 
    addOnClickListener(std::function<void(void)>);

    /**
     * @brief Checks wheter the button is touched
     * 
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    bool 
    check(
        int16_t x, 
        int16_t y
    );

    virtual void 
    draw();

    void 
    clear();
    
    virtual void 
    on_touch();
    
    /**
     * @brief Copy operator
     * @warning This does not copy the on_press function
     * @return *this
     */
    TouchButton&
    operator=(const TouchButton& other);

    uint16_t color;
    uint16_t bg;
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
    std::function<void(void)> on_press;
};
