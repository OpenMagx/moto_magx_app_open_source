#include "structureparser.h"

bool StructureParser::startDocument()
{
    if(weatherData.forecastDataList.count() != 0)
    {
        weatherData.forecastDataList.clear();
    }
    return TRUE;
}

bool StructureParser::startElement( const QString&, const QString&,
                                    const QString& qName,
                                    const QXmlAttributes& attributes)
{
    // handle weather condition
    if(qName == "yweather:condition")
    {
        weatherData.weatherCondition = attributes.value("text");
        weatherData.weatherCode = attributes.value("code").toInt();
        weatherData.temperature = attributes.value("temp").toInt();
        weatherData.publishedDate = attributes.value("date");
    }
    
    if(qName == "yweather:location")
    {
        weatherData.cityName = attributes.value("city");
    }
    
    if(qName == "yweather:astronomy")
    {
        weatherData.sunRiseTime = attributes.value("sunrise");
        weatherData.sunSetTime = attributes.value("sunset");
    }
    
    if(qName == "yweather:units")
    {
        weatherData.tempUnit = attributes.value("temperature");
        weatherData.distanceUnit = attributes.value("distance");
        weatherData.pressureUnit = attributes.value("pressure");
        weatherData.speedUnit = attributes.value("speed");
    }
    
    if(qName == "yweather:wind")
    {
        weatherData.chill = attributes.value("chill");
        weatherData.direction = attributes.value("direction");
        weatherData.speed = attributes.value("speed");
    }
    
    if(qName == "yweather:atmosphere")
    {
        weatherData.humidity = attributes.value("humidity");
        weatherData.visibility = attributes.value("visibility");
        weatherData.pressure = attributes.value("pressure");
        weatherData.rising = attributes.value("rising");
    }
    
    if(qName == "yweather:forecast")
    {   
        ForecastData *forecastData = new ForecastData();
        forecastData->day = attributes.value("day");
        forecastData->date = attributes.value("date");
        forecastData->lowTemp = attributes.value("low");
        forecastData->highTemp = attributes.value("high");
        forecastData->condition = attributes.value("text");
        
        weatherData.forecastDataList.append(forecastData);
        
    }
    
    return TRUE;
}

bool StructureParser::endElement( const QString&, const QString&, const QString& )
{
    indent.remove((uint)0, 4);
    return TRUE;
}
