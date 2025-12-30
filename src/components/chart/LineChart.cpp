#include "LineChart.h"

namespace ui
{

  double LineChart::default_getter(const chart::ChartData& data){
    return 0.0;
  }

  chart::range_t LineChart::default_range(const chart::ChartDataAnalysis& data){
    return {0.0, 1.0};
  }

  LineChart::LineChart(
    int16_t x, int16_t y,
    uint16_t width, uint16_t height,
    uint16_t color, uint16_t bg, 
    chart::DataAnalysis* data
  ): DataElement(data), PosContainer(x, y, width, height),
  _value_extractor(default_getter),
  _range_extractor(default_range),
  _bg(bg), _color(color),
  _scale_x(1.0f), _scale_y(1.0f), _prepared(false) {}

  LineChart::LineChart(
    LineChartProps& props,
    int16_t x, int16_t y,
    uint16_t width, uint16_t height,
    uint16_t bg, chart::DataAnalysis* data
  ): LineChart(x, y, width, height, props.color, bg, data) {
    (void)setProps(props);
  }

  LineChart::LineChart(
    const LineChart& other
  ): DataElement(other._data), 
  PosContainer(other._x, other._y, other._width, other._height) {
    (void)(*this = other);
  }

  LineChart&
  LineChart::setProps(const LineChartProps& props){
    _color = props.color;
    (void)setValueExtractor(props.value_extractor)
          .setRangeExtractor(props.range_extractor);
    return *this;
  }

  LineChart&
  LineChart::setValueExtractor(chart::value_extractor_t getter){
    _value_extractor = getter;
    if(!_value_extractor) _value_extractor = default_getter;
    return *this;
  }

  LineChart&
  LineChart::setRangeExtractor(chart::range_extractor_t getter){
    _range_extractor = getter;
    if(!_range_extractor) _range_extractor = default_range;
    return *this;
  }

  void LineChart::prepare(){
    if (!_data || _data->data.size() < 2) return;
    // Calculate the scale
    auto range = _range_extractor(_data->analysis);
    _scale_x = _width / (_data->data.size() - 1);
    _scale_y = _height / (range.second - range.first);
    _prepared = true;
  }

  void
  LineChart::onUpdate(){
    // When the data is updated, prepare the chart
    prepare();
  }

  void
  LineChart::draw(){
    // PF("Drawing LineChart at (%d, %d) with size (%d, %d)\n", _x, _y, _width, _height);
    // PF("Data: %p\n", _data);
    // if(_data){
    //   PF("Data size: %d\n", _data->data.size());
    // }
    // If there is no sufficient data, return
    if(!_data || _data->data.size() < 2 || !_prepared) return;

    // PF("Scale: (%f, %f)\n", _scale_x, _scale_y);

    using namespace chart;
    ChartData *p1 = &_data->data[0], *p2;
    
    auto minmax = _range_extractor(_data->analysis);
    auto prev = _value_extractor(*p1) - minmax.first, next = prev;

    // PTLN("_value_extractor called");

    // Plot the data
    for (int i = 1; i < _data->data.size(); i++){
      p2 = &_data->data[i];
      next = _value_extractor(*p2) - minmax.first;
      // Calculate the position of the points
      int x1 = _x + (p1->index * _scale_x);
      int y1 = _y + (_height - prev * _scale_y);
      int x2 = _x + (p2->index * _scale_x);
      int y2 = _y + (_height - next * _scale_y);

      // PF("Drawing line from (%d, %d) to (%d, %d)\n", x1, y1, x2, y2);
      // Draw the line
      tft.drawWedgeLine(x1, y1, x2, y2, 1, 1, _color, _bg);
      // Update the previous point
      p1 = p2;
      prev = next;
    }
  }

  LineChart& LineChart::operator=(const LineChart& other){
    _value_extractor = other._value_extractor;
    _range_extractor = other._range_extractor;
    _bg = other._bg;
    _color = other._color;
    _scale_x = other._scale_x;
    _scale_y = other._scale_y;
    _prepared = other._prepared;
    PosContainer::operator=(other);
    ScreenElement::operator=(other);
    return *this;
  }

} // namespace ui