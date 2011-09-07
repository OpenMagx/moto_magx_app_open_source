/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#ifndef _RECORDSETTINGITEM_H_
#define _RECORDSETTINGITEM_H_
#include <ZSettingItem.h>
#include <RC_RecordInterface.h>
//#include "rcrecord.h"


class RecordSettingItem : public ZSettingItem
{
public:
	RecordSettingItem(QString, ZListBox*);
	~RecordSettingItem();
	virtual QString getFace();

private:
	QString face;
};

#endif
