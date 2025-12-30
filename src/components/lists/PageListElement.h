#pragma once


#include "../buttons/TextIconElement.h"
#include "../PosContainer.h"
#include "../buttons/IconButtonElement.h"

namespace ui
{
  class PageListElement: public ScreenElement, public PosContainer{
    public:    
    PageListElement(
      int16_t x, int16_t y,
      int16_t w, int16_t h,
      uint16_t bg,
      int n_items = 8,
      int items_per_page = 4
    );

    virtual
    ~PageListElement();

    void
    add(
      TouchButton* btn
    );

    void
    del(
      int index
    );

    int getTouchedIndex();

    virtual bool 
    eventListener(Point* touch);

    virtual void
    draw();

    virtual void
    updateState();

    int getStartIndex(int p);
    int getEndIndex(int p);
    int getItemHeight();
    int getItemY(int i);

    int touched_index;
    int max_page;
    int page;
    int prev_page;
    int items_per_page;
    std::vector<TouchButton*> _items;
    TextIconButton *_page_btn;

    String getPageString(int p);

    void updateItems();
  };
}