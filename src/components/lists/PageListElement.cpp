#include "PageListElement.h"


namespace ui
{
  // Constants
  constexpr int size = 35, padding = 5; 

  PageListElement::PageListElement(
    int16_t x, int16_t y,
    int16_t w, int16_t h,
    uint16_t bg,
    int n_items,
    int items_per_page
  ):
    ScreenElement(),
    PosContainer(x, y, w, h),
    max_page(n_items / items_per_page),
    page(0),
    prev_page(0),
    items_per_page(items_per_page)
  {
    // If there are items left, add one more page
    if (n_items % items_per_page != 0){
      max_page++;
    }

    // Custom buttons, provided by the user
    _items.reserve(n_items);

    // Page number button
    constexpr auto width = 2*size;
    _page_btn = new TextIconButton(
      x + w/2 - width/2, y + h - size,
      width, width, bg, new TextProps(getPageString(page), placement::middle, bg)
    );

    _size = 3;
    // Pagination buttons
    _buttons = new TouchButton*[_size]{

      (new IconButton( // Left button
        x + w/2 - size - width/2 - padding, y + h - size,
        new IconProps(new GoBackIcon(), size, bg, DEFAULT_BTN_COLOR)
      ))->addOnClickListener([this](){
        prev_page = page;
        page = std::max(0, page - 1);
      }),

      _page_btn, // Page number (middle button)

      (new IconButton( // Right button
        x + w/2 + width/2 + padding, y + h - size,
        new IconProps(new GoForwardIcon(), size, bg, DEFAULT_BTN_COLOR)
      ))->addOnClickListener([this](){
        prev_page = page;
        page = std::min(max_page - 1, page + 1);
      })
    };
  }

  PageListElement::~PageListElement(){
    for(int i = 0; i < _items.size(); i++){
      delete _items[i];
    }
  }

  void PageListElement::add(TouchButton* btn){
    _items.push_back(btn);
    if(_items.size() >= items_per_page * max_page){
      max_page++;
    }
  }

  void PageListElement::del(int i){
    delete _items[i];
    _items.erase(_items.begin() + i);

    max_page = _items.size() / items_per_page;
    max_page += _items.size() % items_per_page != 0 ? 1 : 0;

    updateItems();
    _redraw = true;
  }

  int PageListElement::getStartIndex(int p){
    return p * items_per_page;
  }

  int PageListElement::getEndIndex(int p){
    return std::min((p + 1) * items_per_page, (int)_items.size());
  }

  int PageListElement::getItemHeight(){
    return (height() - size) / items_per_page - padding;
  }

  int PageListElement::getItemY(int i){
    return y() + i % items_per_page * (getItemHeight() + padding);
  }

  String PageListElement::getPageString(int p){
    return String(p + 1) + "/" + String(max_page);
  }

  void PageListElement::updateItems(){
    if (_items.empty()){
      return;
    }

    int item_height = getItemHeight();

    for(int p = 0; p < max_page; p++){
      for(int i = 0; i < items_per_page; i++){
        int index = p * items_per_page + i;
        if(index < _items.size()){
          _items[index]->x = x();
          _items[index]->y = getItemY(index);
          _items[index]->width = width();
          _items[index]->height = item_height;
        }
      }
    }
  }

  int PageListElement::getTouchedIndex(){
    return touched_index;
  }

  bool PageListElement::eventListener(Point* touch){
    touched_index = -1;
    if(_buttons[0]->check(touch->x, touch->y) || _buttons[2]->check(touch->x, touch->y)){
      _redraw = true;
      _page_btn->setText(getPageString(page));
      return false;
    }

    const auto end = getEndIndex(page);
    for (int i = getStartIndex(page); i < end; i++){
      if (_items[i]->check(touch->x, touch->y)){
        touched_index = i;
        return true;
      }
    }
    return false;
  }

  void PageListElement::updateState(){
    _redraw &= prev_page != page;
    if(!_redraw) return;

    // If there is less items than on the previous screen, we must clear the items
    const auto end_clear = getEndIndex(prev_page);
    auto start_clear = getStartIndex(prev_page) + (getEndIndex(page) - getStartIndex(page));
    for(int i = start_clear; i < end_clear; i++){
      _items[i]->clear();
    }
    draw();
    _redraw = false;
  }

  void PageListElement::draw(){
    const auto end = getEndIndex(page);   
    for (int i = getStartIndex(page); i < end; i++){
      _items[i]->draw();
    }
    ScreenElement::iterate(_drawItem<TouchButton>);
  }
}