#pragma once

#include "../DataElement.h"
#include "../PosContainer.h"
#include "DataAnalizer.h"

namespace ui
{
  // Helper struct to store the properties of a LineChart
  struct LineChartProps{
    uint16_t color;
    chart::range_extractor_t range_extractor;
    chart::value_extractor_t value_extractor;

    /**
     * @brief Construct a new LineChartProps object
     * @param color The color of the line
     * @param range_extractor The range extractor function, .first is the minimum value, .second is the maximum value
     * @param value_extractor The value extractor function
     */
    LineChartProps(
      uint16_t color = 0,
      chart::range_extractor_t range_extractor = nullptr,
      chart::value_extractor_t value_extractor = nullptr
    ): color(color), range_extractor(range_extractor), value_extractor(value_extractor) {}

    LineChartProps(const LineChartProps& other) {
      (void)(*this = other);
    }

    LineChartProps& operator=(const LineChartProps& other){
      value_extractor = other.value_extractor;
      range_extractor = other.range_extractor;
      color = other.color;
      return *this;
    }
  };

  /**
   * @brief LineChart class, used to draw a single line chart
   */
  class LineChart: public DataElement<chart::DataAnalysis*>, public PosContainer{
    public:

      static double default_getter(const chart::ChartData& data);
      static chart::range_t default_range(const chart::ChartDataAnalysis& data);

      LineChart(
        int16_t x, int16_t y,
        uint16_t width, uint16_t height,
        uint16_t color, uint16_t bg, 
        chart::DataAnalysis* data = nullptr
      );

      LineChart(
        LineChartProps& props,
        int16_t x, int16_t y,
        uint16_t width, uint16_t height,
        uint16_t bg, chart::DataAnalysis* data = nullptr
      );

      // Copy constructor
      LineChart(
        const LineChart& other
      );

      LineChart&
      setProps(const LineChartProps& props);

      /**
       * @brief Set the value extractor function, it will be used to extract the value from the data
       * @param getter The value extractor function
       * @return *this
       */
      LineChart& 
      setValueExtractor(chart::value_extractor_t getter);

      /**
       * @brief Set the range extractor function, it will be used to extract the range from the data
       * .first is the minimum value, .second is the maximum value
       * @param getter The range extractor function
       * @return *this
       */
      LineChart&
      setRangeExtractor(chart::range_extractor_t getter);

      /**
       * @brief Prepare the chart, calculate the scale
       */
      void
      prepare();

      virtual void
      onUpdate();

      virtual void
      draw();

      LineChart& operator=(const LineChart& other);

      chart::value_extractor_t _value_extractor;
      chart::range_extractor_t _range_extractor;
      uint16_t _bg, _color;
      float _scale_x, _scale_y;
      bool _prepared;
  };
}