#include "Chart.h"

namespace ui
{
  void default_updater(AxisBase* axis, chart::ChartDataAnalysis* data){
    (void)axis->prepare();
  }

  Chart::axis_updater_t Chart::default_axis_updater = default_updater;

  Chart::Chart(
    int16_t x, int16_t y,
    uint16_t width, uint16_t height,
    uint16_t bg, chart::DataAnalysis* data
  ): DataElement(data), PosContainer(x, y, width, height),
  _legend(x, y - 25, width, 20, bg, LegendDirection::ROW)
  {
    _stick_x = -1;
    _stick_y = -1;
    _stick_pos = Position::TOP;
    _bg = bg;
    onUpdate();
  }

  void Chart::init(){
    _legend.prepareLayout();

    // Update the position of the legend
    _stick_x = _stick_x == -1 ? _x : _stick_x;
    _stick_y = _stick_y == -1 ? _y : _stick_y;
    _legend.setStickPosition(_stick_x, _stick_y, _stick_pos);
  }

  void Chart::addChart(const String& label, LineChartProps& props){
    _charts.emplace_back(props, _x, _y, _width, _height, _bg, _data);
    if (_data) _charts.back().prepare();
    _legend.addLabel(label, props.color);
  }

  void Chart::addChart(
    const String& label,
    uint16_t color,
    chart::range_extractor_t range_extractor,
    chart::value_extractor_t value_extractor
  ){
    LineChartProps props(color, range_extractor, value_extractor);
    addChart(label, props);
  }

  void Chart::addAxis(
    float min, float max,
    int n_ticks,
    Position pos,
    AxisRotation rotation,
    Position position,
    ScalePolicy policy,
    AxisBase::value_formatter_t formatter,
    axis_updater_t updater
  ){
    int x, y, size;

    switch(pos){
      case Position::TOP:
        x = _x;
        y = _y;
        size = _width;
        break;
      case Position::RIGHT:
        x = _x + _width;
        y = _y;
        size = _height;
        break;
      case Position::BOTTOM:
        x = _x;
        y = _y + _height;
        size = _width;
        break;
      case Position::LEFT:
        x = _x;
        y = _y;
        size = _height;
        break;
    }

    AxisBase axis(x, y, size, _bg, n_ticks,  min, max);
    axis
    .setFormatter(formatter)
    .setRotation(rotation)
    .setValuePosition(position)
    .setScalePolicy(policy);
    _axes.push_back(_AxisConfig{axis, updater});
  }

  void Chart::setLegendProps(
    uint16_t width, uint16_t height,
    LegendDirection direction,
    Position stick_pos,
    int16_t stick_x, int16_t stick_y 
  ){
    _legend.width(width);
    _legend.height(height);
    _legend._direction = direction;
    _stick_x = stick_x;
    _stick_y = stick_y;
    _stick_pos = stick_pos;
  }

  void Chart::onUpdate(){
    if (!_data) return;

    // Update the axis
    for (auto it = _axes.begin(); it != _axes.end(); it++){
      it->updater(&it->axis, &_data->analysis);
    }

    // Only after the axis are prepared, prepare the charts
    for (auto it = _charts.begin(); it != _charts.end(); it++){
      it->setData(_data);
    }
    _redraw = true;
  }

  void Chart::drawBase(){
    tft.fillRect(_x, _y, _width, _height, _bg);
    for (auto it = _axes.begin(); it != _axes.end(); it++){
      it->axis.draw();
    }
    _legend.draw();
  }

  void Chart::draw(){
    if (!_charts.size()) return;

    drawBase();
    for (auto it = _charts.begin(); it != _charts.end(); it++){
      it->draw();
    }

    _redraw = false;
  }
}