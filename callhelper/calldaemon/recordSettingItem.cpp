/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#include "recordSettingItem.h"


RecordSettingItem::RecordSettingItem(QString face, ZListBox* parent) : ZSettingItem(parent)
{
	this->face = face;
	//QString num = face->getPhoneNumber();
	//ADDRBK_SEARCH_RESULT_S asrs;
	//ADDRBK_ENG_Manager::searchByNumber(asrs, num);
	
	//SqlHelp sql;
	//QString title = sql.search(num);
	
	//this->appendSubItem(0, QString("%1%2  %3").arg(num).arg(asrs.name).arg(QString::fromUtf8(title)));	
	//this->appendSubItem(0,QString("%1/%2/%3 %4:%5:%6   %7").arg(face->getStartDateTime().date().year()).arg(face->getStartDateTime().date().month()).arg(face->getStartDateTime().date().day()).arg(face->getStartDateTime().time().hour()).arg(face->getStartDateTime().time().minute()).arg(face->getStartDateTime().time().second()).arg(face->getDuration()));
	
}

RecordSettingItem::~RecordSettingItem()
{
}

QString RecordSettingItem::getFace()
{
	return this->face;
}



