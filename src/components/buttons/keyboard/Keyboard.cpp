#include "Keyboard.h"

namespace ui
{

    KeyboardButton** loadFromLayout(const int& size, const String* layoutChars, uint16_t bg){
        auto layout = new KeyboardButton*[size];

        int16_t x = startX, y = startY;

        auto setProps = [&](int i){
            return new TextProps(layoutChars[i], placement::middle);
        };
        auto w = width;
        for (int i=0; i < size; i++){
            if (i == size - 1){
                w = spaceWidth;
            }
            layout[i] = new KeyboardButton(x, y, w, height, bg, setProps(i));
            buildQwertyEnLayout(x, y, i);
        }
        return layout;
    }

    constexpr auto NUMBER_OF_LAYOUTS = 3;
    constexpr auto CHAR_LAYOUT = 0;
    constexpr auto UPPER_CHAR_LAYOUT = 1;
    constexpr auto SPECIAL_LAYOUT = 2;

    Keyboard::Keyboard(
        uint16_t bg,
        const String& init
    ): DataElement(init), _currentLayout(0), _bg(bg),
    _delete(new IconButton(320 - delMarginRight - delWidth, lastRowY - height - marginTop, new IconProps(new DeleteIcon(), height, bg))),
    _capsLock(new TextIconButton(2, lastRowY, 80, height, bg , nullptr, new IconProps(new CapsLockIcon(), 32, bg, TFT_LIGHTGREY, placement::middle))),
    _changeMode(new KeyboardButton(160 + spaceWidth/2 + 2, lastRowY, 80, height, bg, new TextProps("123", placement::middle))) {
        _size = qwertySize;

        _keypad = new KeyboardButton**[NUMBER_OF_LAYOUTS]{
            loadFromLayout(_size, qwertyEn, bg),
            loadFromLayout(_size, qwertyEnCapitalized, bg),
            loadFromLayout(_size, qwertyEnSpecialChar, bg),
        };
        _capsLock->addOnClickListener([&](){
            this->_currentLayout = this->_currentLayout == 0 ? 1 : 0;
            this->draw();
        });
        _changeMode->addOnClickListener([&](){
            if (this->_currentLayout < 2){
                this->_capsLock->clear();
                this->_currentLayout = 2;
                _changeMode->_props->text = "ABC";
            }
            else{
                this->_currentLayout = 0;
                _changeMode->_props->text = "123";
            }
            this->draw();
        });
        
    }   

    Keyboard::~Keyboard(){
        for (int i=0; i < NUMBER_OF_LAYOUTS; i++){
            _currentLayout = i;
            iterate([](KeyboardButton* btn){delete btn;});
            delete [] _keypad[i];
        }
        delete [] _keypad;
    }
    
    void Keyboard::draw(){
        iterate([&](KeyboardButton* btn){
            btn->draw();
        });
        _delete->draw();
        _changeMode->draw();
        if (_currentLayout != SPECIAL_LAYOUT){
            _capsLock->draw();
        }
    }

    void Keyboard::clear(){
        tft.fillRect(0, startY, 320, 240 - startY, _bg);
    }

    bool Keyboard::eventListener(Point* touch){
        auto touched = false;
        iterate([&](KeyboardButton* btn){
            if(btn->check(touch->x, touch->y)){
                this->_onClick(btn->_props->text);
                touched = true;
            }
        });
        if (_currentLayout != SPECIAL_LAYOUT){
            touched |= _capsLock->check(touch->x, touch->y);
        }
        touched |= _delete->check(touch->x, touch->y);
        touched |= _changeMode->check(touch->x, touch->y);
        return touched;
    }

    void Keyboard::addOnClickEvent(std::function<void(const String&)> call){
        _onClick = call;
    }

    void Keyboard::addOnDeleteEvent(std::function<void(void)> call){
        _delete->addOnClickListener(call);
    }

    void Keyboard::
    iterate(std::function<void(KeyboardButton*)> call){
        ScreenElement::_iterateItems(_keypad[_currentLayout], _size, call);
    }
}