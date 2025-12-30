#pragma once

#include "LineChart.h"
#include "Axis.h"
#include "Legend.h"

namespace ui
{

  /*
  
  ## Chart Component

  The chart component is used to draw multiple line charts on the same chart, with multiple axes.
  Has completly customizable axes, charts, and legend.

  You can add multiple line charts, multiple axes (with 4 possible positions), and a legend 
  (with 2 possible directions, and custom stick point).
  
  */
  class Chart: public DataElement<chart::DataAnalysis*>, public PosContainer{
    public:
      typedef std::function<void(AxisBase*, chart::ChartDataAnalysis*)> axis_updater_t;

      typedef struct {
        AxisBase axis;
        axis_updater_t updater;
      } _AxisConfig;

      static axis_updater_t default_axis_updater;

      Chart(
        int16_t x, int16_t y,
        uint16_t width, uint16_t height,
        uint16_t bg, chart::DataAnalysis* data = nullptr
      );

      /**
       * @brief Initialize the chart component, sets up the legend
       */
      void init();

      /**
       * @brief Add a new line chart to the chart component
       */
      void 
      addChart(const String& label, LineChartProps& props);

      /**
       * @brief Add a new line chart to the chart component
       * @param color The color of the line
       * @param range_extractor The range extractor function, .first is the minimum value, .second is the maximum value
       * @param value_extractor The value extractor function, returns the value of the data
       */
      void 
      addChart(
        const String& label,
        uint16_t color,
        chart::range_extractor_t range_extractor,
        chart::value_extractor_t value_extractor
      );

      /**
       * @brief Add a new axis to the chart component
       * @param min The minimum value of the axis
       * @param max The maximum value of the axis
       * @param n_ticks The number of ticks on the axis
       * @param axis_pos The position of the axis
       * @param rotation The rotation of the axis
       * @param position The position of the values
       * @param policy The scale policy of the axis
       * @param formatter The formatter function, as the argument it takes the value, and returns the string representation
       * @param updater The updater function, as the arguments it takes the axis and the data analysis, by default
       *              it uses the default updater function
       */
      void 
      addAxis(
        float min, float max,
        int n_ticks = 5,
        Position axis_pos = Position::BOTTOM,
        AxisRotation rotation = AxisRotation::HORIZONTAL,
        Position value_pos = Position::BOTTOM,
        ScalePolicy policy = ScalePolicy::STRICT,
        AxisBase::value_formatter_t formatter = AxisBase::default_formatter,
        axis_updater_t updater = default_axis_updater
      );

      /**
       * @brief Set the Legend Props object (by default the legend is at the top of the chart, with the row direction)
       * @param width The width of the legend
       * @param height The height of the legend
       * @param direction The direction of the legend lables
       * @param stick_pos The position of the sticky point (if not set, the stick point will be at the top of the chart
       * - making the legend stick there)
       * @param stick_x The x position of the sticky point (if not set, stick_x = -1 -> chart_x, same for stick_y)
       * @param stick_y The y position of the sticky point
       */
      void 
      setLegendProps(
        uint16_t width, uint16_t height,
        LegendDirection direction,
        Position stick_pos = Position::TOP,
        int16_t stick_x = -1, int16_t stick_y = -1
      );

      virtual void
      onUpdate();
      
      virtual void
      draw();

      void 
      drawBase();

    private:
      int16_t _stick_x, _stick_y;
      Position _stick_pos;
      uint16_t _bg;
      Legend _legend;
      std::list<LineChart> _charts;
      std::list<_AxisConfig> _axes;
  };
}