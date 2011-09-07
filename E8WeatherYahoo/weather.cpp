#include "weather.h"

static NAPILink *napi_link;


QString WeatherApp::ctr(const char*ChineseString)
{
	QTextCodec* gbkstr = QTextCodec::codecForName("UTF-8");
	return gbkstr->toUnicode(ChineseString);
}

WeatherApp::WeatherApp():ZKbMainWidget()
{
    initConfig();
    createWindow();
}

void WeatherApp::updateProfile()
{
    getProfileNamebySelect(profName); 
    ZConfig config (configFileName, true );
    config.writeEntry(QString("WeatherConfig"), QString("Profile"), profName);
    config.flush();
}

void WeatherApp::changeCity()
{
    CitySelectDlg *dlg = new CitySelectDlg("Select City","Select","Cancel");
    if(dlg->exec())
    {
        selectedCityId = dlg->getCityCode();    
        qDebug("Selected city is :" + selectedCityId);
        ZConfig config (configFileName, true );
        config.writeEntry(QString("WeatherConfig"), QString("City"), selectedCityId);
        config.flush();
        delete dlg;
    }
}


void WeatherApp::initConfig()
{
    profName = QString("");
    selectedCityId = QString("");
    napi = NULL;
    link = NULL;
    
    configFileName = getAppDir() + "weatherConfig.ini";
    ZConfig config (configFileName, false );
    profName = config.readEntry(QString("WeatherConfig"), QString("Profile"), "");
    selectedCityId = config.readEntry(QString("WeatherConfig"), QString("City"), "2295420");
    
    QString skin = config.readEntry(QString("WeatherConfig"), QString("Skin"), "default");
    skinFolder = getAppDir() + QString("skins/") + skin + QString("/");
    QString skinFile = skinFolder + QString("weatherSkin.ini");
    
    ZConfig skinConfig(skinFile,false);
	
	bgIconX = skinConfig.readUIntEntry("skinConfig","bgIconX");
	bgIconY = skinConfig.readUIntEntry("skinConfig", "bgIconY");
	
	iconX = skinConfig.readUIntEntry("skinConfig","iconX");
	iconY = skinConfig.readUIntEntry("skinConfig", "iconY");
	
	cityNameX = skinConfig.readUIntEntry("skinConfig", "cityNameX");
	cityNameY = skinConfig.readUIntEntry("skinConfig", "cityNameY");
	
	tempX = skinConfig.readUIntEntry("skinConfig", "tempX");
	tempY = skinConfig.readUIntEntry("skinConfig", "tempY");
        
    cityFontSize = skinConfig.readUIntEntry("skinConfig", "cityFontSize");
    tempFontSize = skinConfig.readUIntEntry("skinConfig", "tempFontSize");
    
    fontColorR = skinConfig.readUIntEntry("skinConfig", "fontColorR", 255);
    fontColorG = skinConfig.readUIntEntry("skinConfig", "fontColorG", 255);
    fontColorB = skinConfig.readUIntEntry("skinConfig", "fontColorB", 255);
    
    if(profName == "")
    {
        updateProfile();
    }
    
    
    if(selectedCityId == "")
    {
        changeCity();
    }
}

void WeatherApp::quit()
{
    qApp->quit();
}

void WeatherApp::createWindow()
{
    setAppTitle("Magx Weather");
    setBackgroundMode(NoBackground);
    
    softkey = new ZSoftKey("CST_2A",this);
    softkey->setText(ZSoftKey::LEFT,"Options");
    softkey->setText(ZSoftKey::RIGHT,"Exit");
    
    QRect rect;
    mainOptions = new ZOptionsMenu(rect, softkey , 0,0, ZSkinService::WidgetClsID(55));
    
    mainOptions->insertItem( "Update Weather", NULL, NULL, true, 0, 0 );
    mainOptions->insertItem( "Change Profile", NULL, NULL, true, 1, 1 );
    mainOptions->insertItem( "Change City", NULL, NULL, true, 2, 2 );        
    mainOptions->insertItem( "Draw on Desktop" , NULL, NULL, true, 3, 3);
    mainOptions->insertItem( "About", NULL, NULL, true, 4, 4 );
    mainOptions->insertItem( "Exit" , NULL, NULL, true, 5, 5 );
    
    mainOptions->connectItem(0, this, SLOT( updateWeather() ) );
    mainOptions->connectItem(1, this, SLOT( updateProfile() ) );
    mainOptions->connectItem(2, this, SLOT( changeCity() ) );
    mainOptions->connectItem(3, this, SLOT( drawOnDesktop() ) );
    mainOptions->connectItem(4, this, SLOT( showAbout() ) );
    mainOptions->connectItem(5, this, SLOT( quit() ) );    
    
    softkey->setOptMenu(ZSoftKey::LEFT, mainOptions);
    softkey->setClickedSlot(ZSoftKey::RIGHT, this, SLOT(quit()));
    setCSTWidget(softkey);
    
    myScrollPanel = new ZScrollPanel( this, NULL, 0, ZSkinService::clsZScrollPanel );
    content = new ZLabel(myScrollPanel->viewport());
    content->setFixedWidth(320);
    content->setAutoResize(TRUE);
    
    myScrollPanel->addChild(content,0,10);
    myScrollPanel->resizeContents(0,10);
    setContentWidget(myScrollPanel);
    content->setFocus();
    
    QFile f( getAppDir() + "weather.xml" );
    if( !f.exists() )
    {
        content->setText(QString("Welcome to Magx Weather. Select Options-> Update Weather to update weather information.") +
            QString(" Select Draw on Desktop in case you want to put the previously updated weather onto the desktop"));
    }
    else
    {
       displayWeatherData();
    }
    f.close();
    
}

