#pragma once

#include <Arduino.h>

namespace ui
{
  class PosContainer{
    public:
      PosContainer(
        int16_t x, int16_t y,
        uint16_t width, uint16_t height
      ): _x(x), _y(y), _width(width), _height(height) {}

      PosContainer(
        const PosContainer& other
      ): _x(other._x), _y(other._y), _width(other._width), _height(other._height) {}

      PosContainer& operator=(const PosContainer& other){
        _x = other._x;
        _y = other._y;
        _width = other._width;
        _height = other._height;
        return *this;
      }

      int16_t x() const { return _x; }
      int16_t y() const { return _y; }
      uint16_t width() const { return _width; }
      uint16_t height() const { return _height; }

      void x(int16_t x) { _x = x; }
      void y(int16_t y) { _y = y; }
      void width(uint16_t width) { _width = width; }
      void height(uint16_t height) { _height = height; }

    protected:
      int16_t _x, _y;
      uint16_t _width, _height;
  };
}