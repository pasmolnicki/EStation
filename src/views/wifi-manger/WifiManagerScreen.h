#pragma once

#include "../base/DataBaseScreen.h"
#include "../../components/lists/PageListElement.h"
#include "../../components/buttons/CardElement.h"

#include "../../providers/MemoryProvider.h"

namespace ui
{
  class WifiManagerScreen: public BaseScreen
  {
    PageListElement *_list;

    public:
      static bool _handleDelete;

      WifiManagerScreen();

      void draw();
      void loop();

      
  };
}