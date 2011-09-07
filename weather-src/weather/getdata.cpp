/**********************************************************************************************************************************
weathershow for E8 EM30
version : 1.0   2010.3.10
Auther  : slbear <25828761@qq.com>
***********************************************************************************************************************************/
#include <qdir.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qtextcodec.h>
#include "getdata.h"
//#include <iostream>
#include <ZApplication.h>
#include <ZConfig.h>
#include <ZSingleSelectDlg.h>
#include "code.h"
//using namespace std;
GetData::GetData(QString cityid)
{
	i=0;
	this->cityid =cityid;
	conf = new ZConfig(SETUPPATH);
	infoconf = new ZConfig(INFOPATH);
	loadConfig();
	connect(this, SIGNAL(signalStat(int)),this, SLOT(slotStat(int)));
}
bool GetData::checkProfile()
{
	if(profile==QString::null)
	return false;
	QFile f("/ezxlocal/download/appwrite/NetProfile/"+profile);
	if(!f.open(IO_ReadOnly))
	{
		return false;
	}
	char* p=new char[17];
	f.readBlock(p,17);
	char d[5];
	memcpy(d,p+12,5);
	d[5]='\0';
	QString ProfileType=QString(d);
	f.close();
	if(ProfileType!="cmwap")
	{
		return false;
	}	
	return true;
}

GetData::~GetData()
{
	delete conf;
	delete infoconf;
	delete socket;
	delete zd;
}

bool GetData::init()
{
	while(checkProfile()==false)
	{
		QDir pdir("/ezxlocal/download/appwrite/NetProfile/");
		QStringList plist = pdir.entryList(QDir::Files);
		ZSingleSelectDlg *dlg = new ZSingleSelectDlg(QString::fromUtf8("请选择cmwap联网方式"),NULL);
		dlg->addItemsList(plist);
		if(dlg->exec()==ZPopup::Accepted)
		{
			int i = dlg->getCheckedItemIndex();
			profile = plist[i];
			conf->writeEntry("SETUP", "profile", profile);
			conf->flush();
		}
		delete dlg;
	}
	zd=new ZDataSessionManager();
	if(zd->init()>>0)
	{
		if(zd->openLink(profile)>=0)
		{
			connect(zd,SIGNAL(connected(int, ZLinkInfo&)),this,SLOT(zconnected(int, ZLinkInfo&)));
			return true;
		}
		else
		{
			signalError(4);
		}
	}
	else
	{
		emit signalError(3);
	}
	return false;
}

void GetData::destroy()
{

}

void GetData::zconnected(int linkid, ZLinkInfo&)
{
	socket = new QSocket();
	zd->bindSocket2Link(linkid,socket->socket());	
	linkID=linkid;
	
	connect(socket,SIGNAL(hostFound()),this,SLOT(slothostFound()));
	connect(socket,SIGNAL(error(int)),this,SLOT(sloterror(int)) );
	connect(socket,SIGNAL(connectionClosed()),this,SLOT(slotconnectionClosed()));
	connect(socket,SIGNAL(delayedCloseFinished()),this,SLOT(slotconnectionClosed()));
	
	connect(socket,SIGNAL(connected()),this,SLOT(slotconnected()));
	connect(socket,SIGNAL(readyRead()),this,SLOT(slotreadyRead()));
	socket->connectToHost("10.0.0.172",80);	
	signalStat(2);
}

void GetData::slothostFound()
{
	emit signalStat(3);
}

void GetData::sloterror(int value)
{
	emit signalError(value);
	switch(value)
	{
		case 0:
			signalStat(4);
			break;
		case 1:
			signalStat(5);
			break;
		case 2:
			signalStat(6);
			break;
	}
	//zd->closeLink(linkID);
}

void GetData::slotconnectionClosed()
{
}

void GetData::slotconnected()
{
	signalStat(7);
	QTextStream os(socket);
	QString querystr="GET /data/"+cityid+".html HTTP/1.1\r\n";
	querystr+="Host: m.weather.com.cn\r\n\r\n";
    os <<querystr;
}


