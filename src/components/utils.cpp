#include "utils.h"


namespace ui
{

/**
 * @brief Waits until the element is closed, by pressing the close button
 * @param element Pointer to the element to be closed
 */
void keepElementUntilClose(ui::ScreenElement* element)
{
    element->draw();
    bool closed = false;
    while(!closed) {
        std::unique_ptr<Point> touch(ts.read_touch());
        if (touch && element->eventListener(touch.get())){
            closed = true;
        }
    }
}

/**
 * @brief Creates a basic popup with as a card, waits util close button is pressed, 
 * can show 2 line message
 */
void makePopup(
    String header, String content,
    uint16_t width, uint16_t height, 
    uint16_t bg, uint16_t color,
    uint16_t header_color
){
    std::unique_ptr<ui::CardElement> popup(new ui::CardElement(
        160 - width/2, 120 - height/2, width, height, color, bg,
        new TextProps(header, placement::middle, color, useFont(fonts::normal), header_color),
        new TextProps(content, placement::middle, color, useFont(fonts::detail))
    ));

    popup->addIcon(
        new IconProps(new ui::ExitIcon(), 32, color), nullptr
    );

    keepElementUntilClose(popup.get());
    popup->clear();
}

/**
 * @brief Creates a basic error page, waits util close button is pressed
 * @warning The screen is not cleared after the screen is closed
 * @param reason Reason for the error
 * @param content Content of the error, excpects multiline message, automatically wrapped
 */
void makeErrorPage(
    String reason, String content
)
{
    constexpr uint16_t errorBg = 0x1041, lightRed = 0xDD13;
    tft.fillScreen(errorBg);

    std::unique_ptr<ui::TextElement[]> text_elems(new ui::TextElement[2]{
        ui::TextElement(160, 20, 
            new TextProps(reason, placement::middle, errorBg, useFont(fonts::normal), lightRed)),
        ui::TextElement(30, 60, 
            new TextProps(content, placement::start, errorBg, useFont(fonts::detail)))
    });

    // Wrap the text to new line
    text_elems[1].setText(textWrapToNewLine(text_elems[1]._text->_props.get(), 50, 60));

    // Create a close button
    std::unique_ptr<ui::IconButtonElement> close_button(new ui::IconButtonElement(
        320 - 10 - 32, 10, new IconProps(new ui::ExitIcon(), 32, errorBg)
    ));

    // Draw the close button
    text_elems[0].draw();
    text_elems[1].draw();
    keepElementUntilClose(close_button.get());
}


} // namespace ui