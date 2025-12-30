#include "DataAnalizer.h"

using namespace chart;

extern WeatherProvider wProvider;

DataAnalizer analizer = DataAnalizer();

DataAnalizer& DataAnalizer::getAnalizer(){
  return analizer;
}

DataAnalizer::DataAnalizer(weather_vector_t* data){
  (void)setData(data);
}

DataAnalizer& DataAnalizer::setData(weather_vector_t* data){
  _data = data;
  return *this;
}

DataAnalizer& DataAnalizer::setData(Forecast* forecast){
  _data = &forecast->forecast;
  return *this;
}

DataAnalizer& DataAnalizer::analyze(int days){
  if(!_data || _data->empty() || days <= 0){
    return *this;
  }

  // Clear the cache
  _cache.clear();  
  _cache.reserve(days);

  int it = 0, day = 0, start = 0, end;
  while(it < _data->size() && day < days){
    // Find when the forecast starts (when next day starts)
    wProvider._findNextDay(it, _data->size(), _data);
    end = it;
    
    // Find the minimum and maximum values (temperature, humidity, precipitation)
    // for each day in the forecast
    DataAnalysis analysis;
    ChartDataAnalysis data;
    auto first = _data->begin() + start, last = _data->begin() + end;
    // Set the default values (goes from right to left)
    data.min_temp = data.max_temp = first->_temp;
    data.min_hum = data.max_hum = first->_humidity;
    data.min_pop = data.max_pop = first->_pop;

    // Reserve the space for the data points
    data.data_size = end - start;
    analysis.data.reserve(data.data_size);

    // Find the minimum and maximum values
    for (auto it = first; it != last; it++){
      // Update the minimum and maximum values
      data.min_temp = std::min(data.min_temp, it->_temp);
      data.max_temp = std::max(data.max_temp, it->_temp);
      data.min_hum = std::min(data.min_hum, it->_humidity);
      data.max_hum = std::max(data.max_hum, it->_humidity);
      data.min_pop = std::min(data.min_pop, decltype(data.min_pop)(it->_pop * 100));
      data.max_pop = std::max(data.max_pop, decltype(data.min_pop)(it->_pop * 100));

      // Store the data point
      analysis.data.push_back({
        .index = int(it - first),
        .temp = it->_temp,
        .hum = it->_humidity,
        .pop = decltype(data.min_pop)(it->_pop * 100)
      });
    }
    analysis.analysis = data;
    // Store the analysis
    _cache.push_back(analysis);

    day++;
    start = it;
  }

  return *this;
}

DataAnalysis* DataAnalizer::getChartData(int day){
  if (day < 0 || day >= _cache.size() || _cache.empty()){
    return nullptr;
  }
  return &_cache[day];
}