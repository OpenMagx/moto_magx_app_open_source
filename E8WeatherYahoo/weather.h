#ifndef _WEATHER_H_
#define _WEATHER_H_

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#include <qsocket.h>
#include <qtextcodec.h>
#include <qfile.h>
#include <qxml.h>
#include <qwindowdefs.h>
#include <qpixmap.h>
#include <qwallpaper.h>

#include <ZKbMainWidget.h>
#include <ZSoftKey.h>
#include <ZOptionsMenu.h>
#include <ZScrollPanel.h>
#include <ZLabel.h>
#include <ZMessageDlg.h>
//#include <ZImage.h>
#include <ZConfig.h>
#include <ZAppInfoArea.h>

#include "./NAPI/NAPIManager.h"
#include "./NAPI/NAPILink.h"
#include "./header/napi.h"
#include "./header/ZDataSessionManager.h"
#include "weatherData.h"
#include "structureparser.h"
#include "citySelectDlg.h"

extern WeatherData weatherData;

class WeatherApp: public ZKbMainWidget
{
    Q_OBJECT
    public:
        WeatherApp();
        ~WeatherApp();
    
    public slots:
        void quit();
        void updateWeather();
        void drawOnDesktop();
	    void netConnected();
	    void showAbout();
	    void updateProfile();
	    void changeCity();
    
    private:
        NAPIManager *napi;
        NAPILink *link;
        int mlinkid;
           
        ZSoftKey *softkey;
        ZScrollPanel *myScrollPanel;
        ZLabel *content;
        ZOptionsMenu *mainOptions;

        struct tm * timeinfo;
        
        QString configFileName;
        QString citiesFileName;
        QString profName;  
        
        QString selectedCityId;
        QString skinName;
        QString skinFolder;
        
        int bgIconX, bgIconY;
        int iconX, iconY;
        int cityNameX, cityNameY;
        int tempX, tempY; 
        int cityFontSize;
        int tempFontSize;
        int fontColorR,fontColorG,fontColorB;
        
    private:
        void initConfig();
        void drawPrevData();
        void createWindow();
        void init();
        void parseWeatherData();
        QString getAppDir();
        void displayWeatherData();
        QString ctr(const char*ChineseString);
        
};

#endif

