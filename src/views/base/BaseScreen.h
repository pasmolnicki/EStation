#pragma once

#include "../../providers/screenData.h"
#include "../../providers/ErrorProvider.h"
#include "../../components/ScreenElement.h"
#include "../../router/paths.h"
#include "../../lang/config.h"
#include "../../tasks/includes.h"

constexpr uint8_t MENU_SPACING = 15;
constexpr uint16_t BASE_SCREEN_BG = 0x0042;
constexpr uint16_t BASE_FIRST_OPTION_Y = 65;
constexpr uint16_t BASE_OPTION_HEIGHT = 40;

namespace ui
{

/// @brief Base class for the screens (views)
class BaseScreen
{
public:
    typedef std::function<void(ScreenElement*)> iterate_cb;
    typedef std::function<void(ScreenElement*, int)> foreach_cb;

    /// @brief Static method for deleting all elements
    /// @tparam T type of the element
    /// @param items array of elements
    /// @param size size of the array
    template <class T>
    static void _deleteItems(T** items, int size);

    /// @brief Iterates over all elements in the array, and check if the touch event occured
    /// (`eventListener` method is called on each element)
    /// @tparam T type of the element
    /// @param items array of elements
    /// @param size size of the array
    /// @param touch coordinates of the touch event
    /// @return true if the event was handled by any of the elements
    template <class T>
    static bool _eventHandler(T** items, int size, Point* touch);

    /// @brief Iterates over all elements in the array and applies the callback
    template <class T>
    static void _iterate(T** items, int size, std::function<void(T*)> call);

    /// @brief Iterates over all elements in the array and applies the callback
    template <class T>
    static void _foreach(T** items, int size, std::function<void(T*, int)> call);

    /// @brief Draws all elements in the array
    template <class T>
    static void _drawItems(T** items, int size);

    /// @brief Updates the state of all elements in the array (calls `updateState` on each element)
    template <class T>
    static void _updateItemsState(T** items, int size);
    

    BaseScreen();

    virtual
    ~BaseScreen();

    /// @brief Changes `ROUTER_PATH` to given path
    /// @param path
    void
    route(const ui::path&);

    /// @brief Main loop of the screen, listens for touch events and routes them to the elements
    virtual void
    loop();

    /// @brief Draws the screen elements
    virtual
    void draw();
    
    /// @brief Iterates over the elements of the screen and applies given function
    virtual
    void iterate(iterate_cb);

    /// @brief Iterates over the elements of the screen and applies given function
    virtual void
    forEach(foreach_cb);

    virtual void
    preload();

    /// @brief Displays error exception that occured on Core 0 (backend core),
    /// routes to ErrorScreen, if one was thrown.
    void 
    handleError();

    bool _exited;
    ScreenElement** _base_items;
    uint8_t _base_size;
    uint16_t _base_bg;
};

template <class T>
void BaseScreen::_deleteItems(T** items, int size){
    if (!items || size == 0) return;
    for (int i = 0; i < size; i++){
        delete items[i];
    }
    delete [] items;
}

template <class T>
void BaseScreen::_iterate(T** items, int size, std::function<void(T*)> call){
    if (!items || size == 0) return;
    for (int i = 0; i < size; i++){
        call(items[i]);
    }
}

template <class T>
void BaseScreen::_foreach(T** items, int size, std::function<void(T*, int)> call){
    if (!items || size == 0) return;
    for (int i = 0; i < size; i++){
        call(items[i], i);
    }
}

template <class T>
void BaseScreen::_drawItems(T** items, int size){
    if (!items || size == 0) return;
    for (int i = 0; i < size; i++){
        items[i]->draw();
    }
}

template <class T>
bool BaseScreen::_eventHandler(T** items, int size, Point* touch){
    if (!items || size == 0) return false;
    for (int i = 0; i < size; i++){
        if (items[i]->eventListener(touch)){
            return true;
        }
    }
    return false;
}

template <class T>
void BaseScreen::_updateItemsState(T** items, int size){
    if (!items) return;
    for (uint8_t i = 0; i < size; i++){
        items[i]->updateState();
    }
}

} // namespace ui
