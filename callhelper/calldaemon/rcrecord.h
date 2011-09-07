/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#ifndef _RCRECORD_H_
#define _RCRECORD_H_
#include <qstring.h>
#include <qdatetime.h>
class RcRecord
{
public:
	RcRecord();
	~RcRecord();
	void setPhoneNumber(const QString& number);
	QString getPhoneNumber();
	
	void setStartDateTime(const QDateTime& startDt);
	QDateTime getStartDateTime();
	
	void setDuration(int duration);
	int getDuration();
	
	void setCompletedStatus(bool completed);
	bool getCompletedStatus();
	
	bool isRead();
	void setRead(bool read);
	
	void setUID();
	int getUID();
private:
	QString phonenumber;
	QDateTime startdatatime;
	int duration;
	bool completed;
	bool read;
	int uid;
};

#endif
