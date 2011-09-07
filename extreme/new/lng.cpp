/******************************
Mgx installer
by wanggjghost(¿·§Œµ•“ÌÃÏ π)

www.591moto.cn
41245110@qq.com
please keep author information if you redistribute this program

**********************************/
#include <qfile.h>
#include <stdio.h>
#include <ZApplication.h>
#include <iostream>

#include "lng.h"

Lng::Lng()
{
	QString appDir = QString(qApp->argv()[0]);
    int i = appDir.findRev("/");
    appDir.remove(i+1, appDir.length()-1);
	QString appName = QString(qApp->argv()[0]);
	appName.remove(0, (appDir.findRev("/")+1) );
   // while ( appName.find("/") > -1 )
	//	appName.remove(0, appName.find("/")+1 );
	
	ZConfig cfg("/ezxlocal/download/appwrite/setup/ezx_system.cfg");
	QString lngStr = cfg.readEntry("SYS_SYSTEM_SET", "LanguageType", "");
	mLngType = lngStr;
	QString lngFile = QString("%1/%2_%3.lng").arg(appDir).arg(appName).arg(lngStr);
	std::cout<<"lng file "<<lngFile<<std::endl;
	if( !QFile::exists( lngFile ) )
		lngFile = QString("%1/%2_zh-cn.lng").arg(appDir).arg(appName);		
	
	std::cout<<"lng file "<<lngFile<<std::endl;
	mCfg = new ZConfig(lngFile);
}


Lng::~Lng()
{
	delete mCfg;
}

QString Lng::tr( const char * sourceText)
{
    QString tmp = mCfg->readEntry("LNG", QString(sourceText), "");
	if(tmp == "") 
	{
	    tmp = QString(sourceText);
		printf("%s =\n", sourceText); 
	}	
	return tmp; 
}
QString Lng::getCurLngType()
{
	return mLngType;
}

