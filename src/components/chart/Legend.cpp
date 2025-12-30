#include "Legend.h"

namespace ui
{

  // Constants
  constexpr int padding = 4, box_size = 10;

  Legend::Legend(
    int16_t x, int16_t y,
    uint16_t width, uint16_t height,
    uint16_t bg,
    LegendDirection direction
  ):PosContainer(x, y, width, height) {
    _direction = direction;
    _bg = bg;
  }

  void Legend::prepareLayout(){
    // Given dimensions are the maximum dimensions,
    // if the label will exceed them it won't be rendered
    // With the first two cases (row or column) we try to fit as many as possible
    // in given direction, and if we can't go further we switch to the next line

    if(_labels.empty()) return;

    _total_height = 0;
    _total_width = 0;

    int x = _x, y = _y;
    auto it = _labels.begin(), last = _labels.end();
    TextButton* last_label = &it->label;

    // Get the total width and height of the element
    int element_width, element_height;

    // Update the first element's position
    _updateElement(last_label, element_width, element_height, x, y);

    _total_height = element_height + padding;
    _total_width = element_width + padding;

    bool newRowOrColumn = false, breakCondition = false;

    while(it != _labels.end()){
      // Check if we need to switch to the next row or column
      if (_direction == LegendDirection::ROW){
        newRowOrColumn = _total_width > _width;
        breakCondition = _total_height > _height;
      } else if (_direction == LegendDirection::COLUMN){
        newRowOrColumn = _total_height > _height;
        breakCondition = _total_width > _width;
      }

      if (breakCondition){
        // We can't fit the element, so we need to break
        last = it;
        break;
      }

      // Update the position of the element, as well as the total width and height
      _updatePosition(x, y, element_width, element_height, newRowOrColumn);
      if (!newRowOrColumn){
        // If we managed to fit the element, get the next label
        last_label = &(++it)->label;
      }
      // Update the element's position
      _updateElement(last_label, element_width, element_height, x, y);
    }

    // If we can't fit the element, remove all the elements that exceed the given dimensions
    if (last != _labels.end()){
      _labels.erase(last, _labels.end());
    }
  }

  void Legend::addLabel(
    const String& label,
    uint16_t color
  )
  {
    _labels.push_back({
      TextButton(_x, _y, new TextProps(label, placement::start, _bg, useFont(fonts::detail)))
      ,color
    });
    _labels.back().label.setWidthHeight();
  }

  void Legend::draw(){
    for (auto it = _labels.begin(); it != _labels.end(); it++){
      // Draw the box
      tft.fillRect(it->label.x - box_size, it->label.y + (it->label.height - box_size) / 2, box_size, box_size, it->color);
      it->label.draw();
    }
  }

  void Legend::setStickPosition(
    int16_t x, int16_t y, 
    Position pos
  )
  {
    int16_t move_x, move_y;
    switch(pos){
      case Position::TOP:
        move_x = x - _x;
        move_y = y - _total_height - _y;
        break;
      case Position::BOTTOM:
        move_x = x - _x;
        move_y = y - _y;
        break;
      case Position::LEFT:
        move_x = x - _total_width - _x;
        move_y = y - _y;
        break;
      default:
        move_x = x - _x;
        move_y = y - _y;
        break;
    }
    // apply movement the each label
    for (auto it = _labels.begin(); it != _labels.end(); it++){
      it->label.x += move_x;
      it->label.y += move_y;
    }
  }

  void Legend::_updatePosition(
    int& x, int& y,
    int element_width, int element_height, 
    bool newRowOrColumn
  ){
    if (newRowOrColumn){
      // Switch to the next row or column
      if (_direction == LegendDirection::ROW){
        // Switch to the next column (row is full)
        _total_height += element_height + padding;
        _total_width = element_width + padding;

        x = _x; // Reset the x position
        y += element_height + padding;
      } else {
        // Switch to the next row (column is full)
        _total_width += element_width + padding;
        _total_height = element_height + padding;

        y = _y; // Reset the y position
        x += element_height + padding;
      }
    } else {
      // Keep the current row or column
      if (_direction == LegendDirection::ROW){
        // Keep the row
        x += element_width + 2*padding;
        _total_width += element_width + 2*padding;
      } else {
        // Keep the column
        y += element_height + 2*padding;
        _total_height += element_height + 2*padding;
      }
    }
  }

  void Legend::_updateElement(
    TextButton* last_label, 
    int& element_width, int& element_height,
    int& x, int& y
  ){
    last_label->x = x + box_size + padding;
    last_label->y = y;
    element_width = last_label->width + padding + box_size;
    element_height = last_label->height;
  }
}