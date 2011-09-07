/**********************************************************************************************************************************
weathershow for E8 EM30
version : 1.0   2010.3.10
Auther  : slbear <25828761@qq.com>
***********************************************************************************************************************************/
#include "code.h"
#include <ZApplication.h>
#include <ZConfig.h>
#include <qwallpaper.h>
#include <qpixmap.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	ZApplication *a = new ZApplication(argc, argv);
	ZConfig conf("/ezxlocal/download/appwrite/setup/ezx_theme.cfg");
	QString skinpath = conf.readEntry("THEME_GROUP_LOG", "CurrentTheme");
	qDebug(skinpath);

	ZConfig conf2(skinpath);
	QString oriwallpaper = conf2.readEntry("THEME_CONFIG_TABLE", "WallPaper");
	qDebug(oriwallpaper);
	
	QPixmap *ori_pixmap = new QPixmap(oriwallpaper);//QWallpaper::sysWallpaper();//new QPixmap(wallpaper);
	if(ori_pixmap->isNull())
	{
	qDebug("DEBUG::  wallpaper is null");
	return 0;
	}
	QWallpaper::setSysWallpaper(ori_pixmap);
	ori_pixmap = QWallpaper::sysWallpaper();
	
	ZConfig setupconf(SETUPPATH);
	QString cityid = setupconf.readEntry("SETUP", "cityid");
	QString curskin = setupconf.readEntry("SETUP", "skin");
	QPixmap *wppanel = new QPixmap(getAppDir()+"skins/"+curskin+"/wp/wpweather.png");
	QPixmap *alarmpanel = new QPixmap(getAppDir()+"skins/"+curskin+"/wp/wpalarm.png");	
	QString alarmtext = setupconf.readEntry("WP", "text");
	int panel_x = setupconf.readNumEntry("WP", "panel_x"); 
	int panel_y = setupconf.readNumEntry("WP", "panel_y");
	int alarmpanel_x = setupconf.readNumEntry("WP", "alarmpanel_x");
	int alarmpanel_y = setupconf.readNumEntry("WP", "alarmpanel_y");
	bool showwp = setupconf.readBoolEntry("SETUP", "showweather");
	bool showalarm = setupconf.readBoolEntry("SETUP", "showwpalarm");
	
	ZConfig wsconf(getAppDir()+"skins/"+curskin+"/skin.ini");
	QString weatherpath = wsconf.readEntry("panel1", "weathericon");
	

	int weather_x = wsconf.readNumEntry("WP", "weather_x"); 
	int weather_y = wsconf.readNumEntry("WP", "weather_y"); 
	int city_x = wsconf.readNumEntry("WP", "city_x"); 
	int city_y = wsconf.readNumEntry("WP", "city_y"); 
	int weathertext_x = wsconf.readNumEntry("WP", "weathertext_x"); 
	int weathertext_y = wsconf.readNumEntry("WP", "weathertext_y"); 
	int size_city = wsconf.readUIntEntry("WP", "size_city");
	int size_weather = wsconf.readUIntEntry("WP", "size_weather");
	QColor textcolor(wsconf.readUIntEntry("WP", "text_R"),wsconf.readUIntEntry("WP", "text_G"),wsconf.readUIntEntry("WP", "text_B"));
	
	

	int alarmtext_x = wsconf.readNumEntry("WPALARM", "alarmtext_x");
	int alarmtext_y = wsconf.readNumEntry("WPALARM", "alarmtext_y");
	QColor alarmcolor(wsconf.readUIntEntry("WPALARM", "alarm_R"),wsconf.readUIntEntry("WPALARM", "alarm_G"),wsconf.readUIntEntry("WPALARM", "alarm_B"));
	int size_alarm = wsconf.readUIntEntry("WPALARM", "size_alarmtext");
	
	ZConfig infoconf(INFOPATH);
	int img1 = infoconf.readUIntEntry(cityid, "img1");
	QString city = infoconf.readEntry(cityid,"city");
	QString weathertext = infoconf.readEntry(cityid, "weather1")+infoconf.readEntry(cityid, "temp1");
	QPixmap *weather;
	if(img1<10)
	weather = new QPixmap(QString(getAppDir()+"weathericon/"+weatherpath+"/smallicon/"+"s000%1"+".png").arg(img1));
	else
	weather = new QPixmap(QString(getAppDir()+"weathericon/"+weatherpath+"/smallicon/"+"s00%1"+".png").arg(img1));

	
	
	
	QPainter painter;
	painter.begin(ori_pixmap);
	if(showwp)
	{
	painter.drawPixmap(panel_x, panel_y, *wppanel);
	painter.drawPixmap(weather_x+panel_x, weather_y+panel_y, *weather);
	painter.setFont(QFont("AMSCL", size_city, QFont::Bold));
	painter.setPen(textcolor);
	painter.drawText(city_x+panel_x, city_y+panel_y, city);
	painter.setFont(QFont("AMSCL", size_weather, QFont::Normal));
	painter.drawText(weathertext_x+panel_x, weathertext_y+panel_y, weathertext);
	}
	if(showalarm)
	{
	painter.drawPixmap(alarmpanel_x, alarmpanel_y, *alarmpanel);
	painter.setFont(QFont("AMSCL", size_alarm, QFont::Bold));
	painter.setPen(alarmcolor);
	painter.drawText(alarmpanel_x+alarmtext_x, alarmpanel_y+alarmtext_y, alarmtext);
	}
	
	
	painter.end();
	QWallpaper::setSysWallpaper(ori_pixmap);
	//int i = a->exec();
	delete ori_pixmap;
	delete wppanel;
	delete weather;
	delete a;
	delete alarmpanel;
	//return i;
	//qApp->quit();
	
}
