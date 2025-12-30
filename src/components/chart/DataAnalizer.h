#pragma once

#include "../../providers/WeatherProvider.h"


#define DEBUG_CHARTS true

#if defined(DEBUG_CHARTS) && DEBUG_CHARTS == true
  #define PF(x, ...) Serial.printf(x, __VA_ARGS__)
  #define PTLN(x) Serial.println(x)
#endif

namespace chart
{
  // Data structure representing a single data point
  struct ChartData{
    int index;
    double temp;
    uint8_t hum;
    uint8_t pop;
  };

  // Data structure representing the analysis of a single day,
  // containing the minimum and maximum values of temperature, humidity and precipitation
  struct ChartDataAnalysis{
    // Store the number of data points
    int data_size;
    // Store the minimum and maximum temperature
    double min_temp, max_temp;
    // Store the minimum and maximum humidity
    uint8_t min_hum, max_hum;
    // Store the minimum and maximum precipitation
    uint8_t min_pop, max_pop;
  };

  
  typedef std::vector<ChartData> vchart_data_t;

  // Helper structure to store the data and its analysis
  struct DataAnalysis{
    vchart_data_t data;
    ChartDataAnalysis analysis;
  };

  using weather_vector_t = std::vector<Weather>;

  class DataAnalizer{
    
    std::vector<DataAnalysis> _cache;
    weather_vector_t *_data;
    public:
    DataAnalizer(weather_vector_t* data = nullptr);

    static DataAnalizer& getAnalizer();

    /**
     * @brief Set the data to be analyzed
     * @return *this
     */
    DataAnalizer&
    setData(weather_vector_t* data);

    /**
     * @brief Set the forecast to be analyzed
     * @return *this
     */
    DataAnalizer&
    setData(Forecast* forecast);

    /**
     * @brief Find the minimum and maximum values (temperature, humidity, precipitation) 
     * for each day in the forecast
     * @param days number of days to analyze
     * @return *this
     */
    DataAnalizer&
    analyze(int days = 3);

    /**
     * @brief Get requested day from processed data
     * @return vector of data points
     */
    DataAnalysis*
    getChartData(int day);

    inline bool hasCache(){
      return !_cache.empty();
    }
  };

  // Function type to extract the value from the data
  typedef std::function<double(const chart::ChartData&)> value_extractor_t;
  typedef std::pair<double, double> range_t;
  typedef std::function<range_t(const chart::ChartDataAnalysis&)> range_extractor_t;
}