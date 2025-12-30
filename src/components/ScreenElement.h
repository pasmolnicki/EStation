#pragma once

#include "../input/TouchButton.h"
#include "../input/TouchScreen.h"

extern TFT_eSPI tft;
extern TouchScreen ts;

namespace ui
{
    class ScreenElement{
        public:
        typedef std::function<void(TouchButton*)> iterate_cb;
        typedef std::function<void(TouchButton*, int)> foreach_cb;

        /// @brief Deletes all items in array
        template <class T>
        static void _deleteItems(T** items, uint8_t size);

        /// @brief Iterates over all items in array and applies the callback
        template <class T>
        static void _iterateItems(T** items, uint8_t size, std::function<void(T*)> call);

        /// @brief Iterates over all items in array and applies the callback
        template <class T>
        static void _foreach(T** items, uint8_t size, std::function<void(T*, int)> call);

        /// @brief Draws the item
        template <class T>
        static void _drawItem(T* item);
        
        ScreenElement();

        virtual
        ~ScreenElement();

        /// @brief Drawing function, by default draws all _buttons
        virtual void
        draw();

        /// @brief Executes when screen is touched
        /// @param touch pixel coordinates of screen touch
        virtual bool
        eventListener(Point* touch);

        /// @brief Updates visuals of component, should be called after 
        /// `setData()` (implemented in `StorageElement`).
        /// By default draw's itself 
        virtual void
        updateState();

        /// @brief Called after `setData()` in StorageElement, should be implemented by child.
        /// Resolves the new data and decides wheter to redraw the component.
        virtual void
        onUpdate();

        virtual
        void iterate(iterate_cb);

        ScreenElement& operator=(const ScreenElement&);

        bool _exited;
        bool _mounted;
        bool _redraw;
        
        TouchButton** _buttons;
        uint8_t _size;
    };

    template <class T>
    void ScreenElement::_deleteItems(T** items, uint8_t size){
        if (!items) return;
        for (uint8_t i = 0; i < size; i++){
            delete items[i];
        }
        delete [] items;
    }

    template <class T>
    void ScreenElement::_iterateItems(T** items, uint8_t size, std::function<void(T*)> call){
        for (uint8_t i = 0; i < size; i++){
            call(items[i]);
        }
    }

    template <class T>
    void ScreenElement::_foreach(T** items, uint8_t size, std::function<void(T*, int)> call){
        for (uint8_t i = 0; i < size; i++){
            call(items[i], i);
        }
    }

    template <class T>
    void ScreenElement::_drawItem(T* item){
        item->draw();
    }
}