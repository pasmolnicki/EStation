#include "WeatherDetailsScreen.h"

extern WeatherProvider wProvider;
extern Localizer localizer;

namespace ui
{
  // Formatters
  String formatTemperature(float temp){
    return String((int)temp) + localizer.getUnit(unit::temperature);
  }

  String formatPercentage(float p){
    return String((int)p) + "%";
  }

  String formatTime(float t){
    int v = (int)t;
    return v < 10 ? "0" + String(v) + ":00" : String(v) + ":00";
  }

  // Updater
  void temperatureUpdater(AxisBase* axis, chart::ChartDataAnalysis* data){
    auto& range = axis->setRange(data->min_temp, data->max_temp)
      .prepare()
      .getRange();
    data->min_temp = range.first;
    data->max_temp = range.second;
  }

  // Range extractors
  chart::range_t temperatureRange(const chart::ChartDataAnalysis& data){
    return std::make_pair(data.min_temp, data.max_temp);
  }

  chart::range_t percentageRange(const chart::ChartDataAnalysis& data){
    return std::make_pair(0.0, 100.0);
  }

  // Value extractors
  float temperatureValue(const chart::ChartData& data){
    return data.temp;
  }
  
  float humidityValue(const chart::ChartData& data){
    return data.hum;
  }

  float precipitationValue(const chart::ChartData& data){
    return data.pop;
  }


  // Constants
  constexpr int startX = 15, iconSize = 90, py = 2, indent = 10, 
                chartWidth = 120, 
                chartHeight = 100,
                _chartIndent = startX + iconSize + indent,
                chartX = 
                  // _chartIndent + (320 - _chartIndent - chartSize) / 2;
                  320 - chartWidth - 35,
                chartY = 240 - (chartHeight + 25);

  WeatherDetailsScreen::WeatherDetailsScreen():
  _chart(chartX, chartY, chartWidth, chartHeight, BASE_SCREEN_BG)
  {
    Lock lock(getSemaphore(tasks::weather));

    auto wIndex = getScreenData().detailScreenWeatherIndex;
    auto weather = wProvider.getAnalizedForecast()->at(wIndex);

    // Set title to the day of the week
    time_t t = weather._dt;
    _title._text->setProps(new TextProps("", placement::middle, _base_bg));
    setTitle(localizer.getDateFormatter()(localtime(&t), date_format::weekday_short));

    _startY += 5;

    int font_height;
    {
      uint16_t x;
      TextProps p;
      FontLoader fl(x, &p);
      font_height = tft.fontHeight();
    }

    _size = 4;
    _items = new DataElement<Weather>*[_size]{
      new WeatherDisplayElement(weather, startX + indent, _startY,
            new IconProps(nullptr, iconSize, _base_bg)),

      // Custom element for displaying max temperature
      (new TextWeatherElement(weather, startX, _startY + iconSize + py, 
          new TextProps("", placement::start, _base_bg, useFont(fonts::normal))
        ))->setter(maxTemperatureSetter),
      // Custom element for displaying min temperature
      (new TextWeatherElement(weather, startX, _startY + iconSize + 2*py + font_height, 
          new TextProps("", placement::start, _base_bg, useFont(fonts::normal))
        ))->setter(minTemperatureSetter),

      new DropletElement(weather, startX, _startY + iconSize + 3*py + 2*font_height, _base_bg,
          new TextProps("", placement::start, _base_bg))
    };

    // Add the axes

    // Time axis
    _chart.addAxis(
      0, 24, 3, Position::BOTTOM, AxisRotation::HORIZONTAL,
      Position::BOTTOM, ScalePolicy::STRICT,
      formatTime
    );

    // Percentage axis
    _chart.addAxis(
      0, 100, 5, Position::RIGHT, AxisRotation::VERTICAL,
      Position::RIGHT, ScalePolicy::STRICT,
      formatPercentage
    );

    // Temperature axis
    _chart.addAxis(
      0, 100, 4, Position::LEFT, AxisRotation::VERTICAL,
      Position::LEFT, ScalePolicy::AUTO,
      formatTemperature,
      temperatureUpdater
    );

    // Add the charts
    _chart.addChart(
      getLocale()->TEMP,
      0xD01F,
      temperatureRange,
      temperatureValue
    );
    _chart.addChart(
      getLocale()->HUMIDITY,
      0x6E5F,
      percentageRange,
      humidityValue
    );
    _chart.addChart(
      getLocale()->POP,
      0x2CBF,
      percentageRange,
      precipitationValue
    );
    _chart.setLegendProps(
      chartWidth, 50, LegendDirection::ROW
    );
    _chart.init();

    auto& analizer = chart::DataAnalizer::getAnalizer();
    if(!analizer.hasCache()){
      analizer.setData(wProvider.forecast()).analyze(4);
    }
    _chart.setData(analizer.getChartData(wIndex + 1));
    updateWeatherStates();
  }

  void WeatherDetailsScreen::updateWeatherStates(){
    iterate([](DataElement<Weather>* elem){
      elem->setData((*wProvider.getAnalizedForecast())[getScreenData().detailScreenWeatherIndex]);
      elem->updateState();
    });
  }

  void WeatherDetailsScreen::draw(){
    WeatherBaseScreen::draw();
    _chart.draw();
  }

  void WeatherDetailsScreen::handleTouch(Point* p){
    auto area = TouchScreen::toArea(p);
    switch(area){
      case TouchPoint::up:
        route(path::NEXT_FORECAST);
        return;
      default:
        break;
    }
  }
} // namespace ui