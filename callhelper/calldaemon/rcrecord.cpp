/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#include "RcRecord.h"

RcRecord::RcRecord()
{
	phonenumber=QString::null;
	//startdatatime=0;
	duration=0;
	completed=false;
	read=false;
	uid=0;
}

RcRecord::~RcRecord()
{
}


void RcRecord::setPhoneNumber(const QString& number)
{
	phonenumber = number;
}
QString RcRecord::getPhoneNumber()
{
	return  phonenumber;
}	
void RcRecord::setStartDateTime(const QDateTime& startDt)
{
	startdatatime=startDt;
}
QDateTime RcRecord::getStartDateTime()
{
	return startdatatime;
}
void RcRecord::setDuration(int duration)
{
	this->duration=duration;
}
int RcRecord::getDuration()
{
	return duration;
}
void RcRecord::setCompletedStatus(bool completed)
{
	this->completed=completed;
}
bool RcRecord::getCompletedStatus()
{
	return completed;
}
bool RcRecord::isRead()
{
	return read;
}
void RcRecord::setRead(bool read)
{
	this->read=read;
}
int RcRecord::getUID()
{
	return uid;
}