void WeatherApp::drawPrevData()
{
    parseWeatherData();
    drawOnDesktop();
}

void WeatherApp::drawOnDesktop()
{
    time_t rawtime;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

    QString dayNightStr = "d";
    QString backgroundIcn = skinFolder + "wdgt_day.png";
    qDebug(QString::number(timeinfo->tm_hour));
    if(timeinfo->tm_hour >= 19 || timeinfo->tm_hour < 6)
    {
        dayNightStr = "n";
        backgroundIcn = skinFolder + "wdgt_night.png";
    }

    qDebug("Draw on Desktop to be implemented");
	ZConfig conf("/ezxlocal/download/appwrite/setup/ezx_theme.cfg");
	QString skinpath = conf.readEntry("THEME_GROUP_LOG", "CurrentTheme");
	qDebug(skinpath);

	ZConfig conf2(skinpath);
	QString oriwallpaper = conf2.readEntry("THEME_CONFIG_TABLE", "WallPaper");
	qDebug(oriwallpaper);
	
	QPixmap *ori_pixmap = new QPixmap(oriwallpaper);
	if(ori_pixmap->isNull())
	{
	    qDebug("DEBUG::  wallpaper is null");
	    return ;
	}
	
	
	QWallpaper::setSysWallpaper(ori_pixmap);
	//ori_pixmap = QWallpaper::sysWallpaper();

	QPixmap *weather;
	weather = new QPixmap(skinFolder + QString::number(weatherData.weatherCode) + dayNightStr + ".png");
	
	QPixmap *bg;
	bg = new QPixmap(backgroundIcn);	
	
	QPainter painter;
	
	painter.begin(ori_pixmap);
	painter.drawPixmap(bgIconX, bgIconY, *bg);
	painter.drawPixmap(iconX, iconY, *weather);
	painter.setFont(QFont("AMSCL", tempFontSize, QFont::Bold));
	QColor textcolor(fontColorR,fontColorG,fontColorB);
	painter.setPen(textcolor);
	
    QString s= QString::number(weatherData.temperature) + "°";

	painter.drawText(tempX, tempY, ctr(s));
	painter.setFont(QFont("AMSCL", cityFontSize));
	painter.drawText(cityNameX, cityNameY, weatherData.cityName);
	painter.end();
	
	QWallpaper::setSysWallpaper(ori_pixmap);
	
	delete ori_pixmap;
	delete bg;
	delete weather;
}

WeatherApp::~WeatherApp()
{
    //weatherData.forecastDataList.clear();
    
    if(NULL != napi_link)
    {
        delete napi_link;
    }
    
    if(NULL != napi)
    {
        delete napi;
    }   
    
    delete content;
    delete myScrollPanel;
    delete mainOptions;
    delete softkey;
}

void WeatherApp::updateWeather()
{
    napi = new NAPIManager(this);
	link = NULL;
	napi_link = 0;
	link = napi->openLink(profName);
	napi_link = link;
	QObject::connect(napi, SIGNAL(connected()), this, SLOT(netConnected()));
}

