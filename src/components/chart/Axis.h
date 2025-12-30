#pragma once

#include "../ScreenElement.h"
#include "../PosContainer.h"
#include "DataAnalizer.h"
#include "chart_data.h"

// For fast drawing of the text (i'm not using the TextElement for it's overheads)
#include "../../input/custom_buttons/TextButton.h"

namespace ui
{
  enum class AxisRotation{
    HORIZONTAL,
    VERTICAL
  };

  enum class ScalePolicy{
    STRICT,
    AUTO
  };

  /*
  We need a base class for the axis
  it should contain the following:
  - **the axis label**
  - **number of ticks**:
    - strict version, that is specified by the user (for example hours of the day (from 0 to 24, by 3 hours))
    - auto version, it will prefer rounded values, but will not exceed the specified number of ticks
    (for example, with temperature rendering, the range is dynamic, so the number of ticks should be dynamic as well,
    having 5 ticks for 18.8 - 26.3 range, we should prioritize the rounded values, so the ticks will be 18 - 27: 18, 20, 22, 24, 26, 28)
    So the auto version also should return new range of values, so the chart can be rendered properly.
    With auto version axis should be first rendered, and only then the chart.

  - **range of values**
  - **custom function to draw the values (custom formatting)**
  - **it may decide wheter to draw the values or not (insufficient space, etc.)**
  - **rotation of the axis** (either horizontal or vertical)
  - and the size of the axis (width or height, depending on the rotation)
  - the position of the axis (x, y)
  - the color of the axis
  - **position of the labels** (either left, right, top or bottom, obviously these make sense only with given rotation)
  
  */
  class AxisBase: public ScreenElement, public PosContainer{
    
    /**
     * @brief Calculate the position of the tick, based on the index
     * @param i The index of the tick
     * @param x The x position of the tick
     * @param y The y position of the tick
     * @param p The placement of the tick
     * @param step The step between the ticks
     */
    void _getTickPos(int i, int& x, int& y,  placement&, double step);

    /**
     * @brief Calculate the range and step size for the axis
     * @return float The step size
     */
    float _calcAutoTicks();

    /**
     * @brief Verify if the tick overlaps with the any of the previous ticks
     */
    bool _verifyTick(int16_t& prev_coord_overlap, TextButton* tick);
  public:
    typedef std::function<String(float)> value_formatter_t;

    static value_formatter_t default_formatter;

    /**
     * @brief Construct a new AxisBase object
     * @param x The x position of the axis (starting point)
     * @param y The y position of the axis (starting point, if the rotation is horizontal, else the ending point)
     * @param size The size of the axis (width or height, depending on the rotation)
     * @param bg The background color of the axis
     * @param label The label of the axis (will be printed at the end of the axis)
     * @param n_ticks The number of ticks on the axis (the division of the axis)
     * @param min The minimum value of the axis
     * @param max The maximum value of the axis
     */
    AxisBase(
      int16_t x, int16_t y,
      uint16_t size,
      uint16_t bg,
      uint8_t n_ticks,
      float min, float max
    );

    AxisBase(const AxisBase& other);

    AxisBase& operator=(const AxisBase& other);

    /**
     * @brief Set the Formatter object, used to display the values
     * @param formatter The formatter function, as the argument it takes the value, and returns the string representation
     * @return *this
     */
    AxisBase&
    setFormatter(value_formatter_t formatter);

    /**
     * @brief Set the Rotation object
     * @param rotation The rotation of the axis
     * @return *this
     */
    AxisBase&
    setRotation(AxisRotation rotation);

    /**
     * @brief Set the Label Position object
     * @param position The position of the label
     * @return *this
     */
    AxisBase&
    setValuePosition(Position position);

    /**
     * @brief Set the Scale Policy object
     * @param policy The scale policy
     * @return *this
     */
    AxisBase&
    setScalePolicy(ScalePolicy policy);

    AxisBase&
    setRange(float min, float max);

    /**
     * @brief Prepare the axis for drawing, create the ticks, and adjust the range
     * @param data The data to be used for the axis
     * @return *this
     */
    AxisBase&
    prepare();

    /**
     * @brief Get the Range object
     * @return chart::range_t 
     */
    const chart::range_t&
    getRange() const;

    virtual void
    draw();

    int _n_ticks;
    uint16_t _bg;
    chart::range_t _range;
    value_formatter_t _formatter;
    AxisRotation _rotation;
    Position _value_position;
    ScalePolicy _scale_policy;
    std::list<TextButton> _ticks_labels;
  };
} // namespace ui