void GetData::slotreadyRead()
{
	signalStat(8);
	int bytes=socket->bytesAvailable();
	char *p=new char[bytes];
	
	socket->readBlock(p,bytes);
	wstr += QString::fromUtf8(QString(p));

	if(wstr.contains("HTTP/1.1 200 OK"))
	{
	if(wstr.contains("}}"))
	{
		qDebug("============================================================");
		qDebug(wstr);
		/*int pos = wstr.find("city");
		int pos1 = wstr.find("city_en", pos);
		QString city = wstr.mid(pos+7, pos1-3-pos-7);
		pos = wstr.find("date_y", pos1);
		pos1 = wstr.find("date", pos+6);
		QString date_y = wstr.mid(pos+9, pos1-pos-12);
		pos = wstr.find("week", pos1);
		QString date = wstr.mid(pos1+7, pos-pos1-10);
		pos1 = wstr.find("fchh", pos);
		QString week = wstr.mid(pos+7, pos1-pos-10);
		pos = wstr.find("cityid", pos1);
		QString fchh = wstr.mid(pos1+7, pos-pos1-10);
		pos1 = wstr.find("temp1", pos);
		QString cityid = wstr.mid(pos+9, pos1-pos-12);
		pos = wstr.find("temp2", pos1);
		QString temp1 = wstr.mid(pos1+8, pos-pos1-11);
		pos1 = wstr.find("temp3", pos);
		QString temp2 = wstr.mid(pos+8, pos1-pos-11);
		pos = wstr.find ("temp4", pos1);
		QString temp3 = wstr.mid(pos1+8, pos-pos1-11);
		pos1 = wstr.find("temp5", pos);
		QString temp4 = wstr.mid(pos+8, pos1-pos-11);
		pos = wstr.find("tempF1", pos1);
		QString temp5 = wstr.mid(pos1+8, pos-pos1-11);
		
		
		pos =  wstr.find("weather1", pos1);
		pos1 = wstr.find("weather2", pos);
		QString weather1 = wstr.mid(pos+11, pos1-pos-14);
		pos = wstr.find("weather3", pos1);
		QString weather2 = wstr.mid(pos1+11, pos-pos1-14);
		pos1 = wstr.find("weather4", pos);
		QString weather3 = wstr.mid(pos+11, pos1-pos-14);
		pos = wstr.find("weather5", pos1);
		QString weather4 = wstr.mid(pos1+11, pos-pos1-14);
		pos1 = wstr.find("img1", pos);
		QString weather5 = wstr.mid(pos+11, pos1-pos-14);
		pos = wstr.find("img2", pos1);
		QString img1 = wstr.mid(pos1+7, pos-pos1-10);
		pos1 = wstr.find("img3", pos);
		QString img2 = wstr.mid(pos+7, pos1-pos-10);
		pos = wstr.find("img4", pos1);
		QString img3 = wstr.mid(pos1+7, pos-pos1-10);
		pos1 = wstr.find("img5", pos);
		QString img4 = wstr.mid(pos+7, pos1-pos-10);
		pos = wstr.find("img6", pos1);
		QString img5 = wstr.mid(pos1+7, pos-pos1-10);
		pos1 = wstr.find("img7", pos);
		QString img6 = wstr.mid(pos+7, pos1-pos-10);
		pos = wstr.find("img8", pos1);
		QString img7 = wstr.mid(pos1+7, pos-pos1-10);
		pos1 = wstr.find("img9", pos);
		QString img8 = wstr.mid(pos+7, pos1-pos-10);
		pos = wstr.find("img10", pos1);
		QString img9 = wstr.mid(pos1+7, pos-pos1-10);
		pos1 = wstr.find("img_single", pos);
		QString img10 = wstr.mid(pos+8, pos1-pos-11);
		
		pos = wstr.find("wind1", pos1);
		pos1 = wstr.find("wind2", pos);
		QString wind1 = wstr.mid(pos+8, pos1-pos-11);
		pos = wstr.find("wind3", pos1);
		QString wind2 = wstr.mid(pos1+8, pos-pos1-11);
		pos1 = wstr.find("wind4", pos);
		QString wind3 = wstr.mid(pos+8, pos1-pos-11);
		pos = wstr.find("wind5", pos1);
		QString wind4 = wstr.mid(pos1+8, pos-pos1-11);		
		pos1 = wstr.find("fx1", pos);
		QString wind5 = wstr.mid(pos+8, pos1-pos-11);
		
		pos = wstr.find("index48_uv", pos1);
		pos1 = wstr.find("index_xc", pos);
		QString uv = wstr.mid(pos+13, pos1-pos-16);
		
		pos = wstr.find("index_co", pos1);
		pos1 = wstr.find("st1", pos);
		QString co = wstr.mid(pos+11, pos1-pos-14);
			
		infoconf->writeEntry(cityid, "city", city);	
		infoconf->writeEntry(cityid, "date_y", date_y);	
		infoconf->writeEntry(cityid, "date", date);	
		infoconf->writeEntry(cityid, "week", week);		
		infoconf->writeEntry(cityid, "fchh", fchh);
		infoconf->writeEntry(cityid, "temp1", temp1);
		infoconf->writeEntry(cityid, "temp2", temp2);
		infoconf->writeEntry(cityid, "temp3", temp3);
		infoconf->writeEntry(cityid, "temp4", temp4);
		infoconf->writeEntry(cityid, "weather1", weather1);
		infoconf->writeEntry(cityid, "weather2", weather2);
		infoconf->writeEntry(cityid, "weather3", weather3);
		infoconf->writeEntry(cityid, "weather4", weather4);
		infoconf->writeEntry(cityid, "img1", img1);
		infoconf->writeEntry(cityid, "img3", img3);
		infoconf->writeEntry(cityid, "img5", img5);
		infoconf->writeEntry(cityid, "img7", img7);
		infoconf->writeEntry(cityid, "wind1", wind1);
		infoconf->writeEntry(cityid, "wind2", wind2);
		infoconf->writeEntry(cityid, "wind3", wind3);
		infoconf->writeEntry(cityid, "wind4", wind4);
		infoconf->writeEntry(cityid, "uv", uv);
		infoconf->writeEntry(cityid, "co", co);
		infoconf->flush();*/
		
		
		int pos = wstr.find(QString("weatherinfo"));
		int pos1 = wstr.find(QString("}}"));
		wstr = wstr.mid(pos+14, pos1-pos-14);
		wstr.replace(QRegExp("\""),"");

		
		
		QStringList list = QStringList::split(",", wstr);
		for(QStringList::Iterator it = list.begin(); it!=list.end(); ++it)
		{
			qDebug(*it);
			pos = (*it).find(':');
			infoconf->writeEntry(cityid, (*it).left(pos), (*it).mid(pos+1));
		}
		infoconf->flush();
		
		
		qDebug("============================================================");
		emit success();
		
		i = 0;
	}
	else
	{
		//wstr = QString::fromUtf8(wstr);
		qDebug("----------------------------------------------------------");
		qDebug(wstr);
		qDebug("----------------------------------------------------------");
		
		if(wstr.find(QString::fromUtf8("weatherinfo")) == -1)
		{
			wstr = QString::null;
			QTextStream os(socket);
			QString querystr="GET /data/"+cityid+".html HTTP/1.1\r\n";
			querystr+="Host: m.weather.com.cn\r\n\r\n";
			os <<querystr;
			return;
		}
	}
	}
	else
	{
		qDebug("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		qDebug(QString::fromUtf8(wstr));
		qDebug("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		i = 0;
		emit signalError(5);
	}
}

void GetData::slotStat(int i)
{
	switch(i)
	{
		case 0:
			qDebug("DEBUG::   open profile error");
			break;
		case 1:
			qDebug("DEBUG::   I only support cmwap");
			break;
		case 2:
			qDebug("DEBUG::   connecting to host");
			break;
		case 3:
			qDebug("DEBUG::   finded host");
			break;
		case 4:
		case 5:
		case 6:
			qDebug("DEBUG::   error to connected to host");
			break;
		case 7:
			qDebug("DEBUG::   connected to host");
			break;
		case 8:
			qDebug("DEBUG::   reading data");
			break;	
		case 9:
			qDebug("DEBUG::   read data error");
	}
}

void GetData::loadConfig()
{
	profile = conf->readEntry("SETUP", "profile");
}
void GetData::setCityid(QString id)
{
	this->cityid = id;
}

