#include "BaseScreen.h"

extern ErrorProvider errorProvider;

namespace ui
{
    // Constructor & other methods

    BaseScreen::BaseScreen():
    _exited(false), _base_size(0), _base_items(nullptr), _base_bg(BASE_SCREEN_BG) {}

    BaseScreen::~BaseScreen(){
        _deleteItems(_base_items, _base_size);
    }

    void BaseScreen::loop(){
        while(!_exited){
            std::unique_ptr<Point> touch(ts.read_touch());
            if (touch){
                _eventHandler(_base_items, _base_size, touch.get());
            }
        }
    }

    void BaseScreen::route(const ui::path& route){
        this->_exited = true;
        changeRoute(route);
    }

    void BaseScreen::handleError(){
        TryLock lock(getSemaphore(tasks::error), 2);
        if (lock && errorProvider.caught()){
            route(path::ERROR);
        }
    }
    
    void BaseScreen::iterate(iterate_cb call){
        _iterate(_base_items, _base_size, call);
    }

    void BaseScreen::forEach(foreach_cb call){
        _foreach(_base_items, _base_size, call);
    }

    void BaseScreen::draw(){
        _drawItems(_base_items, _base_size);
    }

    void BaseScreen::preload(){
        return;
    }

}