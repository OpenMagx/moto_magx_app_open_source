#ifndef __WEATHER_DATA__
#define __WEATHER_DATA__

#include "forecastData.h"
#include <qlist.h>

class WeatherData 
{
    public :
        QString weatherCondition;
        QString cityName;
        int weatherCode;
        int temperature;
        
        // sunrise and sunset
        QString sunRiseTime;
        QString sunSetTime;
        
        // units
        QString tempUnit;
        QString distanceUnit;
        QString pressureUnit;
        QString speedUnit;
        
        // wind details
        QString chill;
        QString direction;
        QString speed;
        
        //atmosphere details
        QString humidity;
        QString visibility;
        QString pressure;
        QString rising;
                
        // published date
        QString publishedDate;
        
        // forecast details
        QList<ForecastData> forecastDataList;
};

#endif
