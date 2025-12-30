#include "WifiManagerScreen.h"

extern MemoryProvider memoryProvider;

namespace ui
{
  void handleClick(){
    WifiManagerScreen::_handleDelete = true;
  }

  bool WifiManagerScreen::_handleDelete = false;

  WifiManagerScreen::WifiManagerScreen() {

    _list = new PageListElement(
      20, 45, 320 - 20 * 2, 190, 
      BASE_SCREEN_BG, memoryProvider.getNetworks()->size()
    );

    auto networks = memoryProvider.getNetworks();
    for (int i = 0; i < networks->size(); i++){
      _list->add(
        (new TextIconButton(0, _list->getItemY(i), _list->width(), _list->getItemHeight(), _base_bg,
          new TextProps((*networks)[i].first),
          new IconProps(new TrashIcon(), 30, DEFAULT_BTN_COLOR, DEFAULT_BTN_COLOR))
        )->addOnClickListener(handleClick)
      );
    }

    _list->updateItems();

    _base_size = 3;
    _base_items = new ScreenElement*[_base_size]{
      new IconButtonElement(4,4, new IconProps(
        new GoBackIcon(), 40, _base_bg, DEFAULT_BTN_COLOR
      )),
      _list,
      new TextElement(160, 4, new TextProps(
          getLocale()->MANAGE_NETWORKS, placement::middle, 
          _base_bg, useFont(fonts::detail))
      ),
    };
  }

  void WifiManagerScreen::draw(){
    tft.fillScreen(_base_bg);
    BaseScreen::draw();
  }

  void WifiManagerScreen::loop(){
    while(!_exited){
      std::unique_ptr<Point> touch(ts.read_touch());

      // Update states of the items
      _updateItemsState(_base_items, _base_size);

      if(!touch){
        continue;
      }

      // Go back button
      if(_base_items[0]->eventListener(touch.get())){
        route(previousRoute());
        return;
      }

      // Handle click on the network list
      if(_list->eventListener(touch.get())){
        if(_handleDelete){
          _handleDelete = false;
          _list->del(_list->getTouchedIndex());
          _list->updateItems();
        }
      }
    }
  }
}