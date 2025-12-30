#include "ErrorScreen.h"

extern ErrorProvider errorProvider;

namespace ui
{
    ErrorScreen::ErrorScreen() {
        Lock l(getSemaphore(tasks::error));

        _base_bg = errorBg;
        _size = 3;

        _items = new TextElement*[_size] {
            new TextElement(160, 20, 
                new TextProps("System exception", placement::middle, _base_bg, useFont(fonts::normal), 0xDD13)),
            new TextElement(30, 60, 
                new TextProps("Code: \n" + errorProvider.code(), placement::start, _base_bg, useFont(fonts::detail))
            ),
            new TextElement(30, 140, 
                new TextProps("Reason: \n" + errorProvider.reason(), placement::start, _base_bg, useFont(fonts::detail)))
        };
        _items[2]->_text->setText(textWrapToNewLine(_items[2]->_text->_props.get(), 50, 60));
    }
}