#include "WeatherClient.h"

HTTPClient http;

extern Localizer localizer;

static const auto APPID = String(""); // Insert your Open Weather Map key 

void throwOnEmptyAppid(){
    if (APPID.isEmpty()){
        throw std::runtime_error("Could not fetch locations, \nappid is not specified, see \n   src/clients/WeatherClient.cpp.");
    }
}

std::vector<LocationInfo> 
WeatherClient::getLocations(const String& location){
    std::vector<LocationInfo> locations;

    throwOnEmptyAppid();

    http.begin("http://api.openweathermap.org/geo/1.0/direct?q=" + location + "&limit=5&appid="+APPID);
    int http_code = http.GET();
    String payload = http.getString();

    if (http_code == 200)
    {
        lazyjson::extractor doc(payload.c_str());
        for (int i = 0; i < 5; i++){
            
            if (doc[i].isNull()){
                break;
            }
            doc[i].cache();

            locations.push_back({
                doc["name"].extract().as<String>(), doc["country"].extract().as<String>(), 
                doc["state"].extract().as<String>(), 
                i, location, doc["lat"].extract().as<double>(), doc["lon"].extract().as<double>()
            });
            doc.reset();
        }
    }
    http.end();
    return locations;
}

LocationInfo WeatherClient::getLocation(const String& location, int index){
    LocationInfo location_info;

    throwOnEmptyAppid();

    http.begin("http://api.openweathermap.org/geo/1.0/direct?q=" + location + "&limit=5&appid="+APPID);
    int http_code = http.GET();

    String payload = http.getString();
    
    if (http_code == 200)
    {
        lazyjson::extractor doc(payload.c_str());
        if (doc[index].isNull()){
            return location_info;
        }
        doc[index].cache();

        location_info = {
            doc["name"].extract().as<String>(), doc["country"].extract().as<String>(), 
            doc["state"].extract().as<String>(), 
            index, location, doc["lat"].extract().as<double>(), doc["lon"].extract().as<double>()
        };
        doc.reset();
    }
    http.end();
    return location_info;
}

bool WeatherClient::init(String city_name, int index){
    auto loc = getLocation(city_name, index);
    auto isSuccessful = loc.index != -1;
    if (isSuccessful){
        _lat = loc.lat;
        _lon = loc.lon;
    }
    return isSuccessful;
}

bool WeatherClient::current(Weather* weather)
{   
    throwOnEmptyAppid();
    http.begin("http://api.openweathermap.org/data/2.5/weather?lat="+String(_lat)+"&lon="+String(_lon)+
        "&units=" + localizer.getUnitSytemName() +"&appid="+APPID);
    
    int16_t http_code = http.GET();
    String payload = http.getString();

    bool isSuccessfull = http_code == 200;

    if (isSuccessfull){
        lazyjson::extractor doc(payload.c_str());

        weather
            ->feels_like(doc["main"]["feels_like"].extract().as<double>())
            ->main(doc["weather"][0]["main"].extract().as<String>())
            ->icon(doc["weather"][0]["icon"].extract().as<String>())
            ->pressure(doc["main"]["pressure"].extract().as<uint16_t>())
            ->humidity(doc["main"]["humidity"].extract().as<uint8_t>())
            ->temp(doc["main"]["temp"].extract().as<double>())
            ->wind_speed(doc["wind"]["speed"].extract().as<double>())
            ->sunrise(doc["sys"]["sunrise"].extract().as<uint32_t>())
            ->sunset(doc["sys"]["sunset"].extract().as<uint32_t>())
            ->dt(doc["dt"].extract().as<uint32_t>())
            ->timezone(doc["timezone"].extract().as<uint32_t>());
    }
    http.end();

    return isSuccessfull;
}


bool WeatherClient::forecast(Forecast* forecast, int timezone)
{
    throwOnEmptyAppid();
    http.begin(
        "http://api.openweathermap.org/data/2.5/forecast?lat="
        +String(_lat)+"&lon="+String(_lon)
        +"&units=" + localizer.getUnitSytemName() +"&appid="+APPID);
    
    int16_t http_code = http.GET();
    String payload = http.getString();

    bool isSuccessfull = http_code == 200;

    if (isSuccessfull)
    {
        lazyjson::extractor doc(payload.c_str());
        for (uint8_t i=0; i < NUMBER_OF_HOURS_TO_FORECAST; i++)
        {
            doc["list"][i].cache();

            forecast->forecast.at(i)
                .feels_like(doc["main"]["feels_like"].extract().as<double>())
                ->main(doc["weather"][0]["main"].extract().as<String>())
                ->icon(doc["weather"][0]["icon"].extract().as<String>())
                ->pressure(doc["main"]["pressure"].extract().as<uint16_t>())
                ->humidity(doc["main"]["humidity"].extract().as<uint8_t>())
                ->temp(doc["main"]["temp"].extract().as<double>())
                ->wind_speed(doc["wind"]["speed"].extract().as<double>())
                ->pop(doc["pop"].extract().as<double>())
                ->dt(doc["dt"].extract().as<uint32_t>())
                ->timezone(timezone);
            doc.reset();
        }
    }
    http.end();

    return isSuccessfull;
}