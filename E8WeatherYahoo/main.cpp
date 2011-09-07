#include <ZApplication.h>
#include "weather.h"

/**
 * The main method
 */
WeatherData weatherData;

int main( int argc, char **argv )
{
	ZApplication* a = new ZApplication( argc, argv );
	WeatherApp *weather = new WeatherApp();
	a->showMainWidget(weather);
	a->exec();

	delete weather;
	delete a;
   	return argc;
}