void WeatherApp::netConnected()
{
    if ( napi_link->linkId >= 0)
    {   
        qDebug("Connection Established");
        int sfd;
        struct ifreq ifr;
        struct sockaddr_in *sin = (struct sockaddr_in *) &ifr.ifr_addr;
   
        memset(&ifr, 0, sizeof ifr);

        if (0 > (sfd = socket(AF_INET, SOCK_STREAM, 0))) {
            perror("socket()");
            return;
        }

        strcpy(ifr.ifr_name, "psd_data5");
        sin->sin_family = AF_INET;

        if (0 == ioctl(sfd, SIOCGIFADDR, &ifr)) 
        {
            qDebug("Got the IP Address");
            QString ipAddr = QString(inet_ntoa(sin->sin_addr));
            qDebug(ipAddr);
            
            // run route add default gateway
            qDebug("Adding Network IP Default Gateway");
            
            QString command = "route add default gw " + ipAddr;
            system(command.latin1());

            QString command2 = "busybox wget \'http://weather.yahooapis.com/forecastrss?w=" + selectedCityId + "&u=c\' -O " + getAppDir() + "weather.xml";
            system(command2.latin1());
            
            NAPI_Fini();

            displayWeatherData();
            drawOnDesktop();
           
        }
    }
}

void WeatherApp::displayWeatherData()
{
    parseWeatherData();
    
    // showing weather details
    QString weatherStr = "City : " + weatherData.cityName + "\n\n";
    weatherStr = weatherStr + "Weather Condition : " + weatherData.weatherCondition + "\n";
    weatherStr = weatherStr + "Temperature : " + QString::number(weatherData.temperature) + "\n";
    weatherStr = weatherStr + "Last Update Time : " + weatherData.publishedDate + "\n\n";
    
    // sunrise and sunset
    weatherStr = weatherStr + "Astronomy Details" + "\n";
    weatherStr = weatherStr + "Sunrise : " + weatherData.sunRiseTime + "\n";
    weatherStr = weatherStr + "Sunset : " + weatherData.sunSetTime + "\n\n";
    
    // wind details
    weatherStr = weatherStr + "Wind Details" + "\n";
    weatherStr = weatherStr + "Chill : " + weatherData.chill + ctr("°" + weatherData.tempUnit) +  "\n";
    weatherStr = weatherStr + "Direction : " + weatherData.direction + " " +ctr("°") + "\n";
    weatherStr = weatherStr + "Speed : " + weatherData.speed + " " + weatherData.speedUnit + "\n\n";
    
    // atmosphere details
    weatherStr = weatherStr + "Atmosphere Details" + "\n";
    weatherStr = weatherStr + "Humidity : " + weatherData.humidity + ctr("%") +  "\n";
    weatherStr = weatherStr + "Visibility : " + weatherData.visibility + " " + weatherData.distanceUnit + "\n";
    weatherStr = weatherStr + "Pressure : " + weatherData.pressure + " " +weatherData.pressureUnit + "\n";
    
    QString risingState = "";
    if(weatherData.rising == "0")
    {
        risingState = "Steady";
    }
    else if(weatherData.rising == "1")
    {
        risingState = "Rising";
    }
    else
    {
        risingState = "Falling";
    }
    weatherStr = weatherStr + "Pressure State : " + risingState + "\n\n";
    
    // forecast details
    weatherStr = weatherStr + "Forecast" + "\n";
    QListIterator<ForecastData> forecastIter( weatherData.forecastDataList );
    ForecastData *fData;
    while ( (fData = forecastIter.current()) != 0 ) {
        ++forecastIter;
        weatherStr = weatherStr + "Day : " + fData->day +", " + fData->date + "\n";
        weatherStr = weatherStr + "Low Temperature : " + fData->lowTemp + ctr("°" + weatherData.tempUnit) + "\n";
        weatherStr = weatherStr + "High Temperature : " + fData->highTemp + ctr("°" + weatherData.tempUnit) + "\n";
        weatherStr = weatherStr + "Condition : " + fData->condition +"\n\n";
    }
    
    content->setText(weatherStr);
    QSize size = content->sizeHint();
    myScrollPanel->resizeContents(0,size.height());
    
}

QString WeatherApp::getAppDir()
{
    QString tmp = QString(qApp->argv()[0]);
    int i = tmp.findRev("/");
    tmp.remove(i+1,tmp.length()-1);
    return tmp;
}

void WeatherApp::showAbout()
{
	ZMessageDlg *aboutDlg = new ZMessageDlg("About",
                                "Magx Weather v0.1 Preview Version\nBy Deepak Srivastav\n",ZMessageDlg::TypeOK);
 	aboutDlg->exec();
	delete aboutDlg;
}

void WeatherApp::parseWeatherData()
{
    StructureParser handler;
    QXmlSimpleReader reader;
    reader.setContentHandler( &handler );
    QFile xmlFile( getAppDir() + "weather.xml" );
    QXmlInputSource source( xmlFile );
    reader.parse( source );
    
    qDebug("Weather condition:" + weatherData.weatherCondition);
    qDebug("Code:" + QString::number(weatherData.weatherCode));
    qDebug("Temp:" + QString::number(weatherData.temperature));
    
}

