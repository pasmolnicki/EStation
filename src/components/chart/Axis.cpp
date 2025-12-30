#include "Axis.h"

namespace ui
{
  String _default_formatter(float value){
    return String(value);
  }

  AxisBase::value_formatter_t AxisBase::default_formatter = _default_formatter;

  AxisBase::AxisBase(
    int16_t x, int16_t y,
    uint16_t size, 
    uint16_t bg,
    uint8_t ticks,
    float min, float max
  ): PosContainer(x, y, size, size)
  {
    _n_ticks = ticks;
    _bg = bg;
    _range = {min, max};

    // Default values
    _formatter = default_formatter;
    (void)setRotation(AxisRotation::HORIZONTAL);
    _value_position = Position::BOTTOM;
    _scale_policy = ScalePolicy::STRICT;
  }

  AxisBase::AxisBase(const AxisBase& other): PosContainer(other){
    (void)(*this = other);
  }

  AxisBase& AxisBase::operator=(const AxisBase& other){
    _formatter = other._formatter;
    _rotation = other._rotation;
    _value_position = other._value_position;
    _scale_policy = other._scale_policy;
    _range = other._range;
    _n_ticks = other._n_ticks;
    _bg = other._bg;
    _ticks_labels = other._ticks_labels;
    return *this;
  }

  AxisBase& AxisBase::setFormatter(value_formatter_t formatter){
    _formatter = formatter;
    return *this;
  }

  AxisBase& AxisBase::setRotation(AxisRotation rotation){
    _rotation = rotation;
    return *this;
  }

  AxisBase& AxisBase::setValuePosition(Position position){
    _value_position = position;
    return *this;
  }

  AxisBase& AxisBase::setScalePolicy(ScalePolicy policy){
    _scale_policy = policy;
    return *this;
  }

  AxisBase& AxisBase::setRange(float min, float max){
    _range = {min, max};
    return *this;
  }

  AxisBase& AxisBase::prepare(){

    // Clear previous ticks
    _ticks_labels.clear();

    
    float scale, step = float(_height) / (_n_ticks - 1);
    int x, y;
    placement p;

    // The previous coordinate of the tick, must be set according to the rotation
    int16_t prev_coord_overlap = _rotation == AxisRotation::HORIZONTAL ?
        std::numeric_limits<int16_t>::min() : std::numeric_limits<int16_t>::max();

    // To find the ticks, we need to first see what kind of policy we have,
    // then if we have automatic one, we need to find the optimal range.
    // If we have a manual policy, we just need to simply calculate the ticks,
    // based on the range
    if (_scale_policy == ScalePolicy::STRICT){
      // Strict policy, we need to use the range as it is
      scale = (_range.second - _range.first) / (_n_ticks - 1);
    } else {
      // Automatic policy, we need to calculate the range
      // using the tickmark algorithm
      scale = _calcAutoTicks();
    }

    for(int i = 0; i < _n_ticks; i++){
      _getTickPos(i, x, y, p, step);
      float value = _range.first + i * scale;
      
      // Create the tick, not adding it yet to the list
      auto tick = TextButton(x, y, new TextProps(
          _formatter(value), p, _bg, useFont(fonts::detail),
          TFT_DARKGREY
      ));
      tick.setWidthHeight();

      // Check if the tick is overlapping with the previous one
      if (_verifyTick(prev_coord_overlap, &tick)){
        _ticks_labels.push_back(std::forward<TextButton>(tick));
      }
    }

    return *this;
  }

  const chart::range_t& AxisBase::getRange() const{
    return _range;
  }  

  void AxisBase::draw(){
    // Draw the line
    if (_rotation == AxisRotation::HORIZONTAL){
      tft.drawFastHLine(_x, _y, _width, DEFAULT_BTN_COLOR);
    } else {
      tft.drawFastVLine(_x, _y, _height, DEFAULT_BTN_COLOR);
    }
    
    // Draw the ticks
    for (auto it = _ticks_labels.begin(); it != _ticks_labels.end(); it++){
      it->draw();
    }
  }

  bool AxisBase::_verifyTick(int16_t& prev_coord_overlap, TextButton* tick){
    // Check if the text is out of bounds
    int overlap_coord_min = 0, 
        overlap_coord_max = 0,
        next_overlap = 0;
    bool reverse = false;

    if (_rotation == AxisRotation::HORIZONTAL){

      // The x is the center of the text, plus we are
      // rendering from left to right, so we need to subtract the overlap size
      // The overlap coord's are the x position's of the bounds of the text
      // min - left, max - right
      overlap_coord_min = tick->x - tick->width / 2; 
      overlap_coord_max = overlap_coord_min + tick->width;
      next_overlap = overlap_coord_max;

      if (_value_position == Position::BOTTOM){
        tick->y += 5;
      } else {
        tick->y -= tick->height + 5;
      }
    } else {
      tick->y -= tick->height / 2;
      overlap_coord_min = tick->y; 
      overlap_coord_max = overlap_coord_min + tick->height;
      next_overlap = overlap_coord_min;
      reverse = true; // We are rendering from bottom to top
    } 

    bool overlap = reverse ? 
      (overlap_coord_min > prev_coord_overlap) :
      (overlap_coord_min < prev_coord_overlap);
    
    // Check if there is overlap with any of the previous ticks
    if (overlap){
      return false;
    } else {
      // Update the prev_coord_overlap
      prev_coord_overlap = next_overlap;
      return true;
    }
  }

  void AxisBase::_getTickPos(int i, int& x, int& y, placement& p, double step){
    // Calculate the position of the tick
    if (_rotation == AxisRotation::HORIZONTAL){
      x = _x + i * step;
      y = _y;
      p = placement::middle;
    } else {
      // Vertical
      x = _x;
      y = _y + _height - i * step; // We are rendering from bottom to top

      if (_value_position == Position::LEFT){
        p = placement::end;
        x += 2;
      } else {
        p = placement::start;
        x -= 2;
      }
    }
  }

  float AxisBase::_calcAutoTicks(){
    // Calculate the ticks
    float range = _range.second - _range.first;
    float rough_step = range / (_n_ticks - 1);
    float magnitude = powf(10, -floor(log10(abs(rough_step))));
    float norm_step = rough_step * magnitude;
    float good_steps[] = {1, 1.5, 2, 2.5, 5, 7.5, 10};
    float step = good_steps[sizeof(good_steps) / sizeof(float) - 1];
    
    for(int i = 0; i < sizeof(good_steps) / sizeof(float); i++){
      if (norm_step <= good_steps[i]){
        step = good_steps[i];
        break;
      }
    }

    step = step / magnitude;

    float min = floor(_range.first / step) * step;
    float max = ceil(_range.second / step) * step;

    _range = {min, max};

    return step;
  }
